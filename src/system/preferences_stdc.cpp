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
#include "lib/charbuf.h"
#include "preferences.h"
#include "preferences_stdc.h"

#if !defined(AMIGA)
#include <stdio.h>
#include <stdlib.h>

#if defined(UNIX)
static const char *tempname = "/tmp/amath.prefs";
static const char *permname = "/usr/local/etc/amath.conf";
#elif defined(HAIKU)
static const char *tempname = "/tmp/amath.prefs";
static const char *permname = "~/config/settings/amath/amath.conf";
#else
static const char* tempname = "amath.prefs";
static const char* permname = "amath.conf";
#endif

bool StandardPreferences::Load()
{
#if defined(UNIX) && defined(HAIKU)
    FILE *file = fopen(tempname, "r");
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
        c = fgets(buf, bufsize, file);
        if (c != nullptr) {
            text->EnsureSize(s++);
            text->Append(c);
        }
    } while (c != nullptr);

    delete [] buf;
    fclose(file);
    SetPrefs(text->GetString());
    delete text;
#endif
    return true;
}

bool StandardPreferences::Keep()
{
    return SavePrefs(tempname);
}

bool StandardPreferences::Save()
{
    return SavePrefs(permname);
}

bool StandardPreferences::SavePrefs(const char* name)
{
#if defined(UNIX) && defined(HAIKU)
    FILE *file = fopen(name, "w");
    if (!file) {
        return false;
    }

    char *out = GetDescription();
    fputs(out, file);
    fclose(file);
#endif
    return true;
}

#endif
