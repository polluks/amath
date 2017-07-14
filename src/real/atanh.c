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
 * http://www.netlib.org/fdlibm/e_atanh.c
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
 * @file  atanh.c
 * @brief Inverse hyperbolic tangent function
 */

#include "prim.h"

static const double one = 1.0, huge = 1e300;
static double zero = 0.0;

/**
 * @brief   Inverse hyperbolic tangent function
 * @details
 * <pre>
 * Method
 *
 *     1.Reduced x to positive by atanh(-x) = -atanh(x)
 *     2.For x>=0.5
 *                   1               2x                         x
 *       atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                   2             1 - x                      1 - x
 *
 *       For x<0.5
 *       atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases
 *     atanh(x) is NaN if |x| > 1
 *     atanh(NaN) is that NaN
 *     atanh(+-1) is +-INF
 * </pre>
 */
double atanh(double x)
{
    double t;
    int32_t hx, ix;
    uint32_t lx;
    GET_HIGH_WORD(hx, x);
    GET_LOW_WORD(lx, x);
    ix = hx & 0x7FFFFFFF;

    // |x| > 1
    if ((ix | ((lx | (-lx)) >> 31)) > 0x3FF00000)
    {
        return NAN;
    }

    if (ix == 0x3FF00000)
        return x / zero;
    if (ix < 0x3E300000 && (huge + x) > zero)
        return x;         /* x<2**-28 */
    SET_HIGH_WORD(x, ix); /* x <- |x| */
    if (ix < 0x3FE00000)
    { /* x < 0.5 */
        t = x + x;
        t = 0.5 * log1p(t + t * x / (one - x));
    }
    else
        t = 0.5 * log1p((x + x) / (one - x));

    if (hx >= 0)
    {
        return t;
    }

    return -t;
}
