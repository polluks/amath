/*
 * Copyright (c) 2015 Carsten Larsen
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
 */

#include "def/libc.h"
#include "lib/numb.h"
#include "lib/charbuf.h"
#include "main/operators.h"

// -----------------------------------------------------
// -------------------- UnaryNode ----------------------
// -----------------------------------------------------

UnaryNode::UnaryNode(ExpressionNode* expression) :
    ExpressionNode(), expression(expression) { }

UnaryNode::~UnaryNode()
{
    if (expression != NOMEM) {
        delete expression;
    }
}

ReductionType UnaryNode::GetReductionType()
{
    return unaryreduc;
}

int UnaryNode::GetPrecedence()
{
    return 7;
}

char* UnaryNode::GetNodeText()
{
    return (char*)"-";
}

char* UnaryNode::GetText()
{
    const char *expText = expression->GetText();
    const char *nodeText = GetNodeText();

    output->Empty();
    output->EnsureSize(StrLen(expText) + StrLen(nodeText) + 2 + 1);

    if (expression->GetPrecedence() != 0 && expression->GetPrecedence() != 5 && expression->GetPrecedence() <= GetPrecedence()) {
        output->Append(nodeText);
        output->Append("(");
        output->Append(expText);
        output->Append(")");
    } else {
        output->Append(nodeText);
        output->Append(expText);
    }

    return output->GetString();
}

Number* UnaryNode::Evaluate()
{
    result = expression->Evaluate()->Unary();
    return result;
}

SyntaxNode* UnaryNode::GetNext()
{
    if (iterator == NOMEM) {
        iterator = expression;
        return iterator;
    }

    return NOMEM;
}

void UnaryNode::Attach(SyntaxNode* node)
{
    if (expression == NOMEM) {
        expression = (ExpressionNode*)node;
        node->SetParent(this);
    }
}

void UnaryNode::Detach(SyntaxNode* node)
{
    if (expression == node) {
        expression = NOMEM;
    }
}

void UnaryNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n) {
        delete expression;
        expression = (ExpressionNode*)x;
    }
}

// -----------------------------------------------------
// ------------------- AbsoluteNode --------------------
// -----------------------------------------------------

AbsoluteNode::AbsoluteNode(ExpressionNode* expression) :
    ExpressionNode(), expression(expression) { }

AbsoluteNode::~AbsoluteNode()
{
    if (expression != NOMEM) {
        delete expression;
    }
}

char* AbsoluteNode::GetText()
{
    const char *expText = expression->GetText();
    const char *nodeText = GetNodeText();

    output->Empty();
    output->EnsureSize(StrLen(expText) + StrLen(nodeText) * 2 + 1);
    output->Append(nodeText);
    output->Append(expText);
    output->Append(nodeText);

    return output->GetString();
}

int AbsoluteNode::GetPrecedence()
{
    return 8;
}

Number* AbsoluteNode::Evaluate()
{
    result = expression->Evaluate()->Absolute();
    return result;
}

char* AbsoluteNode::GetNodeText()
{
    return (char*)"|";
}

SyntaxNode* AbsoluteNode::GetNext()
{
    if (iterator == NOMEM) {
        iterator = expression;
        return iterator;
    }

    return NOMEM;
}

void AbsoluteNode::Attach(SyntaxNode* node)
{
    if (expression == NOMEM) {
        expression = (ExpressionNode*)node;
        node->SetParent(this);
    }
}

void AbsoluteNode::Detach(SyntaxNode* node)
{
    if (expression == node) {
        expression = NOMEM;
    }
}

void AbsoluteNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n) {
        delete expression;
        expression = (ExpressionNode*)x;
    }
}

// -----------------------------------------------------
// ----------------- NumericOperator -------------------
// -----------------------------------------------------

NumericOperator::NumericOperator(ExpressionNode* left, ExpressionNode* right) :
    ExpressionNode(), left(left), right(right) { }

NumericOperator::~NumericOperator()
{
    if (left != NOMEM) {
        delete left;
    }

    if (right != NOMEM) {
        delete right;
    }
}

char* NumericOperator::GetText()
{
    const char *leftText = left->GetText();
    const char *nodeText = GetNodeText();
    const char *rightText = right->GetText();

    output->Empty();
    output->EnsureSize(StrLen(leftText) + 2 + StrLen(nodeText) + StrLen(rightText) + 2 + 1);

    if (left->GetPrecedence() != 0 && left->GetPrecedence() < GetPrecedence()) {
        output->Append("(");
        output->Append(leftText);
        output->Append(")");
    } else {
        output->Append(leftText);
    }

    output->Append(nodeText);

    if (right->GetPrecedence() != 0 && GetPrecedence() > right->GetPrecedence()) {
        output->Append("(");
        output->Append(rightText);
        output->Append(")");
    } else {
        output->Append(rightText);
    }

    return output->GetString();
}

SyntaxNode* NumericOperator::GetNext()
{
    if (iterator == NOMEM) {
        iterator = left;
        return left;
    } else if (iterator == left) {
        iterator = right;
        return right;
    } else {
        return NOMEM;
    }
}

void NumericOperator::Attach(SyntaxNode* node)
{
    if(left == NOMEM) {
        left = (ExpressionNode*)node;
        node->SetParent(this);
    } else if (right == NOMEM) {
        right = (ExpressionNode*)node;
        node->SetParent(this);
    }
}

void NumericOperator::Detach(SyntaxNode* node)
{
    if (left == node) {
        left = NOMEM;
    } else if (right == node) {
        right = NOMEM;
    }
}

void NumericOperator::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (left == n) {
        if(iterator == left) {
            iterator = (ExpressionNode*)x;
        }
        delete left;
        left = (ExpressionNode*)x;

    } else if (right == n) {
        if(iterator == right) {
            iterator = (ExpressionNode*)x;
        }
        delete right;
        right = (ExpressionNode*)x;
    }
}

// -----------------------------------------------------
// ------------------- AdditionNode --------------------
// -----------------------------------------------------

AdditionNode::AdditionNode(ExpressionNode* left, ExpressionNode* right):
    NumericOperator(left, right) { }

ReductionType AdditionNode::GetReductionType()
{
    return compladdreduc;
}

int AdditionNode::GetPrecedence()
{
    return 2;
}

Number* AdditionNode::Evaluate()
{
    result = left->Evaluate()->Add(right->Evaluate());
    return result;
}

char* AdditionNode::GetNodeText()
{
    return (char*)"+";
}

// -----------------------------------------------------
// ----------------- SubtractionNode -------------------
// -----------------------------------------------------

SubtractionNode::SubtractionNode(ExpressionNode* left, ExpressionNode* right) :
    NumericOperator(left, right) { }

ReductionType SubtractionNode::GetReductionType()
{
    return complsubreduc;
}

int SubtractionNode::GetPrecedence()
{
    return 2;
}

Number* SubtractionNode::Evaluate()
{
    result = left->Evaluate()->Sub(right->Evaluate());
    return result;
}

char* SubtractionNode::GetNodeText()
{
    return (char*)"-";
}

// -----------------------------------------------------
// ----------------- MultiplicationNode ----------------
// -----------------------------------------------------

MultiplicationNode::MultiplicationNode(ExpressionNode* left, ExpressionNode* right) :
    NumericOperator(left, right) { }

int MultiplicationNode::GetPrecedence()
{
    return 3;
}

Number* MultiplicationNode::Evaluate()
{
    result = left->Evaluate()->Mul(right->Evaluate());
    return result;
}

char* MultiplicationNode::GetNodeText()
{
    return (char*)"*";
}

// -----------------------------------------------------
// ------------------- DivisionNode --------------------
// -----------------------------------------------------

DivisionNode::DivisionNode(ExpressionNode* left, ExpressionNode* right) :
    NumericOperator(left, right) { }

int DivisionNode::GetPrecedence()
{
    return 3;
}

Number* DivisionNode::Evaluate()
{
    result = left->Evaluate()->Div(right->Evaluate());
    return result;
}

char* DivisionNode::GetNodeText()
{
    return (char*)"/";
}

// -----------------------------------------------------
// -------------------- PowerNode ----------------------
// -----------------------------------------------------

PowerNode::PowerNode(ExpressionNode* left, ExpressionNode* right):
    NumericOperator(left, right) { }

int PowerNode::GetPrecedence()
{
    return 4;
}

Number* PowerNode::Evaluate()
{
    Number* exponent = right->Evaluate();
    result = left->Evaluate()->Raise(exponent);
    return result;
}

char* PowerNode::GetNodeText()
{
    return (char*)"^";
}

// -----------------------------------------------------
// ------------------ AssignmentNode -------------------
// -----------------------------------------------------

AssignmentNode::AssignmentNode(VariableNode* variable, ExpressionNode* expression):
    NumericOperator(variable, expression),
    variable(variable), expression(expression) { }

int AssignmentNode::GetPrecedence()
{
    return 6;
}

Number* AssignmentNode::Evaluate()
{
    // NOTICE: Assignment does not generate a value itself.
    variable->AssignValue(expression->Evaluate());
    return variable->Evaluate();
}

bool AssignmentNode::IsSilent()
{
    return true;
}

char* AssignmentNode::GetNodeText()
{
    return (char*)"=";
}


