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

#ifndef AMATH_WINDOWS_CONSOLE
#define AMATH_WINDOWS_CONSOLE

/**
 * @file  console_windows.h
 * @brief Windows based console.
 *
 */

#include "amath.h"
#include "amathc.h"
#include "console.h"
#include "lib/charval.h"
#include "lib/aengine.h"

#if defined(WINDOWS)
#include <windows.h>

/**
 * @brief Encapsulates the IO of a console in Windows.
 *
 */
class WindowsConsole : public ConsoleBase
{
public:
    WindowsConsole(const char* prompt, CharValidator* validator);
    virtual ~WindowsConsole();
    virtual bool Open();
    virtual void Close();
    virtual void Start();
    virtual void Exit();
    virtual void SetPrompt(const char* string);
    virtual void WriteString(const char* string);
    virtual bool SetAnsiMode(bool value);

private:
    void ReadLine();
    static void Write(const char* string, unsigned int length);

    AnsiConoleEngine* proc;
    DWORD oldOutMode;
    DWORD oldInMode;
    const char* line;
    bool exit;
};

#endif
#endif
