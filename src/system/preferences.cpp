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
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/ntext.h"
#include "lib/charbuf.h"
#include "main/lexer.h"
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
    AllocAndCopy(&this->prompt, "> ");
    digits = 9;
    refactorNames = false;
}

char* PreferencesBase::GetDescription() const
{
    static char* promptkw = Lexer::FindKeyword(symprompt);
    static char* digitkw = Lexer::FindKeyword(symdigits);
    static char delimiter = *(Lexer::FindKeyword(symdelimiter));
    static char promptq = '"';

    Number* d = new RealNumber(GetDigits());
    NumeralSystem* ns = new DecimalSystem(2);
    const char* dtext = ns->GetText(d);
    delete d;

    buf->Empty();
    buf->EnsureSize(
        StrLen(promptkw) + sizeof(SPACE) + sizeof(promptq) +
        StrLen(prompt) + sizeof(promptq) + sizeof(delimiter) +
        StrLen(digitkw) + sizeof(SPACE) + StrLen(dtext) + sizeof(delimiter) + sizeof(char));

    buf->Append(promptkw);
    buf->Append(SPACE);
    buf->Append(promptq);
    buf->Append(prompt);
    buf->Append(promptq);
    buf->Append(delimiter);
    buf->Append(digitkw);
    buf->Append(SPACE);
    buf->Append(dtext);
    buf->Append(delimiter);

    delete ns;
    return buf->GetString();
}

void PreferencesBase::SetPrefs(char* prefs)
{
    if (prefs == nullptr)
    {
        return;
    }

    Parser* parser = new Parser(prefs);
    SyntaxNode* node = parser->Parse();
    delete parser;
    node->Execute();
    delete node;
}

char* PreferencesBase::GetPrompt() const
{
    return prompt;
}

void PreferencesBase::SetPrompt(const char* prompt)
{
    delete this->prompt;
    AllocAndCopy(&this->prompt, prompt);
}

int PreferencesBase::GetDigits() const
{
    return digits;
}

void PreferencesBase::SetDigits(int digits)
{
    this->digits = digits;
}

bool PreferencesBase::GetRefactorNames()
{
    return refactorNames;
}

void PreferencesBase::SetRefactorNames(bool yes)
{
    refactorNames = yes;
}
