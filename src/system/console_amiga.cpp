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
#include "main/evaluator.h"
#include "system/console_amiga.h"

#ifdef AMIGA
#include <clib/dos_protos.h>

AmigaShellConsole::AmigaShellConsole(const char* prompt) :
    ConsoleBase(prompt)
{
    line = new char[linesize];
    exit = false;
}

AmigaShellConsole::~AmigaShellConsole()
{
    delete line;
}

int AmigaShellConsole::GetStackSize()
{
    return 100000;
}

void AmigaShellConsole::Run()
{
    exit = false;
    Flush(Input());
    StartMessage();

    while (!exit)
    {
        Prompt();
        ReadLine();

        if (*line == '\0')
        {
            break;
        }

        Evaluator* evaluator = new Evaluator(line);
        evaluator->Evaluate();
        const char* out = evaluator->GetResult();
        Write(Output(), (APTR)out, StrLen(out));
        delete evaluator;
    }
}

void AmigaShellConsole::Exit()
{
    exit = true;
}

void AmigaShellConsole::ReadLine()
{
    Flush(Input());
    FGets(Input(), line, linesize);
}

void AmigaShellConsole::WriteString(const char* string)
{
    Write(Output(), (APTR)string, StrLen(string));
    Flush(Output());
}

void AmigaShellConsole::WriteString(const char* string, unsigned int length)
{
    Write(Output(), (APTR)string, length);
    Flush(Output());
}

void AmigaShellConsole::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
}

#endif
