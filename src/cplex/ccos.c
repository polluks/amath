/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
 * Copyright (c) 2007 The NetBSD Foundation, Inc.
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
 * The original source code can be obtained from:
 * http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libm/complex/ccos.c?rev=1.1
 *
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Cosine of complex number
 * @version 1.1
 * @date    2007/08/20
 * @details
 * <pre>
 * a+bi
 * real =  cos(a) * cosh(b)
 * imag = -sin(a) * sinh(b)
 * </pre>
 */
complex ccos(complex z)
{
    complex w;
    double a, b;
    double ch, sh;

    a = creal(z);
    b = cimag(z);
    cchsh(b, &ch, &sh);
    w = cpack((cos(a) * ch), (-sin(a) * sh));

    return w;
}
