/* $NetBSD: ccosh.c,v 1.1 2007/08/20 16:01:33 drochner Exp $ */

/*
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The origin source code can be obtained from:
 * http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libm/complex/ccosh.c?rev=1.1
 *
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Hyperbolic cosine of a complex number
 * @version 1.1
 * @date    2007/08/20
 * @details
 * <pre>
 * a+bi
 * real = cosh(a) * cos(b)
 * imag = sinh(a) * sin(b)
 * </pre>
 */
complex ccosh(complex z)
{
    complex w;
    double a, b;
    double ch, sh;

    a = creal(z);
    b = cimag(z);
    cchsh(a, &ch, &sh);
    w = cpack(cos(b) * ch, sin(b) * sh);

    return w;
}
