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

#include "delete.h"
#include "amath.h"
#include "amathc.h"
#include "loc/text.h"
#include "system/program.h"

/**
 * @brief Constructor used to delete either all variable or functions.
 *
 */
DeleteStatement::DeleteStatement(Symbol symbol) :
    StatementNode()
{
    type = symbol;
    name = nullptr;
    argument = nullptr;
}

/**
 * @brief Constructor used to delete a Variable.
 *
 */
DeleteStatement::DeleteStatement(const char* name) :
    StatementNode()
{
    type = symvariable;
    AllocAndCopy(&this->name, name);
    argument = nullptr;
}

/**
 * @brief Constructor used to delete a function.
 *
 */
DeleteStatement::DeleteStatement(const char* name, const char* argument) :
    StatementNode()
{
    type = symfunction;
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->argument, argument);
}


DeleteStatement::~DeleteStatement()
{
    if (name != nullptr)
    {
        delete [] name;
    }

    if (argument != nullptr)
    {
        delete [] argument;
    }
}

char* DeleteStatement::Execute()
{
    bool success = true;
    output->Empty();

    if (type == symvariable && name == nullptr)
    {
        Program->Variables->Clear();
    }
    else if (type == symvariable && name != nullptr)
    {
        success = Program->Variables->Delete(name);
        const char* msg = HELPVARNDEF;

        output->EnsureSize(
            StrLen(msg) +
            StrLen(name) +
            StrLen(NEWLINE) + 1);

        output->Append(msg);
        output->Append(name);
        output->Append(NEWLINE);
    }
    else if (type == symfunction && name == nullptr)
    {
        Program->Functions->Clear();
    }
    else if (type == symfunction && name != nullptr)
    {
        success = Program->Functions->Delete(name, argument);
        const char* msg = HELPFUNNDEF;

        output->EnsureSize(
            StrLen(msg) +
            StrLen(name) + 2 +
            StrLen(argument) +
            StrLen(NEWLINE) + 1);

        output->Append(msg);
        output->Append(name);
        output->Append("(");
        output->Append(argument);
        output->Append(")");
        output->Append(NEWLINE);
    }

    char* temp = success
                     ? statementText
                     : output->GetString();

    return temp;
}
