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
 * @brief   Inverse hyperbolic tangent of complex number
 * @version 1.0
 * @date    14/09/15
 * @details
 * Inverse hyperbolic tangent expressed using complex logarithms:
 * <pre>
 * atanh(z) = 1/2 * ((log(1 + z) - log(1 - z))
 * </pre>
 * More info is available at Wikipedia: <BR>
 * http://en.wikipedia.org/wiki/Inverse_hyperbolic_function#Logarithmic_representation
 */
complex catanh(complex z)
{
    complex half = cpack(0.5, 0.0);
    complex one = cpack(1.0, 0.0);
    complex a = clog(cadd(one, z));
    complex b = clog(csub(one, z));
    complex c = csub(a, b);
    complex w = cmul(half, c);
    return w;
}
