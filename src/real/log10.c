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
 * http://www.netlib.org/fdlibm/e_log10.c
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
 * @file  log10.c
 * @brief Base 10 logarithm function
 */

#include "prim.h"

static const double
two54      =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
ivln10     =  4.34294481903251816668e-01, /* 0x3FDBCB7B, 0x1526E50E */
log10_2hi  =  3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
log10_2lo  =  3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */

static double zero   =  0.0;

/**
 * @brief   Base 10 logarithm function
 * @details
 * <pre>
 * Method:
 *
 *     Let log10_2hi = leading 40 bits of log10(2) and
 *         log10_2lo = log10(2) - log10_2hi,
 *         ivln10    = 1/log(10) rounded.
 *     Then
 *         n = ilogb(x),
 *         if(n<0)  n = n+1;
 *         x = scalbn(x,-n);
 *         log10(x) := n*log10_2hi + (n*log10_2lo + ivln10*log(x))
 *
 *     Note 1:
 *     To guarantee log10(10**n)=n, where 10**n is normal, the rounding
 *     mode must set to Round-to-Nearest.
 * 
 *     Note 2:
 *     [1/log(10)] rounded to 53 bits has error .198 ulps;
 *     log10 is monotonic at all binary break points.
 *
 * Special cases:
 *
 *     log10(x) is NaN with signal if x < 0;
 *     log10(+INF) is +INF with no signal; log10(0) is -INF with signal;
 *     log10(NaN) is that NaN with no signal;
 *     log10(10**N) = N  for N=0,1,...,22.
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 * </pre>
 */
double log10(double x)
{
    double y,z;
    int32_t i,k,hx;
    uint32_t lx;

    EXTRACT_WORDS(hx,lx,x);

    k=0;
    if (hx < 0x00100000) {                  /* x < 2**-1022  */
        if (((hx&0x7fffffff)|lx)==0)
            return -two54/zero;             /* log(+-0)=-inf */
        if (hx<0) return (x-x)/zero;        /* log(-#) = NaN */
        k -= 54;
        x *= two54; /* subnormal number, scale up x */
        GET_HIGH_WORD(hx, x);              /* high word of x */
    }
    if (hx >= 0x7ff00000) return x+x;
    k += (hx>>20)-1023;
    i  = ((uint32_t)k&0x80000000)>>31;
    hx = (hx&0x000fffff)|((0x3ff-i)<<20);
    y  = (double)(k+i);
    SET_HIGH_WORD(x,hx);
    z  = y*log10_2lo + ivln10*log(x);
    return  z+y*log10_2hi;
}
