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

#include "save.h"
#include "amath.h"
#include "loc/text.h"
#include "system/program.h"

SaveStatement::SaveStatement(const char* file)
    : StatementNode()
{
    AllocAndCopy(&this->file, file);
}

SaveStatement::~SaveStatement()
{
    delete [] file;
}

char* SaveStatement::Execute()
{
    const char* vars = Program->Variables->ListDefinitions();
    const char* funcs = Program->Functions->ListDefinitions();

    if (vars == nullptr && funcs == nullptr)
    {
        return static_cast<char*>(HELPSAVENOTH);
    }

    int len = 1;
    len += vars != nullptr ? StrLen(vars) : 0;
    len += funcs != nullptr ? StrLen(funcs) : 0;

    CharBuffer* text = new CharBuffer(len);
    text->Empty();

    if (vars != nullptr)
    {
        text->Append(vars);
    }
    if (funcs != nullptr)
    {
        text->Append(funcs);
    }

    bool success = Program->Filesystem->SaveTextFile(file, text->GetString());
    delete text;

    return static_cast<char*>(success ? HELPSAVESUCC : HELPSAVEFAIL);
}
