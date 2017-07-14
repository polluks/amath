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
 * https://amath.innolan.net
 *
 * The original source code can be obtained from:
 * http://www.netlib.org/fdlibm/e_acosh.c
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
 * @file  acosh.c
 * @brief Inverse hyperbolic cosine function
 */

#include "prim.h"

static const double
    one = 1.0,
    ln2 = 6.93147180559945286227e-01; /* 0x3FE62E42, 0xFEFA39EF */

/**
 * @brief   Inverse hyperbolic cosine function
 * @details
 * <pre>
 * Based on
 *     acosh(x) = log [ x + sqrt(x*x-1) ]
 * 
 * we have
 *     acosh(x) = log(x)+ln2, if x is large; else
 *     acosh(x) = log(2x-1/(sqrt(x*x-1)+x)) if x>2; else
 *     acosh(x) = log1p(t+sqrt(2.0*t+t*t)); where t=x-1
 *
 * Special cases
 *     acosh(x) is NaN if x<1
 *     acosh(NaN) is NaN
 * </pre>
 */
double acosh(double x)
{
    double t;
    int32_t hx, lx;

    GET_HIGH_WORD(hx, x);
    GET_LOW_WORD(lx, x);

    // x < 1
    if (hx < 0x3FF00000)
    {
        return NAN;
    }

    // x > 2**28
    if (hx >= 0x41B00000)
    {
        // x is inf or NaN
        if (hx >= 0x7FF00000)
        {
            return NAN;
        }

        // acosh(huge) = log(2x)
        return log(x) + ln2;
    }

    // acosh(1) = 0
    if (((hx - 0x3FF00000) | lx) == 0)
    {
        return 0.0;
    }

    // 2**28 > x > 2
    if (hx > 0x40000000)
    {
        t = x * x;
        return log(2.0 * x - one / (x + sqrt(t - one)));
    }

    // 1 < x < 2
    t = x - one;
    return log1p(t + sqrt(2.0 * t + t * t));
}
