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
#include "lib/charbuf.h"
#include "lib/aengine.h"

AnsiConoleEngine::AnsiConoleEngine()
{
    linebuf = new CharBuffer();
    out = new CharBuffer();

    lines = new char*[maxLines];

    for (int i = 0; i < maxLines; i++) {
        lines[i] = NOMEM;
    }

    editline = NOMEM;
    curline = -1;
}

AnsiConoleEngine::~AnsiConoleEngine()
{
    for (int i = 0; i < maxLines; i++) {
        if (lines[i] != NOMEM) {
            delete [] lines[i];
        }
    }

    delete [] lines;
    delete linebuf;
    delete out;
}

void AnsiConoleEngine::StartInput()
{
    linebuf->ClearAndAlloc(lineSize + 1);
    len = lineSize;
    cursor = linebuf->buf;
    endpos = cursor;
    *endpos = '\0';

    lineswap = false;
    escmode = false;
    csimode = false;
    delmode = false;
    linedone = false;
}

//#include <real.h>
//#include <numb.h>
//#include <ntext.h>

const char* AnsiConoleEngine::ProcessChar(const unsigned char character)
{
    unsigned char ch = character;
    out->Empty();

    /*
    // -------------- DEUG ------------------
    Number *d = new RealNumber((int)ch);
    NumeralSystem *ns = new DecimalSystem(0);
    const char *dtext = ns->GetText(d);
    StrCopy(out->buf, dtext);
    StrConcat(out->buf, SPACE);
    delete ns;
    delete d;
    return out->buf;
    // -------------- DEUG ------------------
    */

    if (len == 0) {
        // TODO: double buffer
    }

    bool processed = false;

    if (ch == 0) {
        processed = true;
    } else if (ch == 27) {
        escmode = true;
        processed = true;
    } else if (ch == 155 || (escmode && ch == 91)) {
        csimode = true;
        processed = true;
    } else if (csimode) {
        switch (ch) {
        case 65: // Arrow up (27 91 65)
            ShowLast();
            break;
        case 66: // Arrow down (27 91 66)
            ShowNext();
            break;
        case 67: // Arrow right (27 91 67)
            if (cursor != endpos) {
                cursor++;
                out->Append(CURSORFORWARD);
            }
            break;
        case 68: // Arrow left (27 91 68)
            if (cursor != linebuf->buf) {
                cursor--;
                out->Append(CURSORBACKWARD);
            }
            break;
        case 51: // DEL         27 91 51 126
            delmode = true;
        default:
            // F1          27 79 80
            // F2          27 79 81
            break;
        }

        escmode = false;
        csimode = false;
        processed = true;
    } else {
        escmode = false;
        csimode = false;
    }

    // Delete one character to the right
    if (delmode && ch == 126) {
        if (cursor != endpos) {
            char *i = cursor;
            do {
                *i = *(i + 1);
                i++;
            } while (i != endpos);

            len++;
            out->Append(DELETE1CHAR);
            endpos--;
            linebuf->ptr = endpos;
        }

        processed = true;
        delmode = false;
    }

    if (processed) {
        return out->GetString();
    }

    if (ch == 13 || ch == 10) {
        out->Append(NEWLINE);
        linebuf->ptr = endpos;
        CopyLine();
        linedone = true;
    } else if (cursor != linebuf->buf && (ch == 8 || ch == 127)) {
        // Deleting in middle of line
        if (cursor != endpos) {
            char *i = cursor - 1;
            do {
                *i = *(i + 1);
                i++;
            } while (i != endpos);

        }

        len++;
        out->Append(CURSORBACKWARD);
        out->Append(DELETE1CHAR);
        cursor--;
        endpos--;
        linebuf->ptr = endpos;
    } else if (ch >= 32 && ch <= 126) {
        // Insert in middle of line
        if (cursor != endpos) {
            char *i = endpos;
            do {
                *i = *(i - 1);
                i--;
            } while (i != cursor);
            out->Append(INSERT1CHAR);
        }

        len--;
        out->Append(ch);
        *cursor++ = ch;
        endpos++;
        linebuf->ptr = endpos;
    }

    return out->GetString();
}

void AnsiConoleEngine::CopyLine()
{
    curline++;

    if (curline == maxLines) {
        curline--;

        delete [] lines[0];
        for (int i = 0; i < maxLines - 1; i++) {
            lines[i] = lines[i + 1];
        }
    }

    AllocAndCopy(&(lines[curline]), linebuf->GetString());

    if (editline != NOMEM) {
        delete [] editline;
        editline = NOMEM;
    }
}

void AnsiConoleEngine::ShowLast()
{
    if (curline == -1) {
        return;
    }

    if (!lineswap) {
        AllocAndCopy(&editline, linebuf->GetString());
        lineswap = true;
        showline = curline + 1;
    } else if (showline == curline + 1) {
        delete editline;
        AllocAndCopy(&editline, linebuf->GetString());
    }

    showline--;
    if (showline < 0) {
        showline = 0;
    }

    out->Empty();
    out->EnsureSize(
        StrLen(DELETELINE) +
        StrLen(PROMPT) +
        StrLen(lines[showline]) + 1);

    out->Append(DELETELINE);
    out->Append(PROMPT);
    out->Append(lines[showline]);

    linebuf->Empty();
    linebuf->EnsureSize(StrLen(lines[showline]));
    linebuf->Append(lines[showline]);

    unsigned int linelen = StrLen(linebuf->GetString());
    cursor = linebuf->buf + linelen;
    endpos = cursor;
    len = lineSize - linelen;
}

void AnsiConoleEngine::ShowNext()
{
    if (!lineswap) {
        return;
    }

    showline++;
    if (showline > curline + 1) {
        showline = curline + 1;
        return;
    }

    out->Empty();
    out->Append(DELETELINE);
    out->Append(PROMPT);

    if (showline > curline) {
        out->EnsureGrowth(StrLen(editline) + 1);
        out->Append(editline);

        linebuf->Empty();
        linebuf->EnsureSize(StrLen(editline));
        linebuf->Append(editline);
    } else {
        out->EnsureGrowth(StrLen(lines[showline]) + 1);
        out->Append(lines[showline]);

        linebuf->Empty();
        linebuf->EnsureSize(StrLen(lines[showline]));
        linebuf->Append(lines[showline]);
    }

    unsigned int linelen = StrLen(linebuf->GetString());
    cursor = linebuf->buf + linelen;
    endpos = cursor;
    len = lineSize - linelen;
}

bool AnsiConoleEngine::InputDone()
{
    return linedone;
}

const char* AnsiConoleEngine::GetLine()
{
    return linebuf->GetString();
}
