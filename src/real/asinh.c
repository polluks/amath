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
 * http://www.netlib.org/fdlibm/s_asinh.c
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
 * @file  asinh.c
 * @brief Inverse hyperbolic sine function
 */

#include "prim.h"

static const double
    one = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
    ln2 = 6.93147180559945286227e-01, /* 0x3FE62E42, 0xFEFA39EF */
    huge = 1.00000000000000000000e+300;

/**
 * @brief   Inverse hyperbolic sine function
 * @details
 * <pre>
 * Method
 *     Based on
 *     asinh(x) = sign(x) * log [ |x| + sqrt(x*x+1) ]
 * 
 *     we have
 *     asinh(x) = x  if  1+x*x=1,
 *              = sign(x)*(log(x)+ln2)) for large |x|, else
 *              = sign(x)*log(2|x|+1/(|x|+sqrt(x*x+1))) if|x|>2, else
 *              = sign(x)*log1p(|x| + x^2/(1 + sqrt(1+x^2)))
 * </pre>
 */
double asinh(double x)
{
    double t, w;
    int32_t hx, ix;
    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x7ff00000)
        return x + x; /* x is inf or NaN */
    if (ix < 0x3e300000)
    { /* |x|<2**-28 */
        if (huge + x > one)
            return x; /* return x inexact except 0 */
    }
    if (ix > 0x41b00000)
    { /* |x| > 2**28 */
        w = log(fabs(x)) + ln2;
    }
    else if (ix > 0x40000000)
    { /* 2**28 > |x| > 2.0 */
        t = fabs(x);
        w = log(2.0 * t + one / (sqrt(x * x + one) + t));
    }
    else
    { /* 2.0 > |x| > 2**-28 */
        t = x * x;
        w = log1p(fabs(x) + t / (one + sqrt(one + t)));
    }
    if (hx > 0)
        return w;
    else
        return -w;
}
