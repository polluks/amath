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
#include "lib/charval.h"
#include "main/evaluator.h"
#include "system/console_stdc.h"

#if !defined(AMIGA)
#include <stdio.h>

StandardConsole::StandardConsole(const char* prompt, CharValidator* validator) :
    ConsoleBase(prompt)
{
    proc = new AnsiConoleEngine(prompt, validator);
    line = nullptr;
    exit = false;
}

StandardConsole::~StandardConsole()
{
    delete proc;
}

int StandardConsole::GetStackSize()
{
    return 100000;
}

void StandardConsole::Run()
{
    exit = false;
    StartMessage();

    while (!exit)
    {
        Prompt();
        ReadLine();
        Evaluator* evaluator = new Evaluator(line);
        evaluator->Evaluate();
        const char* res = evaluator->GetResult();
        Write(res, StrLen(res));
        delete evaluator;
    }
}

void StandardConsole::Exit()
{
    exit = true;
}

void StandardConsole::ReadLine()
{
#ifdef UNIX
    termios new_tio, old_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
#endif

    proc->StartInput();

    while (!proc->InputDone())
    {
        unsigned char c = getchar();
        const char* out = proc->ProcessChar(static_cast<char>(c));
        WriteString(out);
    }

    line = proc->GetLine();

#ifdef UNIX
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
#endif
}

void StandardConsole::WriteString(const char* string)
{
    Write(string, StrLen(string));
}

void StandardConsole::Write(const char* string, unsigned int length)
{
    unsigned int i = 0;
    while (i < length && string[i] != 0)
    {
        fputc(string[i], stdout);
        i++;
    }

    fflush(stdout);
}

void StandardConsole::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
    proc->SetPrompt(string);
}

#endif
