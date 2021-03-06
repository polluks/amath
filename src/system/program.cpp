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

#include "amath.h"
#include "amathc.h"
#include "program.h"
#include "language.h"
#include "language_stdc.h"
#include "language_amiga.h"
#include "filesystem.h"
#include "filesystem_stdc.h"
#include "filesystem_amiga.h"
#include "preferences.h"
#include "preferences_stdc.h"
#include "preferences_amiga.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/ntextd.h"
#include "main/values.h"
#include "main/functionlist.h"

Program::Program() :
    Console(nullptr), shellMode(false), ansiMode(false), status(0)
{
    Variables = new VariableList();
    Functions = new FunctionList();
    ins = new RealNumber();
#if defined(AMIGA)
    Language = new AmigaLanguage();
    Filesystem = new AmigaFilesystem();
    Preferences = new AmigaPreferences();
#else
    Language = new StandardLanguage();
    Filesystem = new StandardFilesystem();
    Preferences = new StandardPreferences();
#endif
    Input = new DecimalSystem(Preferences->GetDigits(), Language->GetFractionPoint());
    Output = new DecimalSystem(Preferences->GetDigits(), Language->GetFractionPoint());
}

Program::~Program()
{
    delete Variables;
    delete Functions;
    delete Filesystem;
    delete Output;
    delete Input;
    delete Language;
    delete ins;

    Preferences->Keep();
    delete Preferences;
}

void Program::NewPositionalInput(short unsigned int base, short unsigned int digits)
{
    delete Input;

    char fractionPoint = Language->GetFractionPoint();

    if (base == 10)
    {
        Input = new DecimalSystem(digits, fractionPoint);
    }
    else
    {
        Input = new PositionalNumeralSystem(base, digits, fractionPoint);
    }
}

void Program::NewPositionalOutput(short unsigned int base, short unsigned int digits)
{
    delete Output;

    char fractionPoint = Language->GetFractionPoint();

    if (base == 10)
    {
        Output = new DecimalSystem(digits, fractionPoint);
    }
    else
    {
        Output = new PositionalNumeralSystem(base, digits, fractionPoint);
    }
}

void Program::SetPrompt(const char* text) const
{
    if (Console != nullptr)
    {
        Console->SetPrompt(text);
    }
    Preferences->SetPrompt(text);
}

Number* Program::GetLastResult() const
{
    return ins;
}

void Program::SetLastResult(Number* number)
{
    delete ins;
    ins = number->Clone();
}

int Program::GetExitStatus() const
{
    return status;
}

void Program::InitAnsiMode()
{
    SetAnsiMode(ansiMode);
}

bool Program::GetAnsiMode() const
{
    return ansiMode;
}

void Program::SetAnsiMode(bool value)
{
    if (Console != nullptr)
    {
        bool success = Console->SetAnsiMode(value);
        if (!success)
        {
            Console->SetAnsiMode(ansiMode);
            return;
        }
    }

    if (Language != nullptr)
    {
        Language->SetAnsiMode(value);
    }

    ansiMode = value;
}

void Program::Exit()
{
    Console->Exit();
}
