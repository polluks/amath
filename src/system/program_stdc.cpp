/*
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
 */

#include "amath.h"
#include "amathc.h"
#include "lib/charbuf.h"
#include "main/evaluator.h"
#include "system/program_stdc.h"
#include "system/console_stdc.h"
#include "system/language_stdc.h"
#include "system/filesystem_stdc.h"
#include "system/preferences_stdc.h"

#if !defined(AMIGA)
#include <stdio.h>

StandardProgram::StandardProgram()
    : Program()
{
    Console = nullptr;
    line = nullptr;
}

StandardProgram::~StandardProgram()
{
    if (Console != nullptr)
    {
        delete Console;
    }

    if (line != nullptr)
    {
        delete line;
    }
}

void StandardProgram::Initialize(int argc, char** argv)
{
    if (argc < 2)
    {
        // STDC version only has a console
        Console = new StandardConsole(Preferences->GetPrompt(), Language);
        return;
    }

    unsigned int len = 1;
    for (int i = 1; i < argc; i++)
    {
        len += StrLen(argv[i]) + 1;
    }

    line = new CharBuffer(len);
    line->Empty();

    for (int i = 1; i < argc; i++)
    {
        line->Append(argv[i]);
        line->Append(' ');
    }

    line->DeleteLastChar();

    if (line->Is("shell"))
    {
        Console = new StandardConsole(Preferences->GetPrompt(), Language);
    }
}

void StandardProgram::Run()
{
    Preferences->Load();

    if (Console != nullptr)
    {
        Console->Run();
        return;
    }

    Evaluator* evaluator = new Evaluator(line->GetString());
    evaluator->Evaluate();
    const char* res = evaluator->GetResult();
    printf("%s%s", res, NORMALTEXT);
    delete evaluator;
}

void StandardProgram::Exit()
{
    Console->Exit();
}

#endif