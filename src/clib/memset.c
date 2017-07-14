/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
 * Copyright (c) 1990, 1993 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Hibler and Chris Torek.
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

/**
 * @file  memset.c
 * @brief Fill block of memory with a constant value.
 *
 * Code originate from FreeBSD base, revision 229286.
 *
 * The original source code can be obtained from:
 * https://svnweb.freebsd.org/base/head/lib/libc/string/memset.c?revision=229286
 *
 */

#include "amathc.h"

#if __GNUC__ > 2
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

typedef uintptr_t mem_ptr;

/**
 * @brief Fill block of memory with a constant value.
 */
void MemSet(void* dst0, int c0, unsigned int length)
{
    unsigned char* dst = (unsigned char*) dst0;
    unsigned int t;
    unsigned int c;

    /*
     * If not enough words, just fill bytes.  A length >= 2 words
     * guarantees that at least one of them is `complete' after
     * any necessary alignment.  For instance:
     *
     *	|-----------|-----------|-----------|
     *	|00|01|02|03|04|05|06|07|08|09|0A|00|
     *	          ^---------------------^
     *		 dst		 dst+length-1
     *
     * but we use a minimum of 3 here since the overhead of the code
     * to do word writes is substantial.
     */
    if (length < 3 * wsize)
    {
        while (length != 0)
        {
            *dst++ = c0;
            --length;
        }
    }

    if ((c = (unsigned char)c0) != 0)
    { /* Fill the word. */
        c = (c << 8) | c; /* u_int is 16 bits. */
#if UINT_MAX > 0xffff
        c = (c << 16) | c;	/* u_int is 32 bits. */
#endif
#if UINT_MAX > 0xffffffff
        c = (c << 32) | c;	/* u_int is 64 bits. */
#endif
    }

    /* Align destination by filling in bytes. */
    if ((t = (mem_ptr)dst & wmask) != 0)
    {
        t = wsize - t;
        length -= t;
        do
        {
            *dst++ = c0;
        }
        while (--t != 0);
    }

    /* Fill words.  Length was >= 2*words so we know t >= 1 here. */
    t = length / wsize;
    do
    {
        *(unsigned int*)dst = c;
        dst += wsize;
    }
    while (--t != 0);

    /* Mop up trailing bytes, if any. */
    t = length & wmask;
    if (t != 0)
        do
        {
            *dst++ = c0;
        }
        while (--t != 0);
}
