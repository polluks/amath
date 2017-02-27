/* @(#)s_modf.c 1.3 95/01/18 */

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
 * http://www.netlib.org/fdlibm/s_modf.c
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

/*
 * modf(double x, double *iptr)
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *	Bit twiddling.
 *
 * Exception:
 *	No exception.
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double one = 1.0;
#else
static double one = 1.0;
#endif

#ifdef __STDC__
double modf(double x, double *iptr)
#else
double modf(x, iptr)
double x,*iptr;
#endif
{
    int i0,i1,j0;
    unsigned i;
    i0 =  __HI(x);		/* high x */
    i1 =  __LO(x);		/* low  x */
    j0 = ((i0>>20)&0x7ff)-0x3ff;	/* exponent of x */
    if(j0<20) {			/* integer part in high x */
        if(j0<0) {			/* |x|<1 */
            __HIp(iptr) = i0&0x80000000;
            __LOp(iptr) = 0;		/* *iptr = +-0 */
            return x;
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) {		/* x is integral */
                *iptr = x;
                __HI(x) &= 0x80000000;
                __LO(x)  = 0;	/* return +-0 */
                return x;
            } else {
                __HIp(iptr) = i0&(~i);
                __LOp(iptr) = 0;
                return x - *iptr;
            }
        }
    } else if (j0>51) {		/* no fraction part */
        *iptr = x*one;
        __HI(x) &= 0x80000000;
        __LO(x)  = 0;	/* return +-0 */
        return x;
    } else {			/* fraction part in low x */
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) { 		/* x is integral */
            *iptr = x;
            __HI(x) &= 0x80000000;
            __LO(x)  = 0;	/* return +-0 */
            return x;
        } else {
            __HIp(iptr) = i0;
            __LOp(iptr) = i1&(~i);
            return x - *iptr;
        }
    }
}
