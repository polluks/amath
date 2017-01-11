/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
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

#ifndef _AMIGA_TASK
#define _AMIGA_TASK

/**
 * @file  atask.h
 * @brief Amiga OS specific sytem task calls.
 *
 */

#include "clib.h"
#include "system/task.h"
#include "system/task_amiga.h"
#include "system/base/thread.h"

#ifdef AMIGA
#include <exec/io.h>
#include <exec/memory.h>
#include <libraries/dos.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>

/**
* @brief Infomations passed to a new task when started.
*
*/
struct ThreadStart {
    ThreadBase *thread;
    Task *maintask;
    unsigned int signal;
};

/**
* @brief Encapsulates system calls to an Amiga OS task.
*
*/
class AmigaTask : public TaskBase {
public:
    AmigaTask();
    ~AmigaTask();
    void Start(ThreadBase *thread);
    void WaitExit();

private:
    static void Invoke();
    unsigned int signal;
    Task *maintask;
    Task *task;
};

#endif
#endif
