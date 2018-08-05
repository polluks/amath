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
#include "system/program.h"
#include "system/program_stdc.h"
#include "system/program_amiga.h"
#include "system/program_haiku.h"
#include "system/program_test.h"

const char* vers = TXTDOSVERSION;

class Program* Program = nullptr;

#if defined(AMIGA)
#include <clib/exec_protos.h>
static struct DosBase *DosBase             = nullptr;
static struct GfxBase *GfxBase             = nullptr;
static struct LocaleBase *LocaleBase       = nullptr;
static struct IntuitionBase *IntuitionBase = nullptr;
#endif

/* GCC 2.95 */
#if (__GNUC__ == 2 && __GNUC_MINOR__ == 95)
void* operator new (size_t size) { return AllocMemSafe(size); }
void* operator new[] (size_t size) { return AllocMemSafe(size); }
void  operator delete (void* ptr) { FreeMemSafe(ptr); }
void  operator delete[] (void* ptr) { FreeMemSafe(ptr); }
#endif

/* GCC 3+ */
#if (__GNUC__ > 2)
/* C++11 */
#if __cplusplus > 199711L
#include <new>
void* operator new (std::size_t size) { return AllocMemSafe(size); }
void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) noexcept { return AllocMemSafe(size); }
void* operator new[] (std::size_t size) { return AllocMemSafe(size); }
void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_value) noexcept { return AllocMemSafe(size); }
void operator delete (void* ptr) noexcept { FreeMemSafe(ptr); }
void operator delete (void* ptr, const std::nothrow_t& nothrow_constant) noexcept { FreeMemSafe(ptr); }
void operator delete[] (void* ptr) noexcept { FreeMemSafe(ptr); }
void operator delete[] (void* ptr, const std::nothrow_t& nothrow_constant) noexcept { FreeMemSafe(ptr); }
#else
/* C++98 */
#include <new>
void* operator new (std::size_t size) throw (std::bad_alloc) { return AllocMemSafe(size); }
void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw() { return AllocMemSafe(size); }
void* operator new[] (std::size_t size) throw (std::bad_alloc) { return AllocMemSafe(size); }
void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_value) throw() { return AllocMemSafe(size); }
void operator delete (void* ptr) throw() { FreeMemSafe(ptr); }
void operator delete (void* ptr, const std::nothrow_t& nothrow_constant) throw() { FreeMemSafe(ptr); }
void operator delete[] (void* ptr) throw() { FreeMemSafe(ptr); }
void operator delete[] (void* ptr, const std::nothrow_t& nothrow_constant) throw() { FreeMemSafe(ptr); }
#endif
#endif

/* MSVC++ */
#if defined(WINDOWS) && defined(_MSC_VER)
#include <new>
void* __CRTDECL operator new (size_t size) { return AllocMemSafe(size); }
void* __CRTDECL operator new[] (size_t size) { return AllocMemSafe(size); }
void  __CRTDECL operator delete (void* ptr) throw() { FreeMemSafe(ptr); }
void  __CRTDECL operator delete[] (void* ptr) throw() { FreeMemSafe(ptr); }
#endif

#if defined(WITHTEST)
#include <stdio.h>
void WriteOut(const char *string) { printf("%s", string); }
void WriteOutInt(int value) { printf("%i", value); }
#endif

int main(int argc, char** argv)
{
#if defined(WITHTEST)
    if (argc == 2 && StrIsEqual(argv[1], "--test"))
    {
        Program = new TestProgram(false);
    }
    else if (argc == 2 && StrIsEqual(argv[1], "--testz"))
    {
        Program = new TestProgram(true);
    }
    else    
#endif
    {
#if defined(AMIGA)
        DosBase = (struct DosBase*)OpenLibrary(AMIGADOS_NAME, AMIGADOS_REV);
        IntuitionBase = (struct IntuitionBase*)OpenLibrary(INTUITION_NAME, INTUITION_REV);
        GfxBase = (struct GfxBase*)OpenLibrary(GRAPHICS_NAME, GRAPHICS_REV);
        LocaleBase = (struct LocaleBase*)OpenLibrary(LOCALE_NAME, LOCALE_REV);
        Program = new AmigaProgram();
#elif defined(HAIKU)
        Program = new HaikuProgram();
#else
        Program = new StandardProgram();
#endif
    }
    
    Program->Initialize(argc, argv);
    Program->Start();
    
    int exit = Program->GetExitStatus();
    
#if defined(AMIGA)
    if (DosBase != nullptr)
        CloseLibrary((struct Library*)DosBase);
    
    if (LocaleBase != nullptr)
        CloseLibrary((struct Library*)LocaleBase);
    
    if (GfxBase != nullptr)
        CloseLibrary((struct Library*)GfxBase);
    
    if (IntuitionBase != nullptr)
        CloseLibrary((struct Library*)IntuitionBase);
#endif
    
    delete Program;
    FreeAllSafe();
    
    return exit;
}
