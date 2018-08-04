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

#include "eval.h"
#include "amath.h"
#include "amathc.h"
#include "system/program.h"

EvalStatement::EvalStatement(ExpressionNode* expression) :
    StatementNode(), expression(expression)
{
}

EvalStatement::~EvalStatement()
{
    if (expression != nullptr)
    {
        delete expression;
    }
}

char* EvalStatement::Execute()
{
    Number* result = expression->Evaluate();
    Number* temp = result->Clone();
    const char* text = expression->GetText();
    const char* val = Program->Output->GetText(result);

    Program->SetLastResult(temp);
    delete temp;

    output->Empty();
    output->EnsureSize(
        StrLen(text) + 3 +
        StrLen(val) +
        StrLen(NEWLINE) + 1);

    output->Append(text);
    output->Append(" = ");
    output->Append(val);
    output->Append(NEWLINE);

    return output->GetString();
}

SyntaxNode* EvalStatement::GetNext()
{
    if (iterator == nullptr)
    {
        iterator = expression;
        return iterator;
    }

    return nullptr;
}

void EvalStatement::Attach(SyntaxNode* node)
{
    if (expression == nullptr)
    {
        expression = static_cast<ExpressionNode*>(node);
        node->SetParent(this);
    }
}

void EvalStatement::Detach(SyntaxNode* node)
{
    if (expression == node)
    {
        expression = nullptr;
    }
}

void EvalStatement::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n)
    {
        delete expression;
        expression = static_cast<ExpressionNode*>(x);
    }
}
