/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
 * Copyright (c) 2007 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software written by Stephen L. Moshier.
 * It is redistributed by the NetBSD Foundation by permission of the author.
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
 * The original source code can be obtained from:
 * http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libm/complex/ctan.c?rev=1.1
 *
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Tangent of a complex number
 * @version 1.1
 * @date    2007/08/20
 * @details
 * Calculated as in Open Office:<BR>
 * https://wiki.openoffice.org/wiki/Documentation/How_Tos/Calc:_IMTAN_function
 * <pre>
 * a+bi
 *                sin(2.0 * a)
 * real  = ------------------------------
 *          cos(2.0 * a) + cosh(2.0 * b)
 *
 *                sinh(2.0 * b)
 * imag  = ------------------------------
 *          cos(2.0 * a) + cosh(2.0 * b)
 * </pre>
 */
complex ctan(complex z)
{
    complex w;
    double a, b;
    double d;

    a = creal(z);
    b = cimag(z);
    d = cos(2.0 * a) + cosh(2.0 * b);

    if (d == 0.0) {
        w = cpack(D_INFP, D_INFP);
    } else {
        w = cpack((sin(2.0 * a) / d), (sinh(2.0 * b) / d));
    }

    return w;
}
