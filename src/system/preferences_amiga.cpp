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
#include "lib/charbuf.h"
#include "system/preferences.h"
#include "system/preferences_amiga.h"

#ifdef AMIGA
#include <clib/dos_protos.h>

static const char *tempname = "ENV:amath.prefs";
static const char *permname = "ENVARC:amath.prefs";

bool AmigaPreferences::Load()
{
    BPTR file = Open((char*)tempname, MODE_OLDFILE);
    if (!file) {
        return false;
    }

    CharBuffer *text = new CharBuffer();
    text->Empty();

    const int bufsize = 64;
    char* buf = new char[bufsize];
    char* c;
    int s = 1;

    do {
        c = FGets(file, buf, bufsize);
        if (c != NULL) {
            text->EnsureSize(s++);
            text->Append(c);
        }
    } while (c != NULL);

    delete [] buf;
    Close(file);
    SetPrefs(text->GetString());
    delete text;
    return (IoErr() == 0);
}

bool AmigaPreferences::Keep()
{
    return SavePrefs(tempname);
}

bool AmigaPreferences::Save()
{
    return SavePrefs(permname);
}

bool AmigaPreferences::SavePrefs(const char* name)
{
    BPTR file = Open((CONST_STRPTR)name, MODE_NEWFILE);

    if (!file) {
        return false;
    }

    char *out = GetDescription();
    FPuts(file, (CONST_STRPTR)out);
    Close(file);
    return (IoErr() == 0);
}

#endif