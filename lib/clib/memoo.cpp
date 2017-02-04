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

#include "mem.h"
#include "clib.h"

/* GCC 2.95 */
#if (__GNUC__ == 2 && __GNUC_MINOR__ == 95)
void* operator new (size_t size) { return AllocMemSafe(size); }
void* operator new[] (size_t size) { return AllocMemSafe(size); }
void  operator delete (void* ptr) { FreeMemSafe(ptr); }
void  operator delete[] (void* ptr) { FreeMemSafe(ptr); }
#endif

/* GCC 3+ */
#if (__GNUC__ > 2)
#include <new>
void* operator new (size_t size) throw(std::bad_alloc) { return AllocMemSafe(size); }
void* operator new[] (size_t size) throw(std::bad_alloc) { return AllocMemSafe(size); }
void  operator delete (void* ptr) throw() { FreeMemSafe(ptr); }
void  operator delete[] (void* ptr) throw() { FreeMemSafe(ptr); }
#endif

/* MSVC++ */
#if defined (_WIN32)
#include <new>
void* __CRTDECL operator new (size_t size) { return AllocMemSafe(size); }
void* __CRTDECL operator new[] (size_t size) { return AllocMemSafe(size); }
void  __CRTDECL operator delete (void* ptr) throw() { FreeMemSafe(ptr); }
void  __CRTDECL operator delete[] (void* ptr) throw() { FreeMemSafe(ptr); }
#endif
