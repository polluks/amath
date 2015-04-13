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
#include "localize/lex.h"
#include "localize/tags.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/ident.h"
#include "localize/kword.h"
#include "system/program.h"
#include "system/language_stdc.h"

StandardLanguage::StandardLanguage()
{ }

StandardLanguage::~StandardLanguage()
{ }

Symbol StandardLanguage::FindKeyword(const char* ident)
{
    static const unsigned int count = sizeof(keywords) / sizeof(keyworddef);
    for (unsigned int i = 0; i < count; i++) {
        if (Program->Language->StrIsEqualLoc(keywords[i].name, ident)) {
            return keywords[i].symbol;
        }
    }

    return (Symbol)0;
}

char* StandardLanguage::GetText(int id)
{
    const char *text = NOMEM;
    static const unsigned int count = sizeof(textdefs) / sizeof(textdef);
    for (unsigned int i = 0; i < count; i++) {
        if (textdefs[i].id == id) {
            text = textdefs[i].text;
            break;
        }
    }
    char *untagged = UntagText(text);
    return (char*)(untagged != NOMEM ? untagged : HELPNOHELP);
}

char* StandardLanguage::GetHelpText(char* ident)
{
    const char *text = NOMEM;
    static const unsigned int count = sizeof(identtexts) / sizeof(identhelpdef);
    for (unsigned int i = 0; i < count; i++) {
        if (StrIsEqual(identtexts[i].ident, ident)) {
            text = identtexts[i].text;
            break;
        }
    }
    char *untagged = UntagText(text);
    return (char*)(untagged != NOMEM ? untagged : HELPNOHELP);
}

char* StandardLanguage::GetHelpText(Symbol symbol)
{
    const char *text = NOMEM;
    static const unsigned int count = sizeof(helptexts) / sizeof(helptextdef);
    for (unsigned int i = 0; i < count; i++) {
        if (helptexts[i].symbol == symbol) {
            text = helptexts[i].text;
            break;
        }
    }
    char *untagged = UntagText(text);
    return (char*)(untagged != NOMEM ? untagged : HELPNOHELP);
}

char StandardLanguage::GetFractionPoint()
{
    return '.';
}

bool StandardLanguage::CharIsAlNum(long unsigned int character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9');
}

bool StandardLanguage::CharIsAlpha(long unsigned int character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z');
}

bool StandardLanguage::CharIsDigit(long unsigned int character)
{
    return (character >= '0' && character <= '9');
}

bool StandardLanguage::CharIsPunct(long unsigned int character)
{
    return (character == '.');
}

bool StandardLanguage::CharIsSpace(long unsigned int character)
{
    return (character == 32);
}

bool StandardLanguage::CharIsCntrl(long unsigned int character)
{
    return (character < 32 || character > 125);
}

bool StandardLanguage::StrIsEqualLoc(const char* s1, const char* s2)
{
    return StrIsEqual(s1, s2);
}
