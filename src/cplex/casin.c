/*-
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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#include "prim.h"
#include "math.h"
#include "complex.h"

/**
 * @brief   Inverse sine of complex number
 * @version 1.1
 * @date    14/10/01
 * @details
 * Inverse sine expressed using complex logarithms:
 * <pre>
 * arcsin z = -i * log(iz + sqrt(1 - z*z))
 * </pre>
 * More info is available at Wikipedia: <BR>
 * https://wikipedia.org/wiki/Inverse_trigonometric_functions#Logarithmic_forms
 */
complex casin(complex z)
{
    complex one = cpack(1.0, 0.0);
    complex i = cpack(0.0, 1.0);
    complex j = cpack(0.0, -1.0);
    complex iz = cmul(i, z);
    complex z2 = cmul(z, z);
    complex p = csqrt(csub(one, z2));
    complex q = clog(cadd(iz, p));
    complex w = cmul(j, q);
    return w;
}
