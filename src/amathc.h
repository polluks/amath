/*-
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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#ifndef AMATHC_H
#define AMATHC_H

/**
 * @file  amathc.h
 * @brief C functions for manipulating strings and memory.
 *
 */

#include <stddef.h>
#include "amath.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    const char* tag;
    const char* text;
} texttag;

void* AllocMemSafe(size_t);
void FreeMemSafe(void*);
void DetachMemSafe(void*);
void FreeAllSafe();
void MemUsage(long*, long*, long*);

int StrLen(const char* string);
bool StrIsEqual(const char* s1, const char* s2);
void MemSet(void* destination, int c0, unsigned int length);
void MemCopy(void* destination, const void* source, unsigned int length);
unsigned int AllocAndCopy(char** destination, const char* source);
void Untag(char* destination, const char* source,
    texttag tags[], unsigned int tagcount);

#ifdef __cplusplus
}
#endif

#endif
