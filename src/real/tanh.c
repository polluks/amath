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
 * http://www.netlib.org/fdlibm/s_tanh.c
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
 * @file  tanh.c
 * @brief Hyperbolic tangent function
 */

#include "prim.h"

static const double
    one = 1.0,
    two = 2.0,
    tiny = 1.0e-300;

/**
 * @brief   Hyperbolic tangent function
 * @return  The Hyperbolic Tangent of x
 * @details
 * <pre>
 * Method
 *                                    x    -x
 *                                   e  - e
 *     0. tanh(x) is defined to be -----------
 *                                    x    -x
 *                                   e  + e
 * 
 *     1. reduce x to non-negative by tanh(-x) = -tanh(x)
 * 
 *     2.  0      <= x <= 2**-55 : tanh(x) = x*(one+x)
 *                                            -t
 *         2**-55 <  x <=  1     : tanh(x) = -----; t = expm1(-2x)
 *                                           t + 2
 *                                                 2
 *         1      <= x <=  22.0  : tanh(x) = 1-  ----- ; t=expm1(2x)
 *                                               t + 2
 *         22.0   <  x <= INF    : tanh(x) = 1
 *
 * Special cases
 *     tanh(NaN) is NaN
 *     only tanh(0)=0 is exact for finite argument.
 * </pre>
 */
double tanh(double x)
{
    double t, z;
    int32_t jx, ix;

    /* High word of |x|. */
    GET_HIGH_WORD(jx, x);
    ix = jx & 0x7FFFFFFF;

    /* x is INF or NaN */
    if (ix >= 0x7FF00000)
    {
        if (jx >= 0)
            return one / x + one; /* tanh(+-inf)=+-1 */
        else
            return NAN; /* tanh(NaN) = NaN */
    }

    /* |x| < 22 */
    if (ix < 0x40360000)
    {                             /* |x|<22 */
        if (ix < 0x3C800000)      /* |x|<2**-55 */
            return x * (one + x); /* tanh(small) = small */
        if (ix >= 0x3FF00000)
        { /* |x|>=1 */
            t = expm1(two * fabs(x));
            z = one - two / (t + two);
        }
        else
        {
            t = expm1(-two * fabs(x));
            z = -t / (t + two);
        }
    }
    /* |x| > 22, return +-1 */
    else
    {
        z = one - tiny; /* raised inexact flag */
    }

    return (jx >= 0) ? z : -z;
}
