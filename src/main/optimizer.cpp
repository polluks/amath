/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Project homepage:
 * https://amath.innolan.net
 * 
 */

#include "amath.h"
#include "nodes.h"
#include "values.h"
#include "optimizer.h"

Optimizer::Optimizer(SyntaxNode* root)
{
    this->root = root;
}

Optimizer::~Optimizer()
{
}

SyntaxNode* Optimizer::GetRoot() const
{
    return root;
}

void Optimizer::Optimize() const
{
    TagChildren(root);
    ReduceUnaryNodes(root);
    BalanceTree(root);
    ReduceValueNodes(root);
    TagStartNode(root);
}

void Optimizer::TagChildren(SyntaxNode* node)
{
    SyntaxNode* current;
    node->ResetIterator();
    while ((current = node->GetNext()) != nullptr)
    {
        current->SetParent(node);
        TagChildren(current);
    }
}

void Optimizer::BalanceTree(SyntaxNode* node)
{
    if (node == nullptr)
        return;

    node->ResetIterator();

    SyntaxNode* current = node->GetNext();

    while (current != nullptr)
    {
        if (current->GetNodeType() == expression)
        {
            ExpressionNode* troot = static_cast<ExpressionNode*>(current);
            troot->ResetIterator();
            ExpressionNode* pivot = static_cast<ExpressionNode*>(troot->GetNext());
            if (pivot != nullptr && troot->GetPrecedence() == pivot->GetPrecedence())
            {
                int rdepth = GetTreeDepth(troot, 1);
                int pdepth = GetTreeDepth(pivot, 0);
                if (rdepth - pdepth > 1 || rdepth - pdepth < -1)
                {
                    pivot->ResetIterator();
                    pivot->GetNext();
                    ExpressionNode* child = static_cast<ExpressionNode*>(pivot->GetNext());
                    if (child != nullptr)
                    {
                        SyntaxNode* parent = troot->GetParent();
                        parent->Detach(troot);
                        troot->Detach(pivot);
                        pivot->Detach(child);
                        troot->Attach(child);
                        pivot->Attach(troot);
                        parent->Attach(pivot);
                        current = pivot;
                        current->ResetIterator();
                    }
                }
            }
        }

        current = node->GetNext();
        BalanceTree(current);
    }
}

int Optimizer::GetTreeDepth(SyntaxNode* node, int depth)
{
    int max = depth;
    SyntaxNode* current;
    node->ResetIterator();

    while ((current = node->GetNext()) != nullptr)
    {
        int a = GetTreeDepth(current, depth + 1);
        if (a > max)
        {
            max = a;
        }
    }

    return max;
}

void Optimizer::ReduceUnaryNodes(SyntaxNode* node)
{
    SyntaxNode* current;
    node->ResetIterator();

    while ((current = node->GetNext()) != nullptr)
    {
        ReduceUnaryNodes(current);

        if (current->GetReductionType() == unaryreduc)
        {
            ExpressionNode* expression = static_cast<ExpressionNode*>(current);
            expression->ResetIterator();
            ExpressionNode* next = static_cast<ExpressionNode*>(expression->GetNext());

            if (next->GetReductionType() == unaryreduc)
            {
                next->ResetIterator();
                SyntaxNode* temp = next->GetNext();
                next->Detach(temp);
                SyntaxNode* parent = expression->GetParent();
                parent->Replace(expression, temp);
                current = parent;
                current->ResetIterator();
            }
            else if (next->GetReductionType() == valuereduc)
            {
                NumericValueNode* valueNode = static_cast<NumericValueNode*>(next);
                Number* number = valueNode->Evaluate();
                Number* modified = number->Unary();
                valueNode->ReplaceWith(modified);

                current->Detach(valueNode);
                SyntaxNode* parent = current->GetParent();
                parent->Replace(current, valueNode);
                current = parent;
                current->ResetIterator();
            }
        }
    }
}

void Optimizer::ReduceValueNodes(SyntaxNode* node)
{
    SyntaxNode* current;
    node->ResetIterator();

    while ((current = node->GetNext()) != nullptr)
    {
        if (current->GetNodeType() == expression)
        {
            ExpressionNode* expression = static_cast<ExpressionNode*>(current);
            ReductionType reduction = expression->GetReductionType();
            if (reduction == compladdreduc || reduction == complsubreduc)
            {
                expression->ResetIterator();
                NumericValueNode* first = static_cast<NumericValueNode*>(expression->GetNext());
                NumericValueNode* second = static_cast<NumericValueNode*>(expression->GetNext());
                if (
                    first->GetReductionType() == valuereduc && second->GetReductionType() == valuereduc &&
                    ((first->Evaluate()->PureComplexValue() && !second->Evaluate()->PureComplexValue()) ||
                        (!first->Evaluate()->PureComplexValue() && second->Evaluate()->PureComplexValue()))
                )
                {
                    Number* number =
                        reduction == compladdreduc ?
                            first->Evaluate()->Add(second->Evaluate()) :
                            first->Evaluate()->Sub(second->Evaluate());
                    NumericValueNode* reducedNode = new NumericValueNode(number);
                    SyntaxNode* parent = current->GetParent();
                    parent->Replace(current, reducedNode);
                    current = parent;
                    current->ResetIterator();
                }
            }
        }

        ReduceValueNodes(current);
    }
}

void Optimizer::TagStartNode(SyntaxNode* node)
{
    node->ResetIterator();
    SyntaxNode* next = node->GetNext();

    if (next != nullptr)
    {
        TagStartNode(next);
    }
    else
    {
        node->SetFirstNode();
    }
}
