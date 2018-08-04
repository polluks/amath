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

/**
 * @file  trunc.c
 * @brief Truncate function
 */

#include "prim.h"

/**
 * @brief   Truncate function
 * @details
 * <pre>
 * when x > 0
 * trunc(0)   = floor(x)
 *
 * when x < 0
 * trunc(x)   = ceil(x)
 *
 * Special case
 * trunc(0)   = 0
 * trunc(NaN) = NaN
 * </pre>
 */
double trunc(double x)
{
    uint32_t hx, lx;
    GET_HIGH_WORD(hx, x);
    if ((hx & 0x7FF00000) == 0x7FF00000)
    {
        return NAN;
    }

    GET_LOW_WORD(lx, x);
    if (hx == 0 && lx == 0)
    {
        return 0.0;
    }

    if ((hx & 0x80000000) != 0x80000000)
    {
        return floor(x);
    }

    return ceil(x);
}
