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
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Inverse tangent of complex number
 * @version 1.1
 * @date    14/10/01
 * @details
 * Inverse tangent expressed using complex logarithms:
 * <pre>
 * atan(z) = i/2 * (log(1 - i * z) - log(1 + i * z))
 * </pre>
 * More info is available at Wikipedia: <BR>
 * http://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Logarithmic_forms
 */
complex catan(complex z)
{
    complex one = cpack(1.0, 0.0);
    complex two = cpack(2.0, 0.0);
    complex i = cpack(0.0, 1.0);
    complex iz = cmul(i, z);
    complex p = clog(csub(one, iz));
    complex q = clog(cadd(one, iz));
    complex w = cmul(cdiv(i, two), csub(p, q));
    return w;
}
