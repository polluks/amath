/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
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
 * http://amath.innolan.net
 * 
 */

#include "node.h"
#include "amathc.h"
#include "system/program.h"

FunctionNode::FunctionNode(ExpressionNode* expression, char* text, char* sys) :
    ExpressionNode(), expression(expression)
{
    AllocAndCopy(&this->name, text);
    AllocAndCopy(&this->sysname, sys);
}

FunctionNode::~FunctionNode()
{
    if (expression != nullptr)
    {
        delete expression;
    }

    if (name != nullptr)
    {
        delete name;
    }

    if (sysname != nullptr)
    {
        delete sysname;
    }
}

int FunctionNode::GetPrecedence()
{
    return 5;
}

char* FunctionNode::GetText()
{
    const char* functionText = GetNodeText();
    const char* expText = expression->GetText();

    output->EnsureSize(StrLen(functionText) + StrLen(expText) + 2 + 1);
    output->Empty();
    output->Append(functionText);
    output->Append("(");
    output->Append(expText);
    output->Append(")");

    return output->GetString();
}

char* FunctionNode::GetNodeText()
{
    return Program->Preferences->GetRefactorNames()
               ? sysname
               : name;
}

SyntaxNode* FunctionNode::GetNext()
{
    if (iterator == nullptr)
    {
        iterator = expression;
        return expression;
    }

    return nullptr;
}

void FunctionNode::Attach(SyntaxNode* node)
{
    if (expression == nullptr)
    {
        expression = static_cast<ExpressionNode*>(node);
        node->SetParent(this);
    }
}

void FunctionNode::Detach(SyntaxNode* node)
{
    if (expression == node)
    {
        expression = nullptr;
    }
}

void FunctionNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n)
    {
        delete expression;
        expression = static_cast<ExpressionNode*>(x);
    }
}
