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


#include "def/libc.h"
#include "def/text.h"
#include "io/filesystem.h"
#include "lib/charbuf.h"
#include "arc/stdc/cfilesystem.h"

#ifndef AMIGA
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

CharBuffer* StandardFilesystem::ListDirectory(const char *path)
{
    CharBuffer *pathbuf = new CharBuffer();
    pathbuf->Empty();

    if (path == NOMEM) {
        pathbuf->Append(".");
    } else {
        pathbuf->EnsureSize(StrLen(path) + 1);
        pathbuf->Append(path);
    }

    DIR *dir;
    if ((dir = opendir(pathbuf->GetString())) == NULL) {
        CharBuffer *res = new CharBuffer();
        const char *msg = MSGNODIR;
        res->EnsureSize(StrLen(msg) + StrLen(pathbuf->GetString()) + StrLen(NEWLINE) + 1);
        res->Empty();
        res->Append(msg);
        res->Append(pathbuf->GetString());
        res->Append(NEWLINE);

        delete pathbuf;
        return res;
    }

    CharBuffer *lines = new CharBuffer();
    lines->Empty();

    bool first = true;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (StrIsEqual(entry->d_name, ".") || StrIsEqual(entry->d_name, "..")) {
            continue;
        }

        if (first) {
            const char *header = TXTLISTDIRHEADER;
            lines->EnsureSize(StrLen(header) + 1);
            lines->Empty();
            lines->Append(header);
            first = false;
        }

        const char *type;

        switch (entry->d_type) {
        case DT_REG:
            type = TXTLISTDIRTFILE;
            break;
        case DT_DIR:
            type = TXTLISTDIRTDIR;
            break;
        default:
            type = TXTLISTDIRTUNKNOWN;
        }

        const unsigned short colsize = 12;
        unsigned int a = StrLen(type) > colsize ? colsize : StrLen(type);
        unsigned int b = colsize - a;

        lines->EnsureGrowth(colsize + StrLen(entry->d_name) + StrLen(NEWLINE) + 1);
        lines->Append(type);
        lines->Append(' ', b);
        lines->Append(entry->d_name);
        lines->Append(NEWLINE);
    }

    closedir(dir);
    delete pathbuf;
    return lines;
}

CharBuffer* StandardFilesystem::LoadTextFile(const char* name)
{
    FILE *file = fopen(name, "r");
    if (!file) {
        return NOMEM;
    }

    CharBuffer *text = new CharBuffer();
    text->Empty();

    int blocks = 0;
    bool eof = false;

    while (!eof) {
        blocks++;
        text->EnsureSize(blocksize, blocks);
        int count = 0;

        do
        {
            int c = fgetc(file);
            eof = c == EOF;

            if (!eof) {
                text->Append((char)c);
                count++;
            }
        }  while (!eof && count < blocksize);
    }

    fclose(file);
    return text;
}

bool StandardFilesystem::SaveTextFile(const char *name, const char *text)
{
    FILE *file = fopen(name, "w");
    if (!file) {
        return false;
    }

    char *i = (char*)text;
    int r = EOF + 11;
    while (r != EOF && *i) {
        r = fputc(*i++, file);
    }

    fclose(file);
    return true;
}

#endif
