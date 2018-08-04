/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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

#ifndef AMATH_CONSOLE_BASE
#define AMATH_CONSOLE_BASE

/**
 * @file  console.h
 * @brief Generic console system calls.
 *
 */

/**
 * @brief Abstract base class encapsulating console logic.
 *
 */
class ConsoleBase
{
public:
    explicit ConsoleBase(const char* prompt);
    virtual ~ConsoleBase();
    const char* GetName();
    virtual bool Open();
    virtual void Close();
    virtual void Start() = 0;
    virtual void Exit() = 0;
    virtual void Clear();
    virtual void ShowHelp();
    virtual void ShowAbout();
    virtual void ShowLicense();
    virtual void ShowVersion();
    virtual void SetPrompt(const char* string);
    virtual void WriteString(const char* string) = 0;
    virtual bool SetAnsiMode(bool value);
    virtual void ResetConsole();

protected:
    virtual void StartMessage();
    void Prompt();
    const char* GetVersionText();
    const char* GetCompilerText();
    char* prompt;
    bool ansiMode;

private:
    void AnsiItalics();
    void AnsiBold();
};

#endif
