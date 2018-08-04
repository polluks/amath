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

#include "draw.h"
#include "amath.h"
#include "amathc.h"

DrawStatement::DrawStatement(const char* name, const char* parameter)
    : StatementNode()
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
}

DrawStatement::~DrawStatement()
{
    delete [] name;
    delete [] parameter;
}

char* DrawStatement::Execute()
{
#if 0
    UserFunction* function = Program->Functions->GetFunctionDef(name, parameter);

    if (function == nullptr)
    {
        return static_cast<char*>("Function does not exists." NEWLINE);
    }

    GraphWindow* graph = Program->Graphs->CreateNewWindow();

    if (graph == nullptr)
    {
        return static_cast<char*>("Graphs are not supported in this version.");
    }

    graph->OpenGraphWindow(function);
    graph->DrawGraph(function);
#endif
    return statementText;
}
