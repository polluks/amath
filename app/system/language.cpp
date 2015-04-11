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
#include "localize/tags.h"
#include "localize/ialias.h"
#include "system/language.h"

Language::Language()
{
    lastText = NOMEM;
}

Language::~Language()
{
    if (lastText != NOMEM) {
        delete lastText;
    }
}

char* Language::FindAlias(const char* ident)
{
    static const unsigned int count = sizeof(identaliases) / sizeof(identalias);
    for (unsigned int i = 0; i < count; i++) {
        if (StrIsEqual(identaliases[i].ident, ident)) {
            return (char*)identaliases[i].alias;
        }
    }

    return (char*)ident;
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
    delete untagged;

    return lastText;
}