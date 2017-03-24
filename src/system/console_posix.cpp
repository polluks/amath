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
#include "console.h"
#include "console_posix.h"
#include "lib/charval.h"
#include "lib/aengine.h"
#include "main/evaluator.h"

#if defined(POSIX)
#include <stdio.h>
#include <termios.h>

PosixConsole::PosixConsole(const char* prompt, CharValidator* validator) :
    ConsoleBase(prompt), line(nullptr), exit(false)
{
    proc = new AnsiConoleEngine(prompt, validator);
}

PosixConsole::~PosixConsole()
{
    delete proc;
}

bool PosixConsole::Open()
{
    if (tcgetattr(STDIN_FILENO, &oldAttr) != 0)
    {
        termError = true;
        return false;
    }

    newAttr = oldAttr;
    newAttr.c_lflag &=(~ICANON & ~ECHO);
    newAttr.c_cc[VMIN] = 1;
    newAttr.c_cc[VTIME] = 0;

    return (tcsetattr(STDIN_FILENO, TCSANOW, &newAttr) != -1);
}

void PosixConsole::Close()
{
    if (!termError)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);
    }
}

void PosixConsole::Start()
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

void PosixConsole::Exit()
{
    exit = true;
}

void PosixConsole::ReadLine()
{
    proc->StartInput();
    while (!proc->InputDone())
    {
        unsigned char c = getchar();
        const char* out = proc->ProcessChar(static_cast<char>(c));
        WriteString(out);
    }

    line = proc->GetLine();
}

void PosixConsole::WriteString(const char* string)
{
    Write(string, StrLen(string));
}

void PosixConsole::Write(const char* string, unsigned int length)
{
    unsigned int i = 0;
    while (i < length && string[i] != 0)
    {
        fputc(string[i], stdout);
        i++;
    }

    fflush(stdout);
}

void PosixConsole::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
    proc->SetPrompt(string);
}

#endif
