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
#include "program_stdc.h"
#include "console_stdc.h"
#include "console_termios.h"
#include "console_windows.h"
#include "preferences_stdc.h"
#include "lib/charbuf.h"
#include "main/evaluator.h"

#if !defined(AMIGA) && !defined(HAIKU)

StandardProgram::StandardProgram()
    : Program()
{
    Console = nullptr;
    line = nullptr;
    shellMode = false;
}

StandardProgram::~StandardProgram()
{
    if (Console != nullptr)
    {
        Console->Close();
        delete Console;
    }

    if (line != nullptr)
    {
        delete line;
    }
}

void StandardProgram::Initialize(int argc, char** argv)
{
#if defined(WINDOWS)
        Console = new WindowsConsole(Preferences->GetPrompt(), Language);
#elif defined(TERMIOS)
        Console = new TermiosConsole(Preferences->GetPrompt(), Language);
#else
        Console = new StandardConsole(Preferences->GetPrompt(), Language);
#endif
    SetAnsiMode(true);

    line = new CharBuffer();
    line->Empty();

    bool options = true;
    unsigned int len = 1;
    for (int i = 1; i < argc; i++)
    {
        if (options)
        {
            if (StrIsEqual(argv[i], "noansi") || StrIsEqual(argv[i], "--noansi"))
            {
                SetAnsiMode(false);
                continue;
            }
            else if (StrIsEqual(argv[i], "shell") || StrIsEqual(argv[i], "--shell"))
            {
                shellMode = true;
            }
            else
            {
                options = false;
            }
        }

        if (!options)
        {
            len += StrLen(argv[i]) + 1;
            line->EnsureSize(len);
            line->Append(argv[i]);
            line->Append(' ');
        }
    }

    if (len > 1)
    {
        line->DeleteLastChar();
    }
}

void StandardProgram::Start()
{
    if(Console == nullptr || !Console->Open())
    {
        return;
    }

    Preferences->Load();

    if (!line->IsEmpty())
    {
        Evaluator* evaluator = new Evaluator(line->GetString());
        evaluator->Evaluate();
        const char* res = evaluator->GetResult();
        Console->WriteString(res);
        Console->ResetConsole();
        delete evaluator;
        return;
    }

#if defined(WINDOWS)
    Console->Start();
#else
    if (shellMode)
    {
        Console->Start();
        return;
    }

    SetAnsiMode(false);
    Console->ShowHelp();
#endif
}

#endif
