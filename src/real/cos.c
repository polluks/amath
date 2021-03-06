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
 * http://www.netlib.org/fdlibm/s_cos.c
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
 * @file  cos.c
 * @brief Cosine function
 */

#include "prim.h"

/**
 * @brief   Cosine function
 * @param   x
 * @return  Cosine function of x
 * @details
 * <pre>
 * Kernel function:
 *
 *     __kernel_sin        ... sine function on [-pi/4,pi/4]
 *     __kernel_cos        ... cose function on [-pi/4,pi/4]
 *     __ieee754_rem_pio2  ... argument reduction routine
 *
 * Method:
 *
 *     Let S,C and T denote the sin, cos and tan respectively on
 *     [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *     in [-pi/4 , +pi/4], and let n = k mod 4.
 *
 *     We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S           -1/T
 *          2         -S          -C             T
 *          3         -C           S           -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *
 *     Let trig be any of sin, cos, or tan.
 *     trig(+-INF)  is NaN
 *     trig(NaN)    is that NaN
 *
 * Accuracy:
 *
 *     TRIG(x) returns trig(x) nearly rounded
 * </pre>
 */
double cos(double x)
{
    double y[2], z = 0.0;
    int32_t n, ix;

    // High word of x
    GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    // |x| ~< pi/4
    if (ix <= 0x3FE921FB)
    {
        return __kernel_cos(x, z);
    }

    // cos(Inf or NaN) is NaN
    if (ix >= 0x7FF00000)
    {
        return NAN;
    }

    // argument reduction needed
    n = rempio2(x, y);
    switch (n & 3)
    {
    case 0:
        return __kernel_cos(y[0], y[1]);
    case 1:
        return -__kernel_sin(y[0], y[1], 1);
    case 2:
        return -__kernel_cos(y[0], y[1]);
    default:
        return __kernel_sin(y[0], y[1], 1);
    }
}
