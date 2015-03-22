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

#ifndef _DEF_IO_H
#define _DEF_IO_H

/**
 * @file  io.h
 * @brief System dependend I/O constructors
 *
 */

#include "def/libc.h"
#include "def/text.h"
#include "io/console.h"
#include "io/filesystem.h"
#include "arc/stdc/cconsole.h"
#include "arc/stdc/cfilesystem.h"
#include "arc/aos/gui/agraph.h"
#include "arc/aos/gui/awindow.h"
#include "arc/aos/sys/aconsole.h"
#include "arc/aos/sys/afilesystem.h"

#ifdef AMIGA
#include "def/xdef.h"
#else
#include <stdio.h>
#endif

static inline void
WriteToShell(const char *out) {
#ifdef AMIGA
    Write(Output(), (APTR)out, StrLen(out));
    Write(Output(), (APTR)NORMALTEXT, StrLen(NORMALTEXT));
#else
    printf("%s%s", out, NORMALTEXT);
#endif
}

static inline ConsoleBase*
CreateWindow() {
#ifdef AMIGA
    return new AmigaWindow();
#else
    return new StandardConsole();
#endif
}

static inline ConsoleBase*
CreateShell() {
#ifdef AMIGA
    return new AmigaShellConsole();
#else
    return new StandardConsole();
#endif
}

static inline FilesystemBase*
CreateFilesystem() {
#ifdef AMIGA
    return new AmigaFilesystem();
#else
    return new StandardFilesystem();
#endif
}

static inline GraphWindow*
CreateGraphWindow() {
#ifdef AMIGA
    return new AmigaGraphWindow();
#else
    return NOMEM;
#endif
}

#endif
