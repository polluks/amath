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
 * The original source code can be obtained from:
 * http://www.netlib.org/fdlibm/s_cbrt.c
 * 
 * =================================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * =================================================================
 */

/**
 * @file  cbrt.c
 * @brief Cube root function
 */

#include "prim.h"

static const unsigned
    B1 = 715094163, /* B1 = (682-0.03306235651)*2**20 */
    B2 = 696219795; /* B2 = (664-0.03306235651)*2**20 */

static const double
    C = 5.42857142857142815906e-01,  /* 19/35     = 0x3FE15F15, 0xF15F15F1 */
    D = -7.05306122448979611050e-01, /* -864/1225 = 0xBFE691DE, 0x2532C834 */
    E = 1.41428571428571436819e+00,  /* 99/70     = 0x3FF6A0EA, 0x0EA0EA0F */
    F = 1.60714285714285720630e+00,  /* 45/28     = 0x3FF9B6DB, 0x6DB6DB6E */
    G = 3.57142857142857150787e-01;  /* 5/14      = 0x3FD6DB6D, 0xB6DB6DB7 */

/**
 * @brief Cube root function
 */
double cbrt(double x)
{
    int32_t hx, lx, ht;
    double r, s, t = 0.0, w;
    uint32_t sign;

    GET_HIGH_WORD(hx, x);

    // sign = sign(x)
    sign = hx & 0x80000000;
    hx ^= sign;

    // cbrt(NaN,INF) is itself
    if (hx >= 0x7FF00000)
    {
        return x + x;
    }

    GET_LOW_WORD(lx, x);

    // cbrt(0) is itself
    if ((hx | lx) == 0)
    {
        return x;
    }

    // x <- |x|
    SET_HIGH_WORD(x, hx);

    // rough cbrt to 5 bits
    if (hx < 0x00100000) // subnormal number
    {
        SET_HIGH_WORD(t, 0x43500000); // set t= 2**54
        t *= x;
        GET_HIGH_WORD(ht, t);
        SET_HIGH_WORD(t, ht / 3 + B2);
    }
    else
    {
        SET_HIGH_WORD(t, hx / 3 + B1);
    }

    // new cbrt to 23 bits, may be implemented in single precision
    r = t * t / x;
    s = C + r * t;
    t *= G + F / (s + E + D / s);

    // chopped to 20 bits and make it larger than cbrt(x)
    SET_LOW_WORD(t, 0);
    GET_HIGH_WORD(ht, t);
    SET_HIGH_WORD(t, ht + 0x00000001);

    // one step newton iteration to 53 bits with error less than 0.667 ulps
    s = t * t; // t*t is exact
    r = x / s;
    w = t + t;
    r = (r - t) / (w + r); // r-s is exact
    t = t + t * r;

    // retore the sign bit
    GET_HIGH_WORD(ht, t);
    SET_HIGH_WORD(t, ht | sign);

    return (t);
}
