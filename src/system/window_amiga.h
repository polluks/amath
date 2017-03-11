/*-
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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#ifndef AMATH_AMIGA_CONSOLE_WINDOW_H
#define AMATH_AMIGA_CONSOLE_WINDOW_H

/**
 * @file  window_amiga.h
 * @brief Amiga OS specific console window.
 *
 * https://github.com/weiju/amiga-stuff/blob/master/os13/intuition1.c
 */

#include "amath.h"
#include "amathc.h"
#include "console.h"
#include "lib/aengine.h"

#ifdef AMIGA
#include <libraries/dos.h>
#include <devices/console.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <intuition/intuition.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>

#if defined(AOSSMALL)
#define WWIDTH 480
#define WHEIGHT 150
#else
#define WWIDTH 620
#define WHEIGHT 350
#endif

typedef union
{
    IORequest *st;
    IOStdReq  *io;
    Message   *msg;
} STRequest;

typedef union
{
    IntuiMessage *imsg;
    Message   *msg;
} STMessage;

/**
 * @brief Encapsulates the logic of an amiga console device.
 *
 */
class AmigaWindow : public ConsoleBase {
public:
    AmigaWindow(const char *prompt, CharValidator *validator);
    ~AmigaWindow();

    int GetStackSize();
    void Run();
    void Exit();
    void SetPrompt(const char *string);
    void WriteString(const char *string);

private:
    void Create();
    void ReadLine();
    void WriteChar(const char character);
    void WriteString(const char *string, unsigned int length);
    unsigned char TryGetChar(MsgPort *msgport);
    unsigned char ReadChar(STRequest request);
    void Cleanup();

    Window    *window;
    MsgPort   *writeport;
    MsgPort   *readport;
    STRequest writereq;
    STRequest readreq;

    bool exit;
    bool succeed;
    bool openconsole;
    unsigned char inputbuf;
    unsigned long windowsig;
    AnsiConoleEngine *proc;
    const char *line;

//AmigaMenu *menu;
};

#endif
#endif
