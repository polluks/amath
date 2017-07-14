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
 * https://amath.innolan.net
 * 
 */

#include "amath.h"
#include "amathc.h"
#include "userfunction.h"

UserFunction::UserFunction(const char* name, const char* variable, ExpressionNode* expression)
{
    AllocAndCopy(&this->name, name);
    this->variable = new Variable(variable);
    this->expression = expression;
    this->Next = nullptr;

    defname = new CharBuffer();
    definition = new CharBuffer();
    InitializeTexts();

    chainDelete = true;
}

UserFunction::UserFunction(const char* name)
{
    AllocAndCopy(&this->name, name);
    this->variable = nullptr;
    this->expression = nullptr;
    this->Next = nullptr;

    defname = new CharBuffer();
    definition = new CharBuffer();

    chainDelete = true;
}

UserFunction::~UserFunction()
{
    delete [] name;
    delete defname;
    delete definition;

    if (variable != nullptr)
    {
        delete variable;
    }

    if (expression != nullptr)
    {
        delete expression;
    }

    if (chainDelete && Next != nullptr)
    {
        delete Next;
    }
}

void UserFunction::InitializeTexts() const
{
    defname->Empty();
    defname->Append(name);
    defname->Append('(');
    defname->Append(variable != nullptr ? variable->GetName() : EMPTYSTRING);
    defname->Append(')');

    definition->Empty();
    definition->Append(defname->GetString());
    definition->Append('=');
    definition->Append(expression != nullptr ? expression->GetText() : EMPTYSTRING);
}

char* UserFunction::GetName() const
{
    return name;
}

char* UserFunction::GetDefinitionName() const
{
    return defname->GetString();
}

char* UserFunction::GetDefinitionText() const
{
    return definition->GetString();
}

Variable* UserFunction::GetVariable() const
{
    return variable;
}

Variable* UserFunction::CreateVariable(const char* name)
{
    if (variable != nullptr)
    {
        delete variable;
    }

    variable = new Variable(name);
    InitializeTexts();

    return variable;
}

ExpressionNode* UserFunction::GetExpression() const
{
    return expression;
}

void UserFunction::SetExpression(ExpressionNode* expression)
{
    delete this->expression;
    this->expression = expression;
    InitializeTexts();
}
