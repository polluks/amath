/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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
#include "system/task.h"
#include "system/proc_amiga.h"
#include "system/base/thread.h"

#ifdef WITHTEST
#ifdef AMIGA
#ifdef DEVNOTFINISH // Still under development
#include <exec/io.h>
#include <exec/memory.h>
#include <intuition/intuition.h>
#include <libraries/dos.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>
#include <dos/dostags.h>

AmigaProcess::AmigaProcess()
{
    proc = NOMEM;
    maintask = FindTask(NULL);
    signal = AllocSignal(-1);
}

AmigaProcess::~AmigaProcess()
{
    /*
    if (proc != NOMEM) {
        Forbid();
        DeleteTask(proc);
        Permit();
    }
    */

    // See: http://eab.abime.net/showthread.php?t=73783
    // And AROS Stack swap: http://en.wikibooks.org/wiki/Aros/Developer/Docs/Examples/StackSwap
    Forbid();
    FreeSignal(signal);
    Permit();
}

ThreadStart procstart;

void AmigaProcess::Start(ThreadBase *thread)
{

    procstart.thread = thread;
    procstart.maintask = maintask;
    procstart.signal = signal;

    proc = CreateNewProcTags(NP_Entry, (ULONG) &AmigaProcess::Invoke,
                             NP_Name, thread->GetName(),
                             NP_Priority, 1,
                             TAG_DONE);
}

void AmigaProcess::Invoke()
{
    ThreadStart invoked = procstart;

    invoked.thread->Run();
    Signal(invoked.maintask, 1U << invoked.signal);
}

void AmigaProcess::WaitExit()
{
    Wait(1U << signal | SIGBREAKF_CTRL_C | SIGBREAKF_CTRL_D);
}

#endif
#endif
#endif
