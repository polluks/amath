/*
 * Copyright (c) 2015 Carsten Larsen
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

#include "def/libc.h"

#ifndef AMIGA
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "main/nodes.h"
#include "main/evaluator.h"
#include "arc/stdc/cconsole.h"

StandardConsole::StandardConsole()
{
    proc = new AnsiConoleEngine();
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

    while(!exit) {
        Promt();
        ReadLine();
        Evaluator *evaluator = new Evaluator(line);
        evaluator->Evaluate();
        const char *res = evaluator->GetResult();
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
    termios new_tio, old_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    proc->StartInput();

    while (!proc->InputDone()) {
        unsigned char c = getchar();
        //printf("%d ",c);
        const char *out = proc->ProcessChar((char)c);
        WriteString(out);
    }

    line = proc->GetLine();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

void StandardConsole::WriteString(const char *string)
{
    Write(string, StrLen(string));
}

void StandardConsole::Write(const char *string, unsigned int length)
{
    unsigned int i = 0;
    while(i < length && string[i] != 0) {
        fputc(string[i], stdout);
        i++;
    }

    fflush(stdout);
}

#endif