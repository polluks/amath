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

#include "amath.h"

#if defined(WINDOWS)
#include "amathc.h"
#include "console.h"
#include "console_windows.h"
#include "lib/charval.h"
#include "lib/aengine.h"
#include "main/evaluator.h"
#include "loc/text.h"
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#ifndef DISABLE_NEWLINE_AUTO_RETURN
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008
#endif
#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200
#endif

#define IN_DEFAULT \
    ENABLE_PROCESSED_INPUT

#define IN_ANSI \
    ENABLE_PROCESSED_INPUT | \
    ENABLE_VIRTUAL_TERMINAL_INPUT

#define OUT_DEFAULT \
    ENABLE_PROCESSED_OUTPUT | \
    ENABLE_WRAP_AT_EOL_OUTPUT

#define OUT_ANSI1 \
    ENABLE_PROCESSED_OUTPUT | \
    ENABLE_WRAP_AT_EOL_OUTPUT | \
    ENABLE_VIRTUAL_TERMINAL_PROCESSING | \
    DISABLE_NEWLINE_AUTO_RETURN

#define OUT_ANSI2 \
    ENABLE_PROCESSED_OUTPUT | \
    ENABLE_WRAP_AT_EOL_OUTPUT | \
    ENABLE_VIRTUAL_TERMINAL_PROCESSING

#define OUT_WHITE \
    FOREGROUND_INTENSITY | \
    FOREGROUND_RED | \
    FOREGROUND_GREEN | \
    FOREGROUND_BLUE

WindowsConsole::WindowsConsole(const char* prompt, CharValidator* validator) :
    ConsoleBase(prompt), line(nullptr), exit(false)
{
    proc = new AnsiConoleEngine(prompt, validator);
}

WindowsConsole::~WindowsConsole()
{
}

void WindowsConsole::Clear()
{
    if (ansiMode)
    {
        ConsoleBase::Clear();
    }
    else
    {
        HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (in == INVALID_HANDLE_VALUE || out == INVALID_HANDLE_VALUE)
        {
            return;
        }

        system("cls");
        SetConsoleMode(in, IN_DEFAULT);
        SetConsoleMode(out, OUT_DEFAULT);
    }
}

void WindowsConsole::StartMessage()
{
    if (ansiMode)
    {
        ConsoleBase::StartMessage();
    }
    else
    {
        CONSOLE_SCREEN_BUFFER_INFO old;
        WORD oldColor;

        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (out == INVALID_HANDLE_VALUE)
        {
            ConsoleBase::StartMessage();
            return;
        }

        if (!GetConsoleScreenBufferInfo(out, &old)) 
        {
            ConsoleBase::StartMessage();
            return;
        }

        oldColor = old.wAttributes; 

        if (!SetConsoleTextAttribute(out, OUT_WHITE))
        {
            ConsoleBase::StartMessage();
            return;
        }

        WriteString(INTROMSG);
        ResetConsole();

        SetConsoleTextAttribute(out, oldColor);
    }
}

void WindowsConsole::ShowVersion()
{
 if (ansiMode)
    {
        ConsoleBase::ShowVersion();
    }
    else
    {
        CONSOLE_SCREEN_BUFFER_INFO old;
        WORD oldColor;

        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (out == INVALID_HANDLE_VALUE)
        {
            ConsoleBase::ShowVersion();
            return;
        }

        if (!GetConsoleScreenBufferInfo(out, &old)) 
        {
            ConsoleBase::ShowVersion();
            return;
        }

        oldColor = old.wAttributes; 

        if (!SetConsoleTextAttribute(out, OUT_WHITE))
        {
            ConsoleBase::ShowVersion();
            return;
        }

        WriteString(GetVersionText());
        ResetConsole();

        SetConsoleTextAttribute(out, oldColor);

        WriteString(NEWLINE);
        WriteString(GetCompilerText());
        WriteString(NEWLINE);
        ResetConsole();
    }
}

bool WindowsConsole::Open()
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    if (in == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    if (!GetConsoleMode(in, &oldInMode))
    {
        return false;
    }

    if (!SetConsoleMode(in, IN_DEFAULT))
    {
        return false;
    }

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    if (!GetConsoleMode(out, &oldOutMode))
    {
        return false;
    }

    if (!SetConsoleMode(out, OUT_DEFAULT))
    {
        return false;
    }

    return true;
}

void WindowsConsole::Close()
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    if (in == INVALID_HANDLE_VALUE)
    {
        return;
    }
    SetConsoleMode(in, oldInMode);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE)
    {
        return;
    }
    SetConsoleMode(in, oldOutMode);
}

bool WindowsConsole::SetAnsiMode(bool value)
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    if (in == INVALID_HANDLE_VALUE)
    {
        ConsoleBase::SetAnsiMode(false);
        return false;
    }

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE)
    {
        ConsoleBase::SetAnsiMode(false);
        return false;
    }

    // Disable virtual terminal
    if (!value)
    {
        SetConsoleMode(in, IN_DEFAULT);
        SetConsoleMode(out, OUT_DEFAULT);
        ConsoleBase::SetAnsiMode(false);
        proc->Disable();
        return true;
    }

    bool success = true;

    // Enable virtual terminal
    if (!SetConsoleMode(out, OUT_ANSI1))
    {
        if (!SetConsoleMode(out, OUT_ANSI2))
        {
            success = false;
        }
    }

    if (!SetConsoleMode(in, IN_ANSI))
    {
        success = false;
    }

    if (!success)
    {
        SetConsoleMode(in, IN_DEFAULT);
        SetConsoleMode(out, OUT_DEFAULT);
        proc->Disable();
    }

    ConsoleBase::SetAnsiMode(success);
    proc->Enable();
    return success;
}

void WindowsConsole::Start()
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
        ResetConsole();
        delete evaluator;
    }
}

void WindowsConsole::Exit()
{
    exit = true;
}

void WindowsConsole::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
    proc->SetPrompt(string);
}

void WindowsConsole::ReadLine()
{
    DWORD count;
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    if (in == INVALID_HANDLE_VALUE)
    {
        return;
    }

    char inchar;
    proc->StartInput();
    while (!proc->InputDone())
    {
        ReadConsole(in, &inchar, 1, &count, nullptr);
        const char* out = proc->ProcessChar(inchar);
        WriteString(out);
    }

    line = proc->GetLine();
}

void WindowsConsole::WriteString(const char* string)
{
    Write(string, StrLen(string));
}

void WindowsConsole::Write(const char* string, unsigned int length)
{
    DWORD count;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE)
    {
        return;
    }

    WriteConsoleA(out, string, length, &count, nullptr);
}

#endif
