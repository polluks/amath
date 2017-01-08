/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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
    lastText = NOMEM;
    keywordsloc = NOMEM;
    keywordcount = sizeof(keywords) / sizeof(keyworddef);
    textcount = sizeof(textdefs) / sizeof(textdef);
    identcount = sizeof(identtexts) / sizeof(identhelpdef);
    helpcount = sizeof(helptexts) / sizeof(helptextdef);
    aliascount = sizeof(identaliases) / sizeof(identalias);
}

Language::~Language()
{
    if (lastText != NOMEM) {
        delete lastText;
    }

    if (keywordsloc != NOMEM) {
        delete [] keywordsloc;
    }
}

char* Language::FindAlias(const char* ident)
{
    for (unsigned int i = 0; i < aliascount; i++) {
        if (StrIsEqual(identaliases[i].ident, ident)) {
            return (char*)identaliases[i].alias;
        }
    }
    return (char*)ident;
}

Symbol Language::FindKeyword(const char* ident)
{
    for (unsigned int i = 0; i < keywordcount; i++) {
        if (
            Program->Language->StrIsEqualLoc(keywords[i].name, ident) ||
            (keywordsloc != NULL &&
             Program->Language->StrIsEqualLoc(keywordsloc[i].name, ident))) {
            return keywords[i].symbol;
        }
    }
    return (Symbol)0;
}

char* Language::GetText(int id)
{
    textdef *def = NOMEM;
    for (unsigned int i = 0; i < textcount; i++) {
        if (textdefs[i].id == id) {
            def = (textdef*)&textdefs[i];
            break;
        }
    }

    if (def == NOMEM) {
        return (char*)(HELPNOHELP);
    }

    char *text = Translate(def);
    char *untagged = UntagText(text);
    return untagged;
}

char* Language::GetHelpText(char* ident)
{
    char *s = FindAlias(ident);
    identhelpdef *def = NOMEM;
    for (unsigned int i = 0; i < identcount; i++) {
        if (StrIsEqual(identtexts[i].ident, s)) {
            def = (identhelpdef*)&identtexts[i];
            break;
        }
    }

    if (def == NOMEM) {
        return (char*)(HELPNOHELP);
    }

    char *text = Translate(def);
    char *untagged = UntagText(text);
    return untagged;
}

char* Language::GetHelpText(Symbol symbol)
{
    helptextdef *def = NOMEM;
    for (unsigned int i = 0; i < helpcount; i++) {
        if (helptexts[i].symbol == symbol) {
            def = (helptextdef*)&helptexts[i];
            break;
        }
    }

    if (def == NOMEM) {
        return (char*)(HELPNOHELP);
    }

    char *text = Translate(def);
    char *untagged = UntagText(text);
    return untagged;
}

char* Language::UntagText(const char* text)
{
    if (lastText != NOMEM) {
        delete lastText;
        lastText = NULL;
    }

    if (text == NOMEM) {
        return NOMEM;
    }

    unsigned int count = sizeof(texttags) / sizeof(texttag);
    char *untagged = new char[StrLen(text) * 2];
    Untag(untagged, text, (texttag*)texttags, count);

    unsigned int len = StrLen(untagged) + 1;
    lastText = new char[len];
    MemCopy(lastText, untagged, len);
    delete [] untagged;

    return lastText;
}
