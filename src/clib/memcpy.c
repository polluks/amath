/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @file  memcpy.c
 * @brief Copy a block of memory, handling overlap.
 *
 * Code originate from FreeBSD base, revision 229286.
 *
 * Browse at:
 * https://svnweb.freebsd.org/base/head/lib/libc/string/bcopy.c?revision=229286
 *
 */

#include "amathc.h"

#if __GNUC__ > 2
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

#ifdef AMIGA 
#include <clib/exec_protos.h>
#endif

/**
 *
 * sizeof(word) MUST BE A POWER OF TWO
 * SO THAT wmask BELOW IS ALL ONES
 */
typedef uint32_t word;

#ifdef _WIN32
typedef unsigned long long mem_ptr;
#else
typedef unsigned long mem_ptr;
#endif

/**
 *
 * Macros: loop-t-times; and loop-t-times, t>0
 */
#define TLOOP(s)   if (t) TLOOP1(s)
#define TLOOP1(s)  do { s; } while (--t)

/**
 * @brief Copy a block of memory, handling overlap.
 */
void MemCopy(void* destination, const void* source, unsigned int length)
{
    char* dst = (char*) destination;
    const char* src = (const char*) source;
    unsigned int t;

    if (length == 0 || dst == src) // nothing to do
        return;

    if ((mem_ptr)dst < (mem_ptr)src)
    {
        // Copy forward
#ifdef AMIGA // Take advantage of exec
        CopyMem((void*)source, destination, length);
#else
        t = (mem_ptr)src; // only need low bits
        if ((t | (mem_ptr)dst) & wmask)
        {
            // Try to align operands.  This cannot be done unless the low bits match.
            if ((t ^ (mem_ptr)dst) & wmask || length < wsize)
                t = length;
            else
                t = wsize - (t & wmask);
            length -= t;

            TLOOP1(*dst++ = *src++);
        }

        // Copy whole words, then mop up any trailing bytes.
        t = length / wsize;
        TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);

        t = length & wmask;
        TLOOP(*dst++ = *src++);
#endif
    }
    else
    {
        // Copy backwards.  Otherwise essentially the same.
        // Alignment works as before, except that it takes
        // (t&wmask) bytes to align, not wsize-(t&wmask).
        src += length;
        dst += length;
        t = (mem_ptr)src;
        if ((t | (mem_ptr)dst) & wmask)
        {
            if ((t ^ (mem_ptr)dst) & wmask || length <= wsize)
                t = length;
            else
                t &= wmask;
            length -= t;

            TLOOP1(*--dst = *--src);
        }

        t = length / wsize;
        TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);

        t = length & wmask;
        TLOOP(*--dst = *--src);
    }
}
