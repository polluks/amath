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

#include "amath.h"
#include "amathc.h"
#include "functionlist.h"
#include "userfunction.h"
#include "function/defs.h"
#include "function/user.h"
#include "localize/text.h"
#include "localize/ialias.h"

FunctionList::FunctionList()
{
    first = nullptr;
    buf = new CharBuffer();
}

FunctionList::~FunctionList()
{
    if (first != nullptr)
    {
        delete first;
    }

    delete buf;
}

void FunctionList::Clear()
{
    if (first != nullptr)
    {
        delete first;
        first = nullptr;
    }

    buf->ClearBuffer();
}

bool FunctionList::Delete(const char* name, const char* argument)
{
    if (first == nullptr)
    {
        return false;
    }

    if (first != nullptr && StrIsEqual(first->GetName(), name) && StrIsEqual(first->GetVariable()->GetName(), argument))
    {
        UserFunction* func = first;
        first = first->Next;
        func->chainDelete = false;
        delete func;
        return true;
    }

    UserFunction* current = first->Next;
    UserFunction* last = first;

    while (current != nullptr && !StrIsEqual(current->GetName(), name))
    {
        current = current->Next;
        last = last->Next;
    }

    if (current == nullptr)
    {
        return false;
    }
    else if (!StrIsEqual(current->GetVariable()->GetName(), argument))
    {
        return false;
    }

    last->Next = current->Next;

    // Only delete this variable. Not the whole chain.
    current->chainDelete = false;
    delete current;

    return true;
}

UserFunction* FunctionList::GetFirstFunction() const
{
    return first;
}

UserFunction* FunctionList::GetFunctionDef(const char* name)
{
    // Search the list for function definition. If function not found then create a new definition.
    if (first == nullptr)
    {
        first = new UserFunction(name);
        return first;
    }

    UserFunction* current = first;
    UserFunction* last = nullptr;

    while (current != nullptr)
    {
        if (StrIsEqual(current->GetName(), name))
        {
            return current;
        }

        last = current;
        current = current->Next;
    }

    current = new UserFunction(name);
    last->Next = current;

    return current;
}

UserFunction* FunctionList::GetFunctionDef(const char* name, const char* argument) const
{
    UserFunction* current = first;

    while (current != nullptr)
    {
        if (StrIsEqual(current->GetName(), name) && StrIsEqual(current->GetVariable()->GetName(), argument))
        {
            return current;
        }

        current = current->Next;
    }

    return nullptr;
}

FunctionNode* FunctionList::GetFunctionCall(const char* function, ExpressionNode* parameter) const
{
    const functiondef* systemFunction = GetSystemFunction(function);
    if (systemFunction != nullptr)
    {
        char* sysname = FindAlias(function);
        return (systemFunction->create)(parameter, const_cast<char*>(function), sysname);
    }

    UserFunction* current = first;
    while (current != nullptr && !StrIsEqual(current->GetName(), function))
    {
        current = current->Next;
    }

    if (current != nullptr)
    {
        return new UserFunctionNode(current, parameter);
    }

    return nullptr;
}

char* FunctionList::List() const
{
    return ListContent(false);
}

char* FunctionList::ListDefinitions() const
{
    return ListContent(true);
}

char* FunctionList::ListContent(bool cmdFormat) const
{
    if (first == nullptr)
    {
        return static_cast<char*>(cmdFormat ? nullptr : HELPFUNCNDEF);
    }

    int len = 0;
    UserFunction* current = first;

    while (current != nullptr)
    {
        len += StrLen(current->GetName());
        len += 1;
        len += StrLen(current->GetVariable()->GetName());
        len += 2;
        len += StrLen(current->GetExpression()->GetText());
        len += cmdFormat ? 2 : 1;
        current = current->Next;
    }

    buf->Empty();
    buf->EnsureSize(len + StrLen(NEWLINE) + 1);

    current = first;
    while (current != nullptr)
    {
        buf->Append(current->GetName());
        buf->Append("(");
        buf->Append(current->GetVariable()->GetName());
        buf->Append(")=");
        buf->Append(current->GetExpression()->GetText());

        if (cmdFormat)
        {
            buf->Append(';');
        }

        buf->Append(NEWLINE);
        current = current->Next;
    }

    return buf->GetString();
}

bool FunctionList::IsSystemFunction(const char* name)
{
    return (GetSystemFunction(name) != nullptr);
}

functiondef* FunctionList::GetSystemFunction(const char* ident)
{
    char* s = FindAlias(ident);
    static const unsigned int count = sizeof(functiondefs) / sizeof(functiondef);
    for (unsigned int i = 0; i < count; i++)
    {
        if (StrIsEqual(functiondefs[i].name, s))
        {
            return const_cast<functiondef*>(&functiondefs[i]);
        }
    }

    return nullptr;
}

char* FunctionList::FindAlias(const char* ident)
{
    static const unsigned int count = sizeof(identaliases) / sizeof(identalias);
    for (unsigned int i = 0; i < count; i++)
    {
        if (StrIsEqual(identaliases[i].ident, ident))
        {
            return const_cast<char*>(identaliases[i].alias);
        }
    }

    return const_cast<char*>(ident);
}
