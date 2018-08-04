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
 * http://www.netlib.org/fdlibm/e_cosh.c
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
 * @file  cosh.c
 * @brief Hyperbolic cosine function
 */

#include "prim.h"

#if __GNUC__ > 2
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

static const double
    one = 1.0,
    half = 0.5,
    huge = 1.0e300;

/**
 * @brief   Hyperbolic cosine function
 * @details
 * Mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 * <pre>
 * Method
 *
 *     1. Replace x by |x| (cosh(x) = cosh(-x))
 *     2.
 *                                                   [ exp(x) - 1 ]^2
 *        0        <= x <= ln2/2  :  cosh(x) := 1 + -------------------
 *                                                     2*exp(x)
 *
 *                                              exp(x) +  1/exp(x)
 *        ln2/2    <= x <= 22     :  cosh(x) := -------------------
 *                                                      2
 *        22       <= x <= lnovft :  cosh(x) := exp(x)/2
 *        lnovft   <= x <= ln2ovft:  cosh(x) := exp(x/2)/2 * exp(x/2)
 *        ln2ovft  <  x           :  cosh(x) := huge*huge (overflow)
 *
 * Special cases:
 * 
 *     cosh(x) is |x| if x is +INF, -INF, or NaN
 *     only cosh(0)=1 is exact for finite x
 * </pre>
 */
double cosh(double x)
{
    double t, w;
    int32_t ix;
    uint32_t lx;

    // High word of |x|
    GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    // x is INF or NaN
    if (ix >= 0x7FF00000)
    {
        return x * x;
    }

    // |x| in [0,0.5*ln2]
    if (ix < 0x3FD62E43)
    {
        t = expm1(fabs(x));
        w = one + t;
        if (ix < 0x3C800000)
        {
            // cosh(tiny) = 1
            return w;
        }

        return one + (t * t) / (w + w);
    }

    // |x| in [0.5*ln2,22]
    if (ix < 0x40360000)
    {
        t = exp(fabs(x));
        return half * t + half / t;
    }

    // |x| in [22, log(maxdouble)]
    if (ix < 0x40862E42)
    {
        return half * exp(fabs(x));
    }

    // |x| in [log(maxdouble), overflowthresold]
    lx = *((((*(unsigned *)&one) >> 29)) + (unsigned *)&x);
    if (ix < 0x408633CE || ((ix == 0x408633CE) && (lx <= (unsigned)0x8FB9F87D)))
    {
        w = exp(half * fabs(x));
        t = half * w;
        return t * w;
    }

    // |x| > overflowthresold, cosh(x) overflow
    return huge * huge;
}
