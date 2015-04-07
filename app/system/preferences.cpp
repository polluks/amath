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
#include "text.h"
#include "ansicon.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/ntext.h"
#include "lib/charbuf.h"
#include "main/nodes.h"
#include "main/parser.h"
#include "system/preferences.h"

PreferencesBase::PreferencesBase()
{
    buf = new CharBuffer();
    SetDefaults();
}

PreferencesBase::~PreferencesBase()
{
    delete buf;
    delete prompt;
}

void PreferencesBase::SetDefaults()
{
    AllocAndCopy(&this->prompt, ">>> ");
    digits = 9;
}

char* PreferencesBase::GetDescription()
{
    static const char *promptq = "\"";
    static const char *sprompt = "prompt";
    static const char *sdigits  = "digits";

    Number *d = new RealNumber(GetDigits());
    NumeralSystem *ns = new DecimalSystem(2);
    const char *dtext = ns->GetText(d);
    delete d;

    buf->Empty();
    buf->EnsureSize(
        StrLen(sprompt) + StrLen(SPACE) + StrLen(promptq) +
        StrLen(prompt) + StrLen(promptq) + StrLen(NEWLINE) +
        StrLen(sdigits) + StrLen(SPACE) + StrLen(dtext) +
        StrLen(NEWLINE) + 1);

    buf->Append(sprompt);
    buf->Append(SPACE);
    buf->Append(promptq);
    buf->Append(prompt);
    buf->Append(promptq);
    buf->Append(NEWLINE);
    buf->Append(sdigits);
    buf->Append(SPACE);
    buf->Append(dtext);
    buf->Append(NEWLINE);

    delete ns;
    return buf->GetString();
}

void PreferencesBase::SetPrefs(char* prefs)
{
    Parser *parser = new Parser(prefs);
    SyntaxNode *node = parser->Parse();
    delete parser;
    node->Execute();
    delete node;
}

char* PreferencesBase::GetPrompt()
{
    return prompt;
}

void PreferencesBase::SetPrompt(const char* prompt)
{
    delete this->prompt;
    AllocAndCopy(&this->prompt, prompt);
}

int PreferencesBase::GetDigits()
{
    return digits;
}

void PreferencesBase::SetDigits(int digits)
{
    this->digits = digits;
}
