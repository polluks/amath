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
 * http://www.netlib.org/fdlibm/e_asin.c
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
 * @file  asin.c
 * @brief Inverse sine function
 */

#include "prim.h"

static const double
    one = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
    huge = 1.000e+300,
    pio2_hi = 1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
    pio2_lo = 6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
    pio4_hi = 7.85398163397448278999e-01, /* 0x3FE921FB, 0x54442D18 */
    /* coefficient for R(x^2) */
    pS0 = 1.66666666666666657415e-01,  /* 0x3FC55555, 0x55555555 */
    pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
    pS2 = 2.01212532134862925881e-01,  /* 0x3FC9C155, 0x0E884455 */
    pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
    pS4 = 7.91534994289814532176e-04,  /* 0x3F49EFE0, 0x7501B288 */
    pS5 = 3.47933107596021167570e-05,  /* 0x3F023DE1, 0x0DFDF709 */
    qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
    qS2 = 2.02094576023350569471e+00,  /* 0x40002AE5, 0x9C598AC8 */
    qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
    qS4 = 7.70381505559019352791e-02;  /* 0x3FB3B8C5, 0xB12E9282 */

/**
 * @brief   Inverse sine function
 * @details
 * <pre>
 * Method
 *
 * Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
 * we approximate asin(x) on [0,0.5] by
 *      asin(x) = x + x*x^2*R(x^2)
 * where
 *      R(x^2) is a rational approximation of (asin(x)-x)/x^3
 * and its remez error is bounded by
 *      |(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
 *
 * For x in [0.5,1]
 *      asin(x) = pi/2-2*asin(sqrt((1-x)/2))
 * Let y = (1-x), z = y/2, s := sqrt(z), and pio2_hi+pio2_lo=pi/2;
 * then for x>0.98
 *      asin(x) = pi/2 - 2*(s+s*z*R(z))
 *              = pio2_hi - (2*(s+s*z*R(z)) - pio2_lo)
 * 
 * For x<=0.98, let pio4_hi = pio2_hi/2, then
 *      f = hi part of s;
 *      c = sqrt(z) - f = (z-f*f)/(s+f)     ...f+c=sqrt(z)
 * and
 *      asin(x) = pi/2 - 2*(s+s*z*R(z))
 *              = pio4_hi+(pio4-2s)-(2s*z*R(z)-pio2_lo)
 *              = pio4_hi+(pio4-2f)-(2s*z*R(z)-(pio2_lo+2c))
 *
 * Special cases
 *     if x is NaN, return NaN
 *     if |x|>1, return NaN
 * </pre>
 */
double asin(double x)
{
    double t, w, p, q, c, r, s;
    int32_t hx, ix;
    GET_HIGH_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x3ff00000)
    { /* |x|>= 1 */
        uint32_t lx;
        GET_LOW_WORD(lx, x);
        if (((ix - 0x3ff00000) | lx) == 0)
            /* asin(1)=+-pi/2 with inexact */
            return x * pio2_hi + x * pio2_lo;
        return NAN; /* asin(|x|>1) is NaN */
    }
    else if (ix < 0x3fe00000)
    { /* |x|<0.5 */
        if (ix < 0x3e400000)
        { /* if |x| < 2**-27 */
            if (huge + x > one)
            {
                return x; /* return x with inexact if x!=0*/
            }
            else
            {
                t = 0;
            }
        }
        else
        {
            t = x * x;
        }

        p = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
        q = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
        w = p / q;
        return x + x * w;
    }
    /* 1> |x|>= 0.5 */
    w = one - fabs(x);
    t = w * 0.5;
    p = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
    q = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
    s = sqrt(t);
    if (ix >= 0x3FEF3333)
    { /* if |x| > 0.975 */
        w = p / q;
        t = pio2_hi - (2.0 * (s + s * w) - pio2_lo);
    }
    else
    {
        w = s;
        SET_LOW_WORD(w, 0);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = 2.0 * s * r - (pio2_lo - 2.0 * c);
        q = pio4_hi - 2.0 * w;
        t = pio4_hi - (p - q);
    }
    if (hx > 0)
        return t;
    else
        return -t;
}
