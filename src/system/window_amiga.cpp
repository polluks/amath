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

#include "amath.h"
#include "amathc.h"
#include "window_amiga.h"
#include "lib/aengine.h"
#include "main/evaluator.h"

#if defined(AMIGA)

#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>
#include <clib/locale_protos.h>
#include <libraries/dos.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <devices/conunit.h>
#include <devices/console.h>

AmigaWindow::AmigaWindow(const char *prompt, CharValidator *validator) :
    ConsoleBase(prompt)
{
    proc = new AnsiConoleEngine(prompt, validator);
    window = nullptr;
    //menu = nullptr;
    writereq.st = nullptr;
    writeport = nullptr;
    readreq.st = nullptr;
    readport = nullptr;
    succeed = false;
    openconsole = false;
}

AmigaWindow::~AmigaWindow()
{
    Cleanup();
    delete proc;
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
        WFLG_SIMPLE_REFRESH,
        nullptr, nullptr,     // user gadgets, user checkmark
        (UBYTE*) TXTTITLE,    // title
        nullptr, nullptr,     // window screen, super bitmap
        400, 75,              // min width, height
        1600, 1050,           // max width, height
        WBENCHSCREEN          // open on workbench screen
    };

    succeed = true;
    succeed = succeed && (writeport = CreatePort((char*)PORTCR, 0)) != 0;
    succeed = succeed && (readport = CreatePort((char*)PORTCW, 0)) != 0;
    succeed = succeed && (writereq.st = CreateExtIO(writeport, sizeof(IOStdReq))) != 0;
    succeed = succeed && (readreq.st = CreateExtIO(readport, sizeof(IOStdReq))) != 0;
    succeed = succeed && (window = OpenWindow(&nw)) != 0;
    if (!succeed) return;

    windowsig = 1 << window->UserPort->mp_SigBit;
    writereq.io->io_Data = (APTR) window;
    writereq.io->io_Length = sizeof(Window);

    openconsole = OpenDevice(DEVCONSOLE, CONU_SNIPMAP, writereq.st, CONFLAG_DEFAULT) == 0;
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
        readreq.st = nullptr;
    }

    if(readport) {
        DeletePort(readport);
        readport = nullptr;
    }

    if(writereq.st) {
        DeleteExtIO(writereq.st);
        writereq.st = nullptr;
    }

    if(writeport) {
        DeletePort(writeport);
        writeport = nullptr;
    }

    //if (menu) {
    //    delete menu;
    //    menu = nullptr;
    //}

    if(window) {
        CloseWindow(window);
        window = nullptr;
    }
}

void AmigaWindow::Start()
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


//http://amigadev.elowar.com/read/ADCD_2.1/Libraries_Manual_guide/node046C.html#line6

//#include <devices/keymap.h>
//
//BOOL AskKeyMap(struct IOStdReq *request, struct KeyMap *keymap)
//{
//   request->io_Command = CD_ASKKEYMAP;
//    request->io_Length = sizeof(struct KeyMap);
//    request->io_Data = (APTR)keymap;  /* where to put it */
//    DoIO(request);
//    if(request->io_Error) return(FALSE);
//    else  return(TRUE); /* if no error, it worked. */
//}

//BOOL SetKeyMap(struct IOStdReq *request,struct KeyMap *keymap)
//{
//    request->io_Command = CD_SETKEYMAP;
//    request->io_Length = sizeof(struct KeyMap);
//    request->io_Data = (APTR)keymap;      /* where to get it */
//    DoIO(request);
//    if(request->io_Error) return(FALSE);
//    else  return(TRUE);     /* if no error, it worked. */
//}
