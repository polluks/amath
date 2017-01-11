/* @(#)s_nextafter.c 1.3 95/01/18 */

/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
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
 * http://www.netlib.org/fdlibm/s_nextafter.c
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
 */

// NOTICE: Not a part of libamath yet

/* IEEE functions
 *	nextafter(x,y)
 *	return the next machine floating-point number of x in the
 *	direction toward y.
 *   Special cases:
 */

#include "fdlibm.h"

#ifdef __STDC__
double nextafter(double x, double y)
#else
double nextafter(x,y)
double x,y;
#endif
{
    int	hx,hy,ix,iy;
    unsigned lx,ly;

    hx = __HI(x);		/* high word of x */
    lx = __LO(x);		/* low  word of x */
    hy = __HI(y);		/* high word of y */
    ly = __LO(y);		/* low  word of y */
    ix = hx&0x7fffffff;		/* |x| */
    iy = hy&0x7fffffff;		/* |y| */

    if(((ix>=0x7ff00000)&&((ix-0x7ff00000)|lx)!=0) ||   /* x is nan */
            ((iy>=0x7ff00000)&&((iy-0x7ff00000)|ly)!=0))     /* y is nan */
        return x+y;
    if(x==y) return x;		/* x=y, return x */
    if((ix|lx)==0) {			/* x == 0 */
        __HI(x) = hy&0x80000000;	/* return +-minsubnormal */
        __LO(x) = 1;
        y = x*x;
        if(y==x) return y;
        else return x;	/* raise underflow flag */
    }
    if(hx>=0) {				/* x > 0 */
        if(hx>hy||((hx==hy)&&(lx>ly))) {	/* x > y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {				/* x < y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    } else {				/* x < 0 */
        if(hy>=0||hx>hy||((hx==hy)&&(lx>ly))) { /* x < y, x -= ulp */
            if(lx==0) hx -= 1;
            lx -= 1;
        } else {				/* x > y, x += ulp */
            lx += 1;
            if(lx==0) hx += 1;
        }
    }
    hy = hx&0x7ff00000;
    if(hy>=0x7ff00000) return x+x;	/* overflow  */
    if(hy<0x00100000) {		/* underflow */
        y = x*x;
        if(y!=x) {		/* raise underflow flag */
            __HI(y) = hx;
            __LO(y) = lx;
            return y;
        }
    }
    __HI(x) = hx;
    __LO(x) = lx;
    return x;
}
