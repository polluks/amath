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
#include "main/graphlist.h"
#include "main/evaluator.h"
#include "system/console.h"
#include "system/filesystem.h"
#include "system/program_amiga.h"
#include "system/console_amiga.h"
#include "system/window_amiga.h"
#include "system/language_amiga.h"
#include "system/filesystem_amiga.h"
#include "system/preferences_amiga.h"
#include "system/base/io.h"

#ifdef AMIGA
#include <exec/types.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>

#define ARGS_FORMAT "SHELL/S,INPUT/F"

AmigaProgram::AmigaProgram()
    : Program()
{
    rdargs = NULL;
    args.shell = FALSE;
    args.quiet = FALSE;
    args.input = NULL;
    Console = NULL;
}

AmigaProgram::~AmigaProgram()
{
    if (Console != NULL) {
        delete Console;
    }

    if (rdargs != NULL) {
        FreeArgs(rdargs);
    }
}

void AmigaProgram::Initialize(int argc, char **argv)
{
    if(argc < 2) {
        Console = new AmigaWindow(Preferences->GetPrompt());
        return;
    }

//    rdargs = (RDArgs*)ReadArgs((const char*)ARGS_FORMAT, (IPTR*)&args, 0);
    rdargs = (RDArgs*)ReadArgs((const char*)ARGS_FORMAT, (IPTR*)&args, 0);
    if (!rdargs)
    {
        PrintFault(IoErr(), (STRPTR)argv[0]);
    }

    if (!args.quiet) {
        //TODO
    }

    if (args.shell) {
        Console = new AmigaShellConsole(Preferences->GetPrompt());
        return;
    }
}

void AmigaProgram::Run()
{
    if (Console != NULL) {
        Console->Run();
    } else if (args.input != NULL) {
        Evaluator *evaluator = new Evaluator(args.input);
        evaluator->Evaluate();
        const char *res = evaluator->GetResult();
        WriteToShell(res);
        delete evaluator;
    }
}

void AmigaProgram::Exit()
{
    Console->Exit();
}

#endif

