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
#include "program.h"
#include "filesystem_amiga.h"
#include "lib/charbuf.h"
#include "loc/text.h"

#if defined(AMIGA)
#include <clib/dos_protos.h>

/**
 * @brief
 * http://en.wikibooks.org/wiki/Aros/Developer/Docs/Libraries/DOS#Examine_Files_or_Directories
 */
CharBuffer* AmigaFilesystem::ListDirectory(const char* path)
{
    static const long int pathsize = 256;
    CharBuffer* pathbuf = new CharBuffer(pathsize);

    if (path == nullptr)
    {
        if (GetCurrentDirName(pathbuf->GetString(), pathsize))
        {
            pathbuf->Append(path);
        }
        else
        {
            delete pathbuf;
            return nullptr;
        }
    }
    else
    {
        pathbuf->EnsureSize(StrLen(path) + 1);
        pathbuf->Append(path);
    }

    BPTR lock;
    BOOL success;

    lock = Lock((STRPTR)pathbuf->GetString(), ACCESS_READ);

    if (!lock)
    {
        CharBuffer* res = new CharBuffer();
        const char* msg = MSGNODIR;
        res->EnsureSize(StrLen(msg) + StrLen(pathbuf->GetString()) + StrLen(NEWLINE) + 1);
        res->Empty();
        res->Append(msg);
        res->Append(pathbuf->GetString());
        res->Append(NEWLINE);

        delete pathbuf;
        return res;
    }

    CharBuffer* lines = new CharBuffer();
    lines->Empty();

    bool first = true;
    FileInfoBlock* info = new FileInfoBlock();
    success = Examine(lock, info);
    success = ExNext(lock, info);
    while (success)
    {
        if (first)
        {
            const char* header = TXTLISTDIRHEADER;
            lines->EnsureSize(StrLen(header) + 1);
            lines->Empty();
            lines->Append(header);
            first = false;
        }

        const char* type;
        if (info->fib_DirEntryType < 0)
        {
            type = TXTLISTDIRTFILE;
        }
        else
        {
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
    BPTR file = Open(const_cast<char*>(name), MODE_OLDFILE);
    if (!file)
    {
        return nullptr;
    }

    CharBuffer* text = new CharBuffer();
    text->Empty();

    int blocks = 0;
    bool eof = false;
    LONG c;

    while (!eof)
    {
        blocks++;
        text->EnsureSize(blocksize, blocks);
        int count = 0;

        do
        {
            c = FGetC(file);
            eof = (c <= 0);

            if (!eof)
            {
                text->Append(static_cast<char>(c));
                count++;
            }
        }
        while (!eof && count < blocksize);
    }

    Close(file);
    return text;
}

bool AmigaFilesystem::SaveTextFile(const char* name, const char* text)
{
    BPTR file = Open(const_cast<char*>(name), MODE_NEWFILE);

    if (!file)
    {
        return false;
    }

    char* i = const_cast<char*>(text);
    LONG r = 1;
    while (r > 0 && *i)
    {
        r = FPutC(file, *i++);
    }

    Close(file);
    return true;
}

#endif
