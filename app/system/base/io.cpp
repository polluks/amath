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
#include "text.h"
#include "ansicon.h"
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
#include "system/filesystem.h"
#include "system/filesystem_stdc.h"
#include "system/filesystem_amiga.h"
#include "system/preferences.h"
#include "system/preferences_stdc.h"
#include "system/preferences_amiga.h"
#include "system/window_amiga.h"
#include "system/graph_amiga.h"

class Program *Program;
const char *vers = TXTDOSVERSION;

#ifndef AMIGA
#include <new>
void* operator new (size_t size) throw(std::bad_alloc) {
    return AllocMemSafe(size);
}

void* operator new[] (size_t size) throw(std::bad_alloc) {
    return AllocMemSafe(size);
}

void  operator delete (void* ptr) throw() {
    FreeMemSafe(ptr);
}

void  operator delete[] (void* ptr) throw() {
    FreeMemSafe(ptr);
}
#else
inline void* operator new (size_t size) {
    return AllocMemSafe(size);
}

inline void* operator new[] (size_t size) {
    return AllocMemSafe(size);
}

inline void  operator delete (void* ptr) {
    FreeMemSafe(ptr);
}

inline void  operator delete[] (void* ptr) {
    FreeMemSafe(ptr);
}
#endif

class Program* CreateProgram(int argc, char **argv) {
    class Program* out;
#ifdef WITHTEST
    if (argc == 2 && StrIsEqual(argv[1], "test")) {
        out = new TestProgram();
    } else
#endif
    {
#ifdef AMIGA
        out = new AmigaProgram();
#else
        out = new StandardProgram();
#endif
    }
    out->Initialize(argc, argv);
    return out;
}

class Language* CreateLanguage()
{
#ifdef AMIGA
    return new AmigaLanguage();
#else
    return new StandardLanguage();
#endif
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


