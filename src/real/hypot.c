/* @(#)e_hypot.c 1.3 95/01/18 */

/*
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
 * The origin source code can be obtained from:
 * http://www.netlib.org/fdlibm/e_hypot.c
 * 
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 *
 */

#include "prim.h"
#include "math.h"

/* hypot(x,y)
 *
 * Method :
 *	If (assume round-to-nearest) z=x*x+y*y
 *	has error less than sqrt(2)/2 ulp, than
 *	sqrt(z) has error less than 1 ulp (exercise).
 *
 *	So, compute sqrt(x*x+y*y) with some care as
 *	follows to get the error below 1 ulp:
 *
 *	Assume x>y>0;
 *	(if possible, set rounding to round-to-nearest)
 *	1. if x > 2y  use
 *		x1*x1+(y*y+(x2*(x+x1))) for x*x+y*y
 *	where x1 = x with lower 32 bits cleared, x2 = x-x1; else
 *	2. if x <= 2y use
 *		t1*y1+((x-y)*(x-y)+(t1*y2+t2*y))
 *	where t1 = 2x with lower 32 bits cleared, t2 = 2x-t1,
 *	y1= y with lower 32 bits chopped, y2 = y-y1.
 *
 *	NOTE: scaling may be necessary if some argument is too
 *	      large or too tiny
 *
 * Special cases:
 *	hypot(x,y) is INF if x or y is +INF or -INF; else
 *	hypot(x,y) is NAN if x or y is NAN.
 *
 * Accuracy:
 * 	hypot(x,y) returns sqrt(x^2+y^2) with error less
 * 	than 1 ulps (units in the last place)
 */

double hypot(double x, double y)
{
    double a=x,b=y,t1,t2,y1,y2,w;
    uword j,k,ha,hb,hx,hy;

    GET_HIGH_WORD(hx,x);
    GET_HIGH_WORD(hy,y);
    ha = hx&0x7fffffff;	/* high word of  x */
    hb = hy&0x7fffffff;	/* high word of  y */
    if(hb > ha) {
        a=y;
        b=x;
        j=ha;
        ha=hb;
        hb=j;
    }
    else {
        a=x;
        b=y;
    }
    SET_HIGH_WORD(a,ha); /* a <- |a| */
    SET_HIGH_WORD(b,hb); /* b <- |b| */
    if((ha-hb)>0x3c00000) {
        return a+b;   /* x/y > 2**60 */
    }
    k=0;
    if(ha > 0x5f300000) {	/* a>2**500 */
        if(ha >= 0x7ff00000) {	/* Inf or NaN */
            uword la, lb;
            w = a+b;			/* for sNaN */
            GET_LOW_WORD(la,a);
            GET_LOW_WORD(lb,b);
            if(((ha&0xfffff)|la)==0) w = a;
            if(((hb^0x7ff00000)|lb)==0) w = b;
            return w;
        }
        /* scale a and b by 2**-600 */
        ha -= 0x25800000;
        hb -= 0x25800000;
        k += 600;
        SET_HIGH_WORD(a,ha);
        SET_HIGH_WORD(b,hb);
    }
    if(hb < 0x20b00000) {	/* b < 2**-500 */
        if(hb <= 0x000fffff) {	/* subnormal b or 0 */
            uword lb;
            GET_LOW_WORD(lb,b);
            if((hb|lb)==0) return a;
            t1=0;
            SET_HIGH_WORD(t1, 0x7fd00000);	/* t1=2^1022 */
            b *= t1;
            a *= t1;
            k -= 1022;
        } else {		/* scale a and b by 2^600 */
            ha += 0x25800000; 	/* a *= 2^600 */
            hb += 0x25800000;	/* b *= 2^600 */
            k -= 600;

            SET_HIGH_WORD(a,ha);
            SET_HIGH_WORD(b,hb);
        }
    }
    /* medium size a and b */
    w = a-b;
    if (w>b) {
        t1 = 0;
        SET_HIGH_WORD(t1, ha);
        t2 = a-t1;
        w  = sqrt(t1*t1-(b*(-b)-t2*(a+t1)));
    } else {
        a  = a+a;
        y1 = 0;
        SET_HIGH_WORD(y1, hb);
        y2 = b - y1;
        t1 = 0;
        SET_HIGH_WORD(t1, ha+0x00100000);
        t2 = a - t1;
        w  = sqrt(t1*y1-(w*(-w)-(t1*y2+t2*b)));
    }
    if(k!=0) {
        uword ht1;

        t1 = 1.0;
        GET_HIGH_WORD(ht1, t1);
        SET_HIGH_WORD(t1, ht1 + (k<<20));
        return t1*w;
    } else return w;
}
