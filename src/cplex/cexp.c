/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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
 * http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libm/complex/cexp.c?rev=1.1
 *
 * Project homepage:
 * https://amath.innolan.net
 * 
 */

#include "prim.h"

/**
 * @brief Returns e to the power of a complex number
 */
complex cexp(complex z)
{
    complex w;
    double r, x, y;
    x = creal(z);
    y = cimag(z);
    r = exp(x);
    w = cpack(r * cos(y), r * sin(y));
    return w;
}
