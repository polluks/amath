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
#include "console.h"
#include "filesystem.h"
#include "program_amiga.h"
#include "console_amiga.h"
#include "window_amiga.h"
#include "language_amiga.h"
#include "filesystem_amiga.h"
#include "preferences_amiga.h"
#include "lib/charbuf.h"
#include "main/evaluator.h"

#if defined(AMIGA)
#define ARGS_FORMAT "SHELL/S,NOANSI/S,INPUT/F"
#include <clib/dos_protos.h>

#if defined(AOS3)
# define RDPTR LONG*
#else
# define RDPTR IPTR*
#endif

AmigaProgram::AmigaProgram()
    : Program()
{
    rdargs = nullptr;
    args.shell = FALSE;
    args.noansi = FALSE;
    args.input = nullptr;
    Console = nullptr;
}

AmigaProgram::~AmigaProgram()
{
    if (Console != nullptr) {
        Console->Close();
        delete Console;
    }

    if (rdargs != nullptr) {
        FreeArgs(rdargs);
    }
}

void AmigaProgram::Initialize(int argc, char **argv)
{
    rdargs = (RDArgs*)ReadArgs((const char*)ARGS_FORMAT, (RDPTR)&args, 0);
    if (!rdargs)
    {
        PrintFault(IoErr(), (STRPTR)argv[0]);
        return;
    }

    shellMode = args.shell ? true : false;
    ansiMode = args.noansi ? false : true;
    
    if (shellMode || args.input != nullptr)
    {
        Console = new AmigaShellConsole(Preferences->GetPrompt());
    }
    else
    {
        Console = new AmigaWindow(Preferences->GetPrompt(), Language);
    }
    
    InitAnsiMode();
}

void AmigaProgram::Start()
{
    if(Console == nullptr || !Console->Open())
    {
        return;
    }

    Preferences->Load();

    if (args.input != nullptr)
    {
        Evaluator *evaluator = new Evaluator(args.input);
        evaluator->Evaluate();
        const char *res = evaluator->GetResult();
        Console->WriteString(res);
        Console->ResetConsole();
        delete evaluator;
        return;
    }

    Console->Start();
    return;
}

#endif
