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
 * The original source code can be obtained from:
 * http://www.netlib.org/fdlibm/k_sin.c
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
 * @file  ksin.c
 * @brief Kernel sin function
 */

#include "prim.h"

static const double
    half = 5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
    S1 = -1.66666666666666324348e-01,  /* 0xBFC55555, 0x55555549 */
    S2 = 8.33333333332248946124e-03,   /* 0x3F811111, 0x1110F8A6 */
    S3 = -1.98412698298579493134e-04,  /* 0xBF2A01A0, 0x19C161D5 */
    S4 = 2.75573137070700676789e-06,   /* 0x3EC71DE3, 0x57B1FE7D */
    S5 = -2.50507602534068634195e-08,  /* 0xBE5AE5E6, 0x8A2B9CEB */
    S6 = 1.58969099521155010221e-10;   /* 0x3DE5D93A, 0x5ACFD57C */

/**
 * @brief   Kernel sin function
 * @details
 * <pre>
 * Kernel sin function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input iy indicates whether y is 0. (if iy=0, y assume to be 0).
 *
 * Algorithm
 *   1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *   2. if x < 2^-27 (hx<0X3E400000 0), return x with inexact if x!=0.
 *   3. sin(x) is approximated by a polynomial of degree 13 on [0,pi/4]
 *                        3            13
 *       sin(x) ~ x + S1*x + ... + S6*x
 * 
 *     where
 *
 *     |sin(x)         2     4     6     8     10     12  |     -58
 *     |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *     |  x                                               |
 *
 *   4. sin(x+y) = sin(x) + sin'(x')*y
 *               ~ sin(x) + (1-x*x/2)*y
 * 
 *        For better accuracy, let
 *           3      2      2      2      2
 *       r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *     then                3    2
 *       sin(x) = x + (S1*x + (x *(r-y/2)+y))
 * </pre>
 */
double __kernel_sin(double x, double y, int iy)
{
    double z, r, v;
    int32_t ix;

    GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    // |x| < 2**-27
    if (ix < 0x3E400000)
    {
        // generate inexact
        if ((int)x == 0)
        {
            return x;
        }
    }

    z = x * x;
    v = z * x;
    r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));

    if (iy == 0)
    {
        return x + v * (S1 + z * r);
    }

    return x - ((z * (half * y - v * r) - y) - v * S1);
}
