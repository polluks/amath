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
#include "localize/text.h"
#include "system/program.h"
#include "system/filesystem_amiga.h"

#ifdef AMIGA

/**
 * @brief
 *
 * http://en.wikibooks.org/wiki/Aros/Developer/Docs/Libraries/DOS#Examine_Files_or_Directories
 *
 */
CharBuffer* AmigaFilesystem::ListDirectory(const char *path)
{
    static const long int pathsize = 256;
    CharBuffer *pathbuf = new CharBuffer(pathsize);

    if (path == NOMEM) {
        if (GetCurrentDirName (pathbuf->GetString(), pathsize))
        {
            pathbuf->Append(path);
        } else {
            delete pathbuf;
            return NOMEM;
        }
    } else {
        pathbuf->EnsureSize(StrLen(path) + 1);
        pathbuf->Append(path);
    }

    BPTR lock;
    BOOL success;

    lock = Lock((STRPTR)pathbuf->GetString(), ACCESS_READ);

    if (!lock) {
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
    FileInfoBlock *info = new FileInfoBlock();
    success = Examine(lock, info);
    success = ExNext(lock, info);
    while (success != DOSFALSE)
    {
        if (first) {
            const char *header = TXTLISTDIRHEADER;
            lines->EnsureSize(StrLen(header) + 1);
            lines->Empty();
            lines->Append(header);
            first = false;
        }

        const char *type = NOMEM;
        if (info->fib_DirEntryType < 0) {
            type = TXTLISTDIRTFILE;
        } else {
            type = TXTLISTDIRTDIR;
        }

        const unsigned short colsize = 12;
        unsigned int a = StrLen(type) > colsize ? colsize : StrLen(type);
        unsigned int b = colsize - a;

        lines->EnsureGrowth(colsize + StrLen((char*)info->fib_FileName) + StrLen(NEWLINE) + 1);
        lines->Append(type);
        lines->Append(' ', b);
        lines->Append((char*)info->fib_FileName);
        lines->Append(NEWLINE);

        success = ExNext(lock, info);
    }

    UnLock(lock);
    delete pathbuf;
    return lines;
}

CharBuffer* AmigaFilesystem::LoadTextFile(const char* name)
{
    BPTR file = Open((char*)name, MODE_OLDFILE);
    if (!file) {
        return NOMEM;
    }

    CharBuffer *text = new CharBuffer();
    text->Empty();

    int blocks = 0;
    bool eof = false;
    LONG c;

    while (!eof) {
        blocks++;
        text->EnsureSize(blocksize, blocks);
        int count = 0;

        do
        {
            c = FGetC(file);
            eof = (c <= 0);

            if (!eof) {
                text->Append((char)c);
                count++;
            }
        }  while (!eof && count < blocksize);
    }

    Close(file);
    return text;
}

bool AmigaFilesystem::SaveTextFile(const char *name, const char *text)
{
    BPTR file = Open((char*)name, MODE_NEWFILE);

    if (!file) {
        return false;
    }

    char *i = (char*)text;
    LONG r = 1;
    while (r > 0 && *i) {
        r = FPutC(file, *i++);
    }

    Close(file);
    return true;
}

#endif
