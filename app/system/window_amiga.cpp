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
#include "lib/aengine.h"
#include "localize/start.h"
#include "main/evaluator.h"
#include "system/window_amiga.h"
#include "system/base/io.h"

#ifdef AMIGA
#include <exec/types.h>
#include <exec/io.h>
#include <exec/memory.h>
#include <libraries/dos.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <devices/console.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>
struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

AmigaWindow::AmigaWindow(const char *prompt) :
    ConsoleBase(prompt)
{
    proc = new AnsiConoleEngine(prompt);
    window = NULL;
    //menu = NULL;
    writereq.st = NULL;
    writeport = NULL;
    readreq.st = NULL;
    readport = NULL;
    succeed = false;
    openconsole = false;

    intuitionBase = (struct IntuitionBase*)OpenLibrary(INTUITION_NAME, INTUITION_REV);
    IntuitionBase = intuitionBase;
    gfxBase = (struct GfxBase*)OpenLibrary(GRAPHICS_NAME, GRAPHICS_REV);
    GfxBase = gfxBase;
}

AmigaWindow::~AmigaWindow()
{
    Cleanup();

    if (gfxBase) {
        CloseLibrary((Library*)gfxBase);
    }

    if (intuitionBase) {
        CloseLibrary((Library*)intuitionBase);
    }

    delete proc;
}

int AmigaWindow::GetStackSize()
{
    return 100000;
}

void AmigaWindow::Create()
{
    NewWindow nw = {
        10, 20,               // left, top
        WWIDTH, WHEIGHT,      // width, height
        (UBYTE)-1, (UBYTE)-1, // detailpen, blockpen
        IDCMP_CLOSEWINDOW |
        IDCMP_MENUPICK,
        WFLG_SIZEGADGET |
        WFLG_DRAGBAR |
        WFLG_DEPTHGADGET |
        WFLG_CLOSEGADGET |
        WFLG_ACTIVATE |
        WFLG_SMART_REFRESH,
        NULL, NULL,           // user gadgets, user checkmark
        (UBYTE*) ATITLE,      // title
        NULL, NULL,           // window screen, super bitmap
        400, 75,              // min width, height
        1600, 1050,           // max width, height
        WBENCHSCREEN          // open on workbench screen
    };

    succeed = intuitionBase != NULL && gfxBase != NULL;
    succeed = succeed && (writeport = CreatePort(PORTCR, 0)) != 0;
    succeed = succeed && (readport = CreatePort(PORTCW, 0)) != 0;
    succeed = succeed && (writereq.st = CreateExtIO(writeport, sizeof(IOStdReq))) != 0;
    succeed = succeed && (readreq.st = CreateExtIO(readport, sizeof(IOStdReq))) != 0;
    succeed = succeed && (window = OpenWindow(&nw)) != 0;
    if (!succeed) return;

    windowsig = 1 << window->UserPort->mp_SigBit;
    writereq.io->io_Data = (APTR) window;
    writereq.io->io_Length = sizeof(Window);

    openconsole = OpenDevice(DEVCONSOLE, 0, writereq.st, 0) == 0;
    succeed = openconsole;
    if (!openconsole) return;

    readreq.st->io_Device = writereq.st->io_Device;
    readreq.st->io_Unit   = writereq.st->io_Unit;

    // Queue input
    ReadChar(readreq);

    // Do GUI stuff
    //menu = new AmigaMenu(window);
    //menu->Attach();
}

void AmigaWindow::Cleanup()
{
    if(openconsole) {
        if (readreq.st) {
            AbortIO(readreq.st);
            WaitIO(readreq.st);
        }

        CloseDevice(writereq.st);
        openconsole = false;
    }

    if(readreq.st) {
        DeleteExtIO(readreq.st);
        readreq.st = NULL;
    }

    if(readport) {
        DeletePort(readport);
        readport = NULL;
    }

    if(writereq.st) {
        DeleteExtIO(writereq.st);
        writereq.st = NULL;
    }

    if(writeport) {
        DeletePort(writeport);
        writeport = NULL;
    }

    //if (menu) {
    //    delete menu;
    //    menu = NULL;
    //}

    if(window) {
        CloseWindow(window);
        window = NULL;
    }
}

void AmigaWindow::Run()
{
    Create();
    StartMessage();
    exit = false;

    while(!exit) {
        Prompt();
        ReadLine();
        Evaluator *evaluator = new Evaluator(line);
        evaluator->Evaluate();
        const char *out = evaluator->GetResult();
        WriteString(out, StrLen(out));
        delete evaluator;
    }

    Cleanup();
}

void AmigaWindow::Exit()
{
    exit = true;
}

void AmigaWindow::ReadLine()
{
    unsigned long conreadsig = 1L << readport->mp_SigBit;
    proc->StartInput();

    while(!proc->InputDone() && !exit)
    {
        unsigned long signals = Wait(conreadsig | windowsig);

        if (signals & conreadsig)
        {
            unsigned char ch = TryGetChar(readport);
            if (ch != 0)
            {
                const char *out = proc->ProcessChar(ch);
                WriteString(out);
            }
        }

        if (signals & windowsig)
        {
            STMessage w;
            while ((w.msg = GetMsg(window->UserPort)))
            {
                switch(w.imsg->Class)
                {
                case IDCMP_CLOSEWINDOW:
                    exit = true;
                    break;
                    //case IDCMP_MENUPICK:
                    //    menu->Process();
                    //    break;
                default:
                    break;
                }

                ReplyMsg(w.msg);
            }
        }
    }

    line = proc->GetLine();
}

void AmigaWindow::WriteChar(const char character)
{
    writereq.io->io_Command = CMD_WRITE;
    writereq.io->io_Data =    (APTR)&character;
    writereq.io->io_Length =  1;
    DoIO(writereq.st);
}

void AmigaWindow::WriteString(const char *string)
{
    writereq.io->io_Command = CMD_WRITE;
    writereq.io->io_Data =    (APTR)string;
    writereq.io->io_Length =  (ULONG)-1;
    DoIO(writereq.st);
}

void AmigaWindow::WriteString(const char *string, unsigned int length)
{
    writereq.io->io_Command = CMD_WRITE;
    writereq.io->io_Data =    (APTR)string;
    writereq.io->io_Length =  (LONG)length;
    DoIO(writereq.st);
}

unsigned char AmigaWindow::ReadChar(STRequest request)
{
    unsigned char result = inputbuf;
    request.io->io_Command = CMD_READ;
    request.io->io_Data =    (APTR)&inputbuf;
    request.io->io_Length =  1;
    SendIO(request.st);
    return result;
}

unsigned char AmigaWindow::TryGetChar(MsgPort *msgport)
{
    STRequest readreq;
    readreq.msg = GetMsg(msgport);
    return readreq.msg == 0 ? '\0' : ReadChar(readreq);
}

void AmigaWindow::SetPrompt(const char* string)
{
    ConsoleBase::SetPrompt(string);
    proc->SetPrompt(string);
}

#endif


