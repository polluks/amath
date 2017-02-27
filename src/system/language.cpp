/*
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
 */

#include "amath.h"
#include "amathc.h"
#include "localize/lex.h"
#include "localize/help.h"
#include "localize/kword.h"
#include "localize/ident.h"
#include "localize/text.h"
#include "localize/tags.h"
#include "localize/ialias.h"
#include "system/language.h"
#include "system/program.h"

Language::Language()
{
    lastText = nullptr;
    keywordsloc = nullptr;
    keywordcount = sizeof(keywords) / sizeof(keyworddef);
    textcount = sizeof(textdefs) / sizeof(textdef);
    identcount = sizeof(identtexts) / sizeof(identhelpdef);
    helpcount = sizeof(helptexts) / sizeof(helptextdef);
    aliascount = sizeof(identaliases) / sizeof(identalias);
}

Language::~Language()
{
    if (lastText != nullptr)
    {
        delete lastText;
    }

    if (keywordsloc != nullptr)
    {
        delete [] keywordsloc;
    }
}

char* Language::FindAlias(const char* ident) const
{
    for (unsigned int i = 0; i < aliascount; i++)
    {
        if (StrIsEqual(identaliases[i].ident, ident))
        {
            return const_cast<char*>(identaliases[i].alias);
        }
    }

    return const_cast<char*>(ident);
}

Symbol Language::FindKeyword(const char* ident) const
{
    for (unsigned int i = 0; i < keywordcount; i++)
    {
        if (Program->Language->StrIsEqualLoc(keywords[i].name, ident) ||
            (keywordsloc != nullptr && Program->Language->StrIsEqualLoc(keywordsloc[i].name, ident)))
        {
            return keywords[i].symbol;
        }
    }

    return static_cast<Symbol>(0);
}

char* Language::GetText(int id)
{
    textdef* def = nullptr;
    for (unsigned int i = 0; i < textcount; i++)
    {
        if (textdefs[i].id == id)
        {
            def = (textdef*)&textdefs[i];
            break;
        }
    }

    if (def == nullptr)
    {
        return (char*)(HELPNOHELP);
    }

    char* text = Translate(def);
    char* untagged = UntagText(text);
    return untagged;
}

char* Language::GetHelpText(char* ident)
{
    char* s = FindAlias(ident);
    identhelpdef* def = nullptr;
    for (unsigned int i = 0; i < identcount; i++)
    {
        if (StrIsEqual(identtexts[i].ident, s))
        {
            def = (identhelpdef*)&identtexts[i];
            break;
        }
    }

    if (def == nullptr)
    {
        return (char*)(HELPNOHELP);
    }

    char* text = Translate(def);
    char* untagged = UntagText(text);
    return untagged;
}

char* Language::GetHelpText(Symbol symbol)
{
    helptextdef* def = nullptr;
    for (unsigned int i = 0; i < helpcount; i++)
    {
        if (helptexts[i].symbol == symbol)
        {
            def = (helptextdef*)&helptexts[i];
            break;
        }
    }

    if (def == nullptr)
    {
        return (char*)(HELPNOHELP);
    }

    char* text = Translate(def);
    char* untagged = UntagText(text);
    return untagged;
}

char* Language::UntagText(const char* text)
{
    if (lastText != nullptr)
    {
        delete lastText;
        lastText = nullptr;
    }

    if (text == nullptr)
    {
        return nullptr;
    }

    unsigned int count = sizeof(texttags) / sizeof(texttag);
    char* untagged = new char[StrLen(text) * 2];
    Untag(untagged, text, (texttag*)texttags, count);

    unsigned int len = StrLen(untagged) + 1;
    lastText = new char[len];
    MemCopy(lastText, untagged, len);
    delete [] untagged;

    return lastText;
}

bool Language::CharIsQuote(unsigned long character)
{
    return (character == '"');
}

bool Language::CharIsOperator(unsigned long character)
{
    static const unsigned int count = sizeof(operators) / sizeof(operatordef);
    for (unsigned int i = 0; i < count; i++)
    {
        if (operators[i].chr == (char)character)
        {
            return true;
        }
    }

    return false;
}