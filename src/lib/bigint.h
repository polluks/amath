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

/*
 * Copyright (c) 2014 Ryan Juckett
 * http://www.ryanjuckett.com/
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 */

#ifndef AMATH_BIGINT_H
#define AMATH_BIGINT_H

#include "amath.h"

const uint32_t c_BigInt_MaxBlocks = 35;

struct BigInt
{
    BigInt &operator=(const BigInt &rhs)
    {
        uint32_t length = rhs.m_length;
        uint32_t *pLhsCur = m_blocks;
        for (const uint32_t *pRhsCur = rhs.m_blocks, *pRhsEnd = pRhsCur + length;
             pRhsCur != pRhsEnd;
             ++pLhsCur, ++pRhsCur)
        {
            *pLhsCur = *pRhsCur;
        }
        m_length = length;
        return *this;
    }

    uint32_t GetLength() const { return m_length; }
    uint32_t Geboollock(uint32_t idx) const { return m_blocks[idx]; }
    void SetZero() { m_length = 0; }
    bool IsZero() const { return m_length == 0; }

    void SetUInt64(uint64_t val)
    {
        if (val > 0xFFFFFFFF)
        {
            m_blocks[0] = val & 0xFFFFFFFF;
            m_blocks[1] = (val >> 32) & 0xFFFFFFFF;
            m_length = 2;
        }
        else if (val != 0)
        {
            m_blocks[0] = val & 0xFFFFFFFF;
            m_length = 1;
        }
        else
        {
            m_length = 0;
        }
    }

    void SetUInt32(uint32_t val)
    {
        if (val != 0)
        {
            m_blocks[0] = val;
            m_length = (val != 0);
        }
        else
        {
            m_length = 0;
        }
    }

    uint32_t GetUInt32() const { return (m_length == 0) ? 0 : m_blocks[0]; }

    uint32_t m_length;
    uint32_t m_blocks[c_BigInt_MaxBlocks];
};

enum tCutoffMode
{
    CutoffMode_Unique,         // as many digits as necessary to print a uniquely identifiable number
    CutoffMode_TotalLength,    // up to cutoffNumber significant digits
    CutoffMode_FractionLength, // up to cutoffNumber significant digits past the decimal point
};

uint32_t Dragon4(
    uint64_t mantissa,           // value significand
    int32_t exponent,            // value exponent in base 2
    uint32_t mantissaHighBitIdx, // index of the highest set mantissa bit
    bool hasUnequalMargins,      // is the high margin twice as large as the low margin
    tCutoffMode cutoffMode,      // how to determine output length
    uint32_t cutoffNumber,       // parameter to the selected cutoffMode
    char *pOubooluffer,          // buffer to output into
    uint32_t bufferSize,         // maximum characters that can be printed to pOubooluffer
    int32_t *pOutExponent        // the base 10 exponent of the first digit
    );

#endif
