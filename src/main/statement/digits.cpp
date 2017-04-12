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
#include "digits.h"
#include "lib/real.h"
#include "lib/ntextd.h"
#include "loc/text.h"
#include "system/program.h"

/**
 * @brief Constructor used to show number of active digits.
 *
 */
DigitsStatement::DigitsStatement()
    : StatementNode()
{
    show = true;
    digits = 0;
}

/**
 * @brief Constructor used to show number of active digits.
 *
 */
DigitsStatement::DigitsStatement(unsigned int digits) :
    StatementNode(), digits(digits)
{
    show = false;
}

DigitsStatement::~DigitsStatement()
{
}

char* DigitsStatement::Execute()
{
    const char* text;

    if (!show)
    {
        Program->Input->SetDigits(digits);
        Program->Output->SetDigits(digits);
        Program->Preferences->SetDigits(digits);
        text = HELPDIGISETT;
    }
    else
    {
        text = HELPDIGISHOW;
        digits = Program->Output->GetDigits();
    }

    Number* d = new RealNumber(digits);
    NumeralSystem* ns = new DecimalSystem(2);
    const char* dtext = ns->GetText(d);
    delete d;

    output->Empty();
    output->EnsureSize(StrLen(text) + StrLen(dtext) + StrLen(NEWLINE) + 1);
    output->Append(text);
    output->Append(dtext);
    output->Append(NEWLINE);

    delete ns;
    return output->GetString();
}
