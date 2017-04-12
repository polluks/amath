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
 * http://www.netlib.org/fdlibm/e_fmod.c
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
 * @file  fmod.c
 * @brief Return x mod y in exact arithmetic
 */

#include "prim.h"

static const double
    one = 1.0,
    Zero[] = {
        0.0, -0.0,
};

/**
 * @brief   Return x mod y in exact arithmetic
 * @details Method: Shift and subtract
 */
double fmod(double x, double y)
{
    int32_t n, hx, hy, hz, ix, iy, sx, i;
    uint32_t lx, ly, lz;

    EXTRACT_WORDS(hx, lx, x);
    EXTRACT_WORDS(hy, ly, y);
    sx = hx & 0x80000000; /* sign of x */
    hx ^= sx;             /* |x| */
    hy &= 0x7fffffff;     /* |y| */

    /* purge off exception values */
    if ((hy | ly) == 0 || (hx >= 0x7ff00000) ||   /* y=0,or x not finite */
        ((hy | ((ly | -ly) >> 31)) > 0x7ff00000)) /* or y is NaN */
        return (x * y) / (x * y);
    if (hx <= hy)
    {
        if ((hx < hy) || (lx < ly))
            return x; /* |x|<|y| return x */
        if (lx == ly)
            return Zero[(uint32_t)sx >> 31]; /* |x|=|y| return x*0*/
    }

    /* determine ix = ilogb(x) */
    if (hx < 0x00100000)
    { /* subnormal x */
        if (hx == 0)
        {
            for (ix = -1043, i = lx; i > 0; i <<= 1)
                ix -= 1;
        }
        else
        {
            for (ix = -1022, i = (hx << 11); i > 0; i <<= 1)
                ix -= 1;
        }
    }
    else
        ix = (hx >> 20) - 1023;

    /* determine iy = ilogb(y) */
    if (hy < 0x00100000)
    { /* subnormal y */
        if (hy == 0)
        {
            for (iy = -1043, i = ly; i > 0; i <<= 1)
                iy -= 1;
        }
        else
        {
            for (iy = -1022, i = (hy << 11); i > 0; i <<= 1)
                iy -= 1;
        }
    }
    else
        iy = (hy >> 20) - 1023;

    /* set up {hx,lx}, {hy,ly} and align y to x */
    if (ix >= -1022)
        hx = 0x00100000 | (0x000fffff & hx);
    else
    { /* subnormal x, shift x to normal */
        n = -1022 - ix;
        if (n <= 31)
        {
            hx = (hx << n) | (lx >> (32 - n));
            lx <<= n;
        }
        else
        {
            hx = lx << (n - 32);
            lx = 0;
        }
    }
    if (iy >= -1022)
        hy = 0x00100000 | (0x000fffff & hy);
    else
    { /* subnormal y, shift y to normal */
        n = -1022 - iy;
        if (n <= 31)
        {
            hy = (hy << n) | (ly >> (32 - n));
            ly <<= n;
        }
        else
        {
            hy = ly << (n - 32);
            ly = 0;
        }
    }

    /* fix point fmod */
    n = ix - iy;
    while (n--)
    {
        hz = hx - hy;
        lz = lx - ly;
        if (lx < ly)
            hz -= 1;
        if (hz < 0)
        {
            hx = hx + hx + (lx >> 31);
            lx = lx + lx;
        }
        else
        {
            if ((hz | lz) == 0) /* return sign(x)*0 */
                return Zero[(uint32_t)sx >> 31];
            hx = hz + hz + (lz >> 31);
            lx = lz + lz;
        }
    }
    hz = hx - hy;
    lz = lx - ly;
    if (lx < ly)
        hz -= 1;
    if (hz >= 0)
    {
        hx = hz;
        lx = lz;
    }

    /* convert back to floating value and restore the sign */
    if ((hx | lx) == 0) /* return sign(x)*0 */
        return Zero[(unsigned)sx >> 31];
    while (hx < 0x00100000)
    { /* normalize x */
        hx = hx + hx + (lx >> 31);
        lx = lx + lx;
        iy -= 1;
    }
    if (iy >= -1022)
    { /* normalize output */
        hx = ((hx - 0x00100000) | ((iy + 1023) << 20));
        INSERT_WORDS(x, hx | sx, lx);
    }
    else
    { /* subnormal output */
        n = -1022 - iy;
        if (n <= 20)
        {
            lx = (lx >> n) | ((uint32_t)hx << (32 - n));
            hx >>= n;
        }
        else if (n <= 31)
        {
            lx = (hx << (32 - n)) | (lx >> n);
            hx = sx;
        }
        else
        {
            lx = hx >> (n - 32);
            hx = sx;
        }
        INSERT_WORDS(x, hx | sx, lx);
        x *= one; /* create necessary signal */
    }
    return x; /* exact output */
}
