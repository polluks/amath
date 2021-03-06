/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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
 * https://amath.innolan.net
 * 
 */

#include "prim.h"

/**
 * @brief   Inverse secant expressed using complex logarithms:
 * @details
 * Inverse secant expressed using complex logarithms:
 * <pre>
 * arcsec z = -i * log(i * sqr(1 - 1/(z*z)) + 1/z)
 * </pre>
 * More info is available at Wikipedia: <BR>
 * https://wikipedia.org/wiki/Inverse_trigonometric_functions#Logarithmic_forms
 */
complex casec(complex z)
{
    complex one = cpack(1.0, 0.0);
    complex i = cpack(0.0, 1.0);
    complex j = cpack(0.0, -1.0);
    complex rz = creci(z);
    complex z2 = cmul(z, z);
    complex p = cdiv(one, z2);
    complex q = csqrt(csub(one, p));
    complex w = cmul(j, clog(cadd(cmul(i, q), rz)));
    return w;
}
