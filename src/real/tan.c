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
 * http://www.netlib.org/fdlibm/s_tan.c
 * 
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
 * @file  tan.c
 * @brief Tangent function
 */

#include "prim.h"

/**
 * @brief   Tangent function
 * @return  Tangent function of x
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
double tan(double x)
{
    double y[2], z = 0.0;
    int32_t n, ix;

    GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    // |x| ~< pi/4
    if (ix <= 0x3FE921FB)
    {
        return __kernel_tan(x, z, 1);
    }

    // tan(Inf or NaN) is NaN
    if (ix >= 0x7FF00000)
    {
        return NAN;
    }

    // |x| ~< pi/4
    n = rempio2(x, y);
    return __kernel_tan(y[0], y[1], 1 - ((n & 1) << 1));
}
