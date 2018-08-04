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
 * http://www.netlib.org/fdlibm/k_tan.c
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
 * @file  ktan.c
 * @brief Kernel tan function
 */

#include "prim.h"

static const double xxx[] = {
    3.33333333333334091986e-01,             /* 3FD55555, 55555563 */
    1.33333333333201242699e-01,             /* 3FC11111, 1110FE7A */
    5.39682539762260521377e-02,             /* 3FABA1BA, 1BB341FE */
    2.18694882948595424599e-02,             /* 3F9664F4, 8406D637 */
    8.86323982359930005737e-03,             /* 3F8226E3, E96E8493 */
    3.59207910759131235356e-03,             /* 3F6D6D22, C9560328 */
    1.45620945432529025516e-03,             /* 3F57DBC8, FEE08315 */
    5.88041240820264096874e-04,             /* 3F4344D8, F2F26501 */
    2.46463134818469906812e-04,             /* 3F3026F7, 1A8D1068 */
    7.81794442939557092300e-05,             /* 3F147E88, A03792A6 */
    7.14072491382608190305e-05,             /* 3F12B80F, 32F0A7E9 */
    -1.85586374855275456654e-05,            /* BEF375CB, DB605373 */
    2.59073051863633712884e-05,             /* 3EFB2A70, 74BF7AD4 */
    /* one */ 1.00000000000000000000e+00,   /* 3FF00000, 00000000 */
    /* pio4 */ 7.85398163397448278999e-01,  /* 3FE921FB, 54442D18 */
    /* pio4lo */ 3.06161699786838301793e-17 /* 3C81A626, 33145C07 */
};

#define one xxx[13]
#define pio4 xxx[14]
#define pio4lo xxx[15]
#define T xxx

/**
 * @brief   Kernel tan function
 * @details
 * <pre>
 * Kernel tan function on [-pi/4, pi/4], pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input k indicates whether tan (if k = 1) or -1/tan (if k = -1) is returned.
 *
 * Algorithm
 *	1. Since tan(-x) = -tan(x), we need only to consider positive x.
 *	2. if x < 2^-28 (hx<0x3e300000 0), return x with inexact if x!=0.
 *	3. tan(x) is approximated by a odd polynomial of degree 27 on
 *	   [0,0.67434]
 *		  	         3             27
 *	   	tan(x) ~ x + T1*x + ... + T13*x
 *	   where
 *
 * 	        |tan(x)         2     4            26   |     -59.2
 * 	        |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
 * 	        |  x 					|
 *
 *	   Note: tan(x+y) = tan(x) + tan'(x)*y
 *		          ~ tan(x) + (1+x*x)*y
 *	   Therefore, for better accuracy in computing tan(x+y), let
 *		     3      2      2       2       2
 *		r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
 *	   then
 *		 		    3    2
 *		tan(x+y) = x + (T1*x + (x *(r+y)+y))
 *
 *      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
 *		tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
 *		       = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
 * </pre>
 */
double __kernel_tan(double x, double y, int iy)
{
    double z, r, v, w, s;
    double a, t;
    int32_t ix, hx;
    uint32_t low;

    // high word of x
    GET_HIGH_WORD(hx, x);

    // high word of |x|
    ix = hx & 0x7FFFFFFF;

    // x < 2**-28
    if (ix < 0x3E300000)
    {
        // generate inexact
        if ((int32_t)x == 0)
        {
            GET_LOW_WORD(low, x);

            if (((ix | low) | (iy + 1)) == 0)
            {
                return one / fabs(x);
            }

            if (iy == 1)
            {
                return x;
            }

            // compute -1 / (x+y) carefully
            z = w = x + y;
            SET_LOW_WORD(z, 0);
            v = y - (z - x);
            t = a = -one / w;
            SET_LOW_WORD(t, 0);
            s = one + t * z;
            return t + a * (s + t * v);
        }
    }

    // |x| >= 0.6744
    if (ix >= 0x3FE59428)
    {
        if (hx < 0)
        {
            x = -x;
            y = -y;
        }
        z = pio4 - x;
        w = pio4lo - y;
        x = z + w;
        y = 0.0;
    }

    z = x * x;
    w = z * z;

    /*
     * Break x^5*(T[1]+x^2*T[2]+...) into
     * x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
     * x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
     */
    r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] + w * T[11]))));
    v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] + w * T[12])))));
    s = z * x;
    r = y + z * (s * (r + v) + y);
    r += T[0] * s;
    w = x + r;

    if (ix >= 0x3FE59428)
    {
        v = (double)iy;
        return (double)(1 - ((hx >> 30) & 2)) *
               (v - 2.0 * (x - (w * w / (w + v) - r)));
    }

    if (iy == 1)
    {
        return w;
    }

    // compute -1.0 / (x+r) accurately
    z = w;
    SET_LOW_WORD(z, 0);
    v = r - (z - x);  // z+v = r+x
    t = a = -1.0 / w; // a = -1.0/w
    SET_LOW_WORD(t, 0);
    s = 1.0 + t * z;
    return t + a * (s + t * v);
}
