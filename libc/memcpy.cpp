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

#include "def/libc.h"

#ifndef AMIGA
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

/**
 *
 * sizeof(word) MUST BE A POWER OF TWO
 * SO THAT wmask BELOW IS ALL ONES
 */
typedef int word; // "word" used for optimal copy speed

/**
 *
 * Macros: loop-t-times; and loop-t-times, t>0
 */
#define TLOOP(s)   if (t) TLOOP1(s)
#define TLOOP1(s)  do { s; } while (--t)

/**
 * @brief Copy a block of memory, handling overlap.
 *
 * Original file can be found at:
 * https://svnweb.freebsd.org/base/release/9.0.0/lib/libc/string/bcopy.c?revision=229286
 *
 */
void MemCopy(void *destination, const void *source, unsigned int length)
{
    char *dst = (char*) destination;
    const char *src = (const char*) source;
    unsigned int t;

    if (length == 0 || dst == src) // nothing to do
        return;

    if ((unsigned long)dst < (unsigned long)src) {
        // Copy forward
        t = (unsigned long)src; // only need low bits
        if ((t | (unsigned long)dst) & wmask) {

            // Try to align operands.  This cannot be done unless the low bits match.
            if ((t ^ (unsigned long)dst) & wmask || length < wsize)
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

    } else {
        // Copy backwards.  Otherwise essentially the same.
        // Alignment works as before, except that it takes
        // (t&wmask) bytes to align, not wsize-(t&wmask).
        src += length;
        dst += length;
        t = (unsigned long)src;
        if ((t | (unsigned long)dst) & wmask) {

            if ((t ^ (unsigned long)dst) & wmask || length <= wsize)
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