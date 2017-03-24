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
#include "console_stdc.h"
#include "main/evaluator.h"

#if defined(STDC_CONSOLE)
#include <stdio.h>

StandardConsole::StandardConsole(const char* prompt) :
    ConsoleBase(prompt), exit(false)
{
    line = new char[linesize];
}

StandardConsole::~StandardConsole()
{
    delete line;
}

bool StandardConsole::SetAnsiMode(bool value)
{
    return false;
}

void StandardConsole::Start()
{
    exit = false;
    fflush(stdin);
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
        WriteString(out);
        delete evaluator;
    }
}

void StandardConsole::Exit()
{
    exit = true;
}

void StandardConsole::ReadLine()
{
    fflush(stdin);
    fgets(line, linesize, stdin);
}

void StandardConsole::WriteString(const char* string)
{
    fputs(string, stdout);
    fflush(stdout);
}

void StandardConsole::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
}

#endif
