/*
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
 */

#include "amath.h"
#include "amathc.h"
#include "system/thread.h"
#include "system/task_amiga.h"

#ifdef AMIGA
#include <exec/io.h>
#include <exec/memory.h>
#include <intuition/intuition.h>
#include <libraries/dos.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>
#include <dos/dostags.h>

AmigaTask::AmigaTask()
{
    task = nullptr;
    maintask = FindTask(NULL);
    signal = AllocSignal(-1);
}

AmigaTask::~AmigaTask()
{
    if (task != nullptr) {
        Forbid();
        DeleteTask(task);
        Permit();
    }

    Forbid();
    FreeSignal(signal);
    Permit();
}

ThreadStart threadstart;

void AmigaTask::Start(ThreadBase *thread)
{
    threadstart.thread = thread;
    threadstart.maintask = maintask;
    threadstart.signal = signal;
    task = CreateTask(
               (STRPTR)thread->GetName(), 0,
               (APTR)&AmigaTask::Invoke,
               thread->GetStackSize());
}

void AmigaTask::Invoke()
{
    ThreadStart invoked = threadstart;
    invoked.thread->Run();
    Signal(invoked.maintask, 1U << invoked.signal);
}

void AmigaTask::WaitExit()
{
    Wait(1U << signal | SIGBREAKF_CTRL_C | SIGBREAKF_CTRL_D);
}

#endif
