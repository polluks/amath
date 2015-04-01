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
#include "lib/charbuf.h"
#include "system/preferences.h"
#include "system/preferences_stdc.h"

#ifndef AMIGA
#include <stdio.h>
#include <stdlib.h>

static const char *tempname = "/tmp/amath.prefs";
static const char *permname = "/usr/local/etc/amath.conf";

bool StandardPreferences::Load()
{
    FILE *file = fopen(tempname, "r");
    if (!file) {
        return false;
    }

    CharBuffer *text = new CharBuffer();
    text->Empty();

    const int bufsize = 64;
    char* buf = new char[bufsize];
    char* c;

    do {
        c = fgets(buf, bufsize, file);
        if (c != NULL) {
            text->Append(c);
        }
    } while (c != NULL);

    delete buf;
    fclose(file);
    SetPrefs(text->GetString());
    delete text;
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
    FILE *file = fopen(name, "w");
    if (!file) {
        return false;
    }

    char *out = GetDescription();
    fputs(out, file);
    fclose(file);
    return true;
}

#endif
