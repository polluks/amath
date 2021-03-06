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
 * http://www.netlib.org/fdlibm/s_scalbn.c
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

#include "prim.h"

/*
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent
 * manipulation rather than by actually performing an
 * exponentiation or a multiplication.
 */

static const double
    two54 = 1.80143985094819840000e+16,  /* 0x43500000, 0x00000000 */
    twom54 = 5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
    huge = 1.0e+300,
    tiny = 1.0e-300;

double scalbn(double x, int32_t n)
{
    int32_t k, hx, lx;
    EXTRACT_WORDS(hx, lx, x);
    k = (hx & 0x7ff00000) >> 20; /* extract exponent */
    if (k == 0)
    { /* 0 or subnormal x */
        if ((lx | (hx & 0x7fffffff)) == 0)
            return x; /* +-0 */
        x *= two54;
        GET_HIGH_WORD(hx, x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000)
            return tiny * x; /*underflow*/
    }
    if (k == 0x7ff)
        return x + x; /* NaN or Inf */
    k = k + n;
    if (k > 0x7fe)
        return huge * copysign(huge, x); /* overflow  */
    if (k > 0)                           /* normal result */
    {
        SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
        return x;
    }
    if (k <= -54)
    {
        if (n > 50000)                       /* in case integer overflow in n+k */
            return huge * copysign(huge, x); /*overflow*/
        else
            return tiny * copysign(tiny, x); /*underflow*/
    }
    k += 54; /* subnormal result */
    SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x * twom54;
}
