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

#include "mem.h"
#include "clib.h"
#include "localize/start.h"
#include "system/program.h"
#include "system/program_stdc.h"
#include "system/program_amiga.h"
#include "system/program_test.h"
#include "system/console.h"
#include "system/console_stdc.h"
#include "system/console_amiga.h"
#include "system/language.h"
#include "system/language_stdc.h"
#include "system/language_amiga.h"
#include "system/language_posix.h"
#include "system/filesystem.h"
#include "system/filesystem_stdc.h"
#include "system/filesystem_amiga.h"
#include "system/preferences.h"
#include "system/preferences_stdc.h"
#include "system/preferences_amiga.h"
#include "system/window_amiga.h"
#include "system/graph_amiga.h"
#include "system/base/io.h"

#ifdef AMIGA
#include <exec/types.h>
#include <exec/io.h>
#include <exec/memory.h>
#include <libraries/dos.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>
#include <devices/conunit.h>
#include <devices/console.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/intuition_protos.h>
#include <clib/locale_protos.h>
#endif

const char *vers = TXTDOSVERSION;
class  Program *Program = NULL;
#ifdef AMIGA
static struct DosBase *DosBase             = NULL;
static struct GfxBase *GfxBase             = NULL;
static struct LocaleBase *LocaleBase       = NULL;
static struct IntuitionBase *IntuitionBase = NULL;
#endif

class Program* CreateProgram(int argc, char **argv) {
#ifdef WITHTEST
    if (argc == 2 && StrIsEqual(argv[1], "test")) {
        return new TestProgram();
    } else
#endif
    {
#ifdef AMIGA
        IntuitionBase = (struct IntuitionBase*)OpenLibrary(INTUITION_NAME, INTUITION_REV);
        GfxBase = (struct GfxBase*)OpenLibrary(GRAPHICS_NAME, GRAPHICS_REV);

        if (IntuitionBase != NULL && GfxBase != NULL) {
            return new AmigaProgram();
        } else {
            return new StandardProgram();
        }
#else
        return new StandardProgram();
#endif
    }
    return NULL;
}

class Language* CreateLanguage()
{
#ifdef UNIX
    return new PosixLanguage();
#endif
#ifdef AMIGA
    LocaleBase = (struct LocaleBase*)OpenLibrary(LOCALE_NAME, LOCALE_REV);
    if (LocaleBase != NULL) {
        return new AmigaLanguage();
    } else
#endif
    {
        return new StandardLanguage();
    }
}

class PreferencesBase* CreatePreferences()
{
#ifdef AMIGA
    return new AmigaPreferences();
#else
    return new StandardPreferences();
#endif
}

class FilesystemBase* CreateFilesystem()
{
#ifdef AMIGA
    DosBase = (struct DosBase*)OpenLibrary(AMIGADOS_NAME, AMIGADOS_REV);
    if (DosBase == NULL) {
        return NULL;
    }
    return new AmigaFilesystem();
#else
    return new StandardFilesystem();
#endif
}

GraphWindow* CreateGraphWindow() {
#ifdef AMIGA
    return new AmigaGraphWindow();
#else
    return NOMEM;
#endif
}

void WriteToShell(const char *out) {
#ifdef AMIGA
    Write(Output(), (APTR)out, StrLen(out));
    Write(Output(), (APTR)NORMALTEXT, StrLen(NORMALTEXT));
#else
    printf("%s%s", out, NORMALTEXT);
#endif
}

void Cleanup()
{
#ifdef AMIGA
    if (DosBase != NULL) {
        CloseLibrary((struct Library*)DosBase);
    }

    if (LocaleBase != NULL) {
        CloseLibrary((struct Library*)LocaleBase);
    }

    if (GfxBase != NULL) {
        CloseLibrary((struct Library*)GfxBase);
    }

    if (IntuitionBase != NULL) {
        CloseLibrary((struct Library*)IntuitionBase);
    }
#endif
    delete Program;
    FreeAllSafe();
}
