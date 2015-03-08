/* @(#)e_atanh.c 1.3 95/01/18 */
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
#include "libm/rfunc.h"

static const double one = 1.0, huge = 1e300;
static double zero = 0.0;

/**
 * @brief   Inverse hyperbolic tangent function.
 * @version 1.3
 * @date    95/01/18
 * @details
 * <pre>
 * Method :
 *    1.Reduced x to positive by atanh(-x) = -atanh(x)
 *    2.For x>=0.5
 *                  1              2x                          x
 *	atanh(x) = --- * log(1 + -------) = 0.5 * log1p(2 * --------)
 *                  2             1 - x                      1 - x
 *
 * 	For x<0.5
 *	atanh(x) = 0.5*log1p(2x+2x*x/(1-x))
 *
 * Special cases:
 *	atanh(x) is NaN if |x| > 1 with signal;
 *	atanh(NaN) is that NaN with no signal;
 *	atanh(+-1) is +-INF with signal.
 * </pre>
 * @copyright Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * @license   Developed at SunSoft, a Sun Microsystems, Inc. business. Permission
 *            to use, copy, modify, and distribute this software is freely granted,
 *            provided that this notice is preserved.
 */

double atanh(double x)
{
    double t;
    sword hx,ix;
    uword lx;
    GET_HIGH_WORD(hx,x);
    GET_LOW_WORD(lx,x);
    ix = hx&0x7fffffff;
    if ((ix|((lx|(-lx))>>31))>0x3ff00000) /* |x|>1 */
        return (x-x)/(x-x);
    if(ix==0x3ff00000)
        return x/zero;
    if(ix<0x3e300000&&(huge+x)>zero) return x;	/* x<2**-28 */
    SET_HIGH_WORD(x, ix);		/* x <- |x| */
    if(ix<0x3fe00000) {		/* x < 0.5 */
        t = x+x;
        t = 0.5*log1p(t+t*x/(one-x));
    } else
        t = 0.5*log1p((x+x)/(one-x));
    if(hx>=0) return t;
    else return -t;
}
