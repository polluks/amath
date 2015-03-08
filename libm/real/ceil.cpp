/* @(#)s_ceil.c 1.3 95/01/18 */
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

#include "libm/rprim.h"

static const double huge = 1.0e300;

/**
 * @brief   Mathematical ceiling function.
 * @version 1.3
 * @date    95/01/18
 * @details
 * <pre>
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to ceil(x).
 * </pre>
 * @copyright Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * @license   Developed at SunSoft, a Sun Microsystems, Inc. business. Permission
 *            to use, copy, modify, and distribute this software is freely granted,
 *            provided that this notice is preserved.
 */
double ceil(double x)
{
    sword i0,i1,j0;
    uword i,j;
    EXTRACT_WORDS(i0,i1,x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) { 			/* raise inexact if x != 0 */
            if(huge+x>0.0) {		/* return 0*sign(x) if |x|<1 */
                if(i0<0) {
                    i0=0x80000000;
                    i1=0;
                }
                else if((i0|i1)!=0) {
                    i0=0x3ff00000;
                    i1=0;
                }
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {		/* raise inexact flag */
                if(i0>0) i0 += (0x00100000)>>j0;
                i0 &= (~i);
                i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;	/* inf or NaN */
        else return x;			/* x is integral */
    } else {
        i = ((uword)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x;		/* x is integral */
        if(huge+x>0.0) { 		/* raise inexact flag */
            if(i0>0) {
                if(j0==20) i0+=1;
                else {
                    j = i1 + (1<<(52-j0));
                    // NOTICE: Is this a correct cast?
                    if((sword)j<(sword)i1) i0+=1;	/* got a carry */
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    INSERT_WORDS(x,i0,i1);
    return x;
}
