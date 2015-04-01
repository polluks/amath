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

#include "clib.h"
#include "lib/numb.h"
#include "lib/ntext.h"
#include "main/values.h"
#include "main/functions.h"
#include "system/program.h"
#include "system/base/io.h"

Program::Program()
{
    Variables = new VariableList();
    Functions = new FunctionList();
    Graphs = new GraphList();
    ins = new RealNumber();

    Preferences = CreatePreferences();
    Preferences->Load();

    Language = CreateLanguage();
    Input = new DecimalSystem(Preferences->GetDigits(), Language->GetFractionPoint());
    Output = new DecimalSystem(Preferences->GetDigits(), Language->GetFractionPoint());
    Filesystem = CreateFilesystem();
}

Program::~Program()
{
    delete Variables;
    delete Functions;
    delete Graphs;
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

    char fractionpoint = Language->GetFractionPoint();

    if (base == 10) {
        Input = new DecimalSystem(digits, fractionpoint);
    } else {
        Input = new PositionalNumeralSystem(base, digits, fractionpoint);
    }
}

void Program::NewPositionalOutput(short unsigned int base, short unsigned int digits)
{
    delete Output;

    char fractionpoint = Language->GetFractionPoint();

    if (base == 10) {
        Output = new DecimalSystem(digits, fractionpoint);
    } else {
        Output = new PositionalNumeralSystem(base, digits, fractionpoint);
    }
}

Number* Program::GetLastResult()
{
    return ins;
}

void Program::SetLastResult(Number *number)
{
    if (ins == number) {
        return;
    }

    delete ins;
    ins = number->Clone();
}
