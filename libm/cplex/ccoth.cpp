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

#include "libm/cprim.h"
#include "libm/rfunc.h"

/**
 * @brief   Hyperbolic cotangent of a complex number
 * @details
 * <pre>
 * acoth(z) = 0.5 * (log(1 + 1/z) - log(1 - 1/z))
 * </pre>
 * or
 * <pre>
 * a+bi
 *                sinh(2.0 * a)
 * real  = ------------------------------
 *          cosh(2.0 * a) - cos(2.0 * b)
 *
 *                -sin(2.0 * b)
 * imag  = ------------------------------
 *          cosh(2.0 * a) - cos(2.0 * b)
 * </pre>
 */
complex ccoth(complex z)
{
    complex w;
    double a, b;
    double d;

    a = creal(z);
    b = cimag(z);
    d = cosh(2.0 * a) - cos(2.0 * b);
    w = cpack(sinh(2.0 * a) / d, -sin(2.0 * b) / d);

    return w;
}
