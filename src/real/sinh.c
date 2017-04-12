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
 * http://www.netlib.org/fdlibm/e_sinh.c
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
 * @file  sinh.c
 * @brief Hyperbolic sine function
 */

#include "prim.h"

#if __GNUC__ > 2
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

static const double
    one = 1.0,
    shuge = 1.0e307;

/**
 * @brief   Hyperbolic sine function
 * @details
 * <pre>
 * Method
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 *	1. Replace x by |x| (sinh(-x) = -sinh(x)).
 *	2.
 *		                                    E + E/(E+1)
 *	    0        <= x <= 22     :  sinh(x) := --------------, E=expm1(x)
 *			       			        2
 *
 *	    22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *	    lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *	    ln2ovft  <  x	    :  sinh(x) := x*shuge (overflow)
 *
 * Special cases
 *     sinh(x) is |x| if x is +INF, -INF, or NaN.
 *     only sinh(0)=0 is exact for finite x.
 * </pre>
 */
double sinh(double x)
{
    double t, w, h;
    int32_t ix, jx;
    uint32_t lx;

    // High word of |x|
    GET_HIGH_WORD(jx, x);
    ix = jx & 0x7FFFFFFF;

    // x is INF or NaN
    if (ix >= 0x7FF00000)
    {
        return NAN;
    }

    h = 0.5;
    if (jx < 0)
        h = -h;
    /* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
    if (ix < 0x40360000)
    {                        /* |x|<22 */
        if (ix < 0x3E300000) /* |x|<2**-28 */
            if (shuge + x > one)
                return x; /* sinh(tiny) = tiny with inexact */
        t = expm1(fabs(x));
        if (ix < 0x3FF00000)
            return h * (2.0 * t - t * t / (t + one));
        return h * (t + t / (t + one));
    }

    /* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
    if (ix < 0x40862E42)
        return h * exp(fabs(x));

    /* |x| in [log(maxdouble), overflowthresold] */
    lx = *((((*(uint32_t *)&one) >> 29)) + (uint32_t *)&x);
    if (ix < 0x408633CE || ((ix == 0x408633CE) && (lx <= (uint32_t)0X8FB9F87D)))
    {
        w = exp(0.5 * fabs(x));
        t = h * w;
        return t * w;
    }

    /* |x| > overflowthresold, sinh(x) overflow */
    return x * shuge;
}
