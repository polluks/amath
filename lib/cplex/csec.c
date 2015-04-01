/*
 * Copyright (c) 2015 Carsten Larsen
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
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Secant of a complex number
 * @details
 * Calculated as in Open Office:<BR>
 * https://wiki.openoffice.org/wiki/Documentation/How_Tos/Calc:_IMSEC_function
 * <pre>
 * a+bi
 *             2.0 * cos(a) * cosh(b)
 * real  = ------------------------------
 *          cosh(2.0 * b) + cos(2.0 * a)
 *
 *             2.0 * sin(a) * sinh(b)
 * imag  = ------------------------------
 *          cosh(2.0 * b) + cos(2.0 * a)
 * </pre>
 */
complex csec(complex z)
{
    complex w;
    double a, b;
    double d;

    a = creal(z);
    b = cimag(z);
    d = cosh(2.0 * b) + cos(2.0 * a);

    if (d == 0.0) {
        w = cpack(HUGE, HUGE); // TODO: INF, INF
    } else {
        w = cpack((2.0 * cos(a) * cosh(b) / d), (2.0 * sin(a) * sinh(b) / d));
    }

    return w;
}
