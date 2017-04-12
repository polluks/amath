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
 * http://www.netlib.org/fdlibm/e_atan2.c
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
 * @file  atan2.c
 * @brief Inverse tangent function
 */

#include "prim.h"

static const double
    tiny = 1.0e-300,
    zero = 0.0,
    pi_o_4 = 7.8539816339744827900E-01, /* 0x3FE921FB, 0x54442D18 */
    pi_o_2 = 1.5707963267948965580E+00, /* 0x3FF921FB, 0x54442D18 */
    pi = 3.1415926535897931160E+00,     /* 0x400921FB, 0x54442D18 */
    pi_lo = 1.2246467991473531772E-16;  /* 0x3CA1A626, 0x33145C07 */


/**
 * @brief   Inverse tangent function
 * @param   y,x  
 * @details
 * <pre>
 * Method
 *     1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
 *     2. Reduce x to positive by (if x and y are unexceptional):
 *        ARG (x+iy) = arctan(y/x)           ... if x > 0,
 *        ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
 *
 * Special cases
 *     ATAN2((anything), NaN ) is NaN;
 *     ATAN2(NAN , (anything) ) is NaN;
 *     ATAN2(+-0, +(anything but NaN)) is +-0  ;
 *     ATAN2(+-0, -(anything but NaN)) is +-pi ;
 *     ATAN2(+-(anything but 0 and NaN), 0) is +-pi/2;
 *     ATAN2(+-(anything but INF and NaN), +INF) is +-0 ;
 *     ATAN2(+-(anything but INF and NaN), -INF) is +-pi;
 *     ATAN2(+-INF,+INF ) is +-pi/4 ;
 *     ATAN2(+-INF,-INF ) is +-3pi/4;
 *     ATAN2(+-INF, (anything but,0,NaN, and INF)) is +-pi/2;
 *
 * Constants
 *     The hexadecimal values are the intended ones for the following
 *     constants. The decimal values may be used, provided that the
 *     compiler will convert from decimal to binary accurately enough
 *     to produce the hexadecimal values shown.
 * </pre>
 */
double atan2(double y, double x)
{
    double z;
    int32_t k, m, hx, hy, ix, iy;
    uint32_t lx, ly;

    EXTRACT_WORDS(hx, lx, x);
    ix = hx & 0x7fffffff;
    EXTRACT_WORDS(hy, ly, y);
    iy = hy & 0x7fffffff;
    if (((ix | ((lx | -lx) >> 31)) > 0x7ff00000) ||
        ((iy | ((ly | -ly) >> 31)) > 0x7ff00000)) /* x or y is NaN */
        return x + y;
    if (((hx - 0x3ff00000) | lx) == 0)
        return atan(y);                      /* x=1.0 */
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2); /* 2*sign(x)+sign(y) */

    /* when y = 0 */
    if ((iy | ly) == 0)
    {
        switch (m)
        {
        case 0:
        case 1:
            return y; /* atan(+-0,+anything)=+-0 */
        case 2:
            return pi + tiny; /* atan(+0,-anything) = pi */
        case 3:
            return -pi - tiny; /* atan(-0,-anything) =-pi */
        }
    }
    /* when x = 0 */
    if ((ix | lx) == 0)
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;

    /* when x is INF */
    if (ix == 0x7ff00000)
    {
        if (iy == 0x7ff00000)
        {
            switch (m)
            {
            case 0:
                return pi_o_4 + tiny; /* atan(+INF,+INF) */
            case 1:
                return -pi_o_4 - tiny; /* atan(-INF,+INF) */
            case 2:
                return 3.0 * pi_o_4 + tiny; /*atan(+INF,-INF)*/
            case 3:
                return -3.0 * pi_o_4 - tiny; /*atan(-INF,-INF)*/
            }
        }
        else
        {
            switch (m)
            {
            case 0:
                return zero; /* atan(+...,+INF) */
            case 1:
                return -zero; /* atan(-...,+INF) */
            case 2:
                return pi + tiny; /* atan(+...,-INF) */
            case 3:
                return -pi - tiny; /* atan(-...,-INF) */
            }
        }
    }
    /* when y is INF */
    if (iy == 0x7ff00000)
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;

    /* compute y/x */
    k = (iy - ix) >> 20;
    if (k > 60)
        z = pi_o_2 + 0.5 * pi_lo; /* |y/x| >  2**60 */
    else if (hx < 0 && k < -60)
        z = 0.0; /* |y|/x < -2**60 */
    else
        z = atan(fabs(y / x)); /* safe to do y/x */
    switch (m)
    {
    case 0:
        return z; /* atan(+,+) */
    case 1:
    {
        uint32_t zh;
        GET_HIGH_WORD(zh, z);
        SET_HIGH_WORD(z, zh ^ 0x80000000);
    }
        return z; /* atan(-,+) */
    case 2:
        return pi - (z - pi_lo); /* atan(+,-) */
    default:                     /* case 3 */
        return (z - pi_lo) - pi; /* atan(-,-) */
    }
}
