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
 * 2. Altered source versions must be plainly marked as such, and must not
 *     be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 */

#include "bigint.h"
#include "mathr.h"

static int32_t BigInt_Compare(const BigInt &lhs, const BigInt &rhs)
{
    // A bigger length implies a bigger number.
    int32_t lengthDiff = lhs.m_length - rhs.m_length;
    if (lengthDiff != 0)
        return lengthDiff;

    // Compare blocks one by one from high to low.
    for (int32_t i = lhs.m_length - 1; i >= 0; --i)
    {
        if (lhs.m_blocks[i] == rhs.m_blocks[i])
            continue;
        else if (lhs.m_blocks[i] > rhs.m_blocks[i])
            return 1;
        else
            return -1;
    }

    // no blocks differed
    return 0;
}

static void BigInt_Add(BigInt *pResult, const BigInt &lhs, const BigInt &rhs)
{
    // determine which operand has the smaller length
    const BigInt *pLarge;
    const BigInt *pSmall;
    if (lhs.m_length < rhs.m_length)
    {
        pSmall = &lhs;
        pLarge = &rhs;
    }
    else
    {
        pSmall = &rhs;
        pLarge = &lhs;
    }

    const uint32_t largeLen = pLarge->m_length;
    const uint32_t smallLen = pSmall->m_length;

    // The output will be at least as long as the largest input
    pResult->m_length = largeLen;

    // Add each block and add carry the overflow to the next block
    uint64_t carry = 0;
    const uint32_t *pLargeCur = pLarge->m_blocks;
    const uint32_t *pLargeEnd = pLargeCur + largeLen;
    const uint32_t *pSmallCur = pSmall->m_blocks;
    const uint32_t *pSmallEnd = pSmallCur + smallLen;
    uint32_t *pResultCur = pResult->m_blocks;
    while (pSmallCur != pSmallEnd)
    {
        uint64_t sum = carry + (uint64_t)(*pLargeCur) + (uint64_t)(*pSmallCur);
        carry = sum >> 32;
        (*pResultCur) = sum & 0xFFFFFFFF;
        ++pLargeCur;
        ++pSmallCur;
        ++pResultCur;
    }

    // Add the carry to any blocks that only exist in the large operand
    while (pLargeCur != pLargeEnd)
    {
        uint64_t sum = carry + (uint64_t)(*pLargeCur);
        carry = sum >> 32;
        (*pResultCur) = sum & 0xFFFFFFFF;
        ++pLargeCur;
        ++pResultCur;
    }

    // If there's still a carry, append a new block
    if (carry != 0)
    {
        assert(carry == 1);
        assert((uint32_t)(pResultCur - pResult->m_blocks) == largeLen && (largeLen < c_BigInt_MaxBlocks));
        *pResultCur = 1;
        pResult->m_length = largeLen + 1;
    }
    else
    {
        pResult->m_length = largeLen;
    }
}

static void BigInt_Multiply(BigInt *pResult, const BigInt &lhs, const BigInt &rhs)
{
    assert(pResult != &lhs && pResult != &rhs);

    // determine which operand has the smaller length
    const BigInt *pLarge;
    const BigInt *pSmall;
    if (lhs.m_length < rhs.m_length)
    {
        pSmall = &lhs;
        pLarge = &rhs;
    }
    else
    {
        pSmall = &rhs;
        pLarge = &lhs;
    }

    // set the maximum possible result length
    uint32_t maxResultLen = pLarge->m_length + pSmall->m_length;
    assert(maxResultLen <= c_BigInt_MaxBlocks);

    // clear the result data
    for (uint32_t *pCur = pResult->m_blocks, *pEnd = pCur + maxResultLen; pCur != pEnd; ++pCur)
        *pCur = 0;

    // perform standard long multiplication
    const uint32_t *pLargeBeg = pLarge->m_blocks;
    const uint32_t *pLargeEnd = pLargeBeg + pLarge->m_length;

    // for each small block
    uint32_t *pResultStart = pResult->m_blocks;
    for (const uint32_t *pSmallCur = pSmall->m_blocks, *pSmallEnd = pSmallCur + pSmall->m_length;
         pSmallCur != pSmallEnd;
         ++pSmallCur, ++pResultStart)
    {
        // if non-zero, multiply against all the large blocks and add into the result
        const uint32_t multiplier = *pSmallCur;
        if (multiplier != 0)
        {
            const uint32_t *pLargeCur = pLargeBeg;
            uint32_t *pResultCur = pResultStart;
            uint64_t carry = 0;
            do
            {
                uint64_t product = (*pResultCur) + (*pLargeCur) * (uint64_t)multiplier + carry;
                carry = product >> 32;
                *pResultCur = product & 0xFFFFFFFF;
                ++pLargeCur;
                ++pResultCur;
            } while (pLargeCur != pLargeEnd);

            assert(pResultCur < pResult->m_blocks + maxResultLen);
            *pResultCur = (uint32_t)(carry & 0xFFFFFFFF);
        }
    }

    // check if the terminating block has no set bits
    if (maxResultLen > 0 && pResult->m_blocks[maxResultLen - 1] == 0)
        pResult->m_length = maxResultLen - 1;
    else
        pResult->m_length = maxResultLen;
}

static void BigInt_Multiply(BigInt *pResult, const BigInt &lhs, uint32_t rhs)
{
    // perform long multiplication
    uint32_t carry = 0;
    uint32_t *pResultCur = pResult->m_blocks;
    const uint32_t *pLhsCur = lhs.m_blocks;
    const uint32_t *pLhsEnd = lhs.m_blocks + lhs.m_length;
    for (; pLhsCur != pLhsEnd; ++pLhsCur, ++pResultCur)
    {
        uint64_t product = (uint64_t)(*pLhsCur) * rhs + carry;
        *pResultCur = (uint32_t)(product & 0xFFFFFFFF);
        carry = product >> 32;
    }

    // if there is a remaining carry, grow the array
    if (carry != 0)
    {
        // grow the array
        assert(lhs.m_length + 1 <= c_BigInt_MaxBlocks);
        *pResultCur = (uint32_t)carry;
        pResult->m_length = lhs.m_length + 1;
    }
    else
    {
        pResult->m_length = lhs.m_length;
    }
}

static void BigInt_Multiply2(BigInt *pResult, const BigInt &in)
{
    // shift all the blocks by one
    uint32_t carry = 0;

    uint32_t *pResultCur = pResult->m_blocks;
    const uint32_t *pLhsCur = in.m_blocks;
    const uint32_t *pLhsEnd = in.m_blocks + in.m_length;
    for (; pLhsCur != pLhsEnd; ++pLhsCur, ++pResultCur)
    {
        uint32_t cur = *pLhsCur;
        *pResultCur = (cur << 1) | carry;
        carry = cur >> 31;
    }

    if (carry != 0)
    {
        // grow the array
        assert(in.m_length + 1 <= c_BigInt_MaxBlocks);
        *pResultCur = carry;
        pResult->m_length = in.m_length + 1;
    }
    else
    {
        pResult->m_length = in.m_length;
    }
}

static void BigInt_Multiply2(BigInt *pResult)
{
    // shift all the blocks by one
    uint32_t carry = 0;

    uint32_t *pCur = pResult->m_blocks;
    uint32_t *pEnd = pResult->m_blocks + pResult->m_length;
    for (; pCur != pEnd; ++pCur)
    {
        uint32_t cur = *pCur;
        *pCur = (cur << 1) | carry;
        carry = cur >> 31;
    }

    if (carry != 0)
    {
        // grow the array
        assert(pResult->m_length + 1 <= c_BigInt_MaxBlocks);
        *pCur = carry;
        ++pResult->m_length;
    }
}

static void BigInt_Multiply10(BigInt *pResult)
{
    // multiply all the blocks
    uint64_t carry = 0;

    uint32_t *pCur = pResult->m_blocks;
    uint32_t *pEnd = pResult->m_blocks + pResult->m_length;
    for (; pCur != pEnd; ++pCur)
    {
        uint64_t product = (uint64_t)(*pCur) * 10ull + carry;
        (*pCur) = (uint32_t)(product & 0xFFFFFFFF);
        carry = product >> 32;
    }

    if (carry != 0)
    {
        // grow the array
        assert(pResult->m_length + 1 <= c_BigInt_MaxBlocks);
        *pCur = (uint32_t)carry;
        ++pResult->m_length;
    }
}

static uint32_t g_PowerOf10_U32[] =
    {
        1,        // 10 ^ 0
        10,       // 10 ^ 1
        100,      // 10 ^ 2
        1000,     // 10 ^ 3
        10000,    // 10 ^ 4
        100000,   // 10 ^ 5
        1000000,  // 10 ^ 6
        10000000, // 10 ^ 7
};

static BigInt g_PowerOf10_Big[] =
    {
        // 10 ^ 8
        {1,
         {100000000}},
        // 10 ^ 16
        {2,
         {0x6fc10000, 0x002386f2}},
        // 10 ^ 32
        {4, {
                0x00000000, 0x85acef81, 0x2d6d415b, 0x000004ee,
            }},
        // 10 ^ 64
        {7, {
                0x00000000, 0x00000000, 0xbf6a1f01, 0x6e38ed64, 0xdaa797ed, 0xe93ff9f4, 0x00184f03,
            }},
        // 10 ^ 128
        {14, {
                 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x2e953e01, 0x03df9909, 0x0f1538fd, 0x2374e42f, 0xd3cff5ec, 0xc404dc08, 0xbccdb0da, 0xa6337f19, 0xe91f2603, 0x0000024e,
             }},
        // 10 ^ 256
        {27, {
                 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x982e7c01, 0xbed3875b, 0xd8d99f72, 0x12152f87, 0x6bde50c6, 0xcf4a6e70, 0xd595d80f, 0x26b2716e, 0xadc666b0, 0x1d153624, 0x3c42d35a, 0x63ff540e, 0xcc5573c0, 0x65f9ef17, 0x55bc28f2, 0x80dcc7f7, 0xf46eeddc, 0x5fdcefce, 0x000553f7,
             }}};

static void BigInt_Pow10(BigInt *pResult, uint32_t exponent)
{
    // make sure the exponent is within the bounds of the lookup table data
    assert(exponent < 512);

    // create two temporary values to reduce large integer copy operations
    BigInt temp1;
    BigInt temp2;
    BigInt *pCurTemp = &temp1;
    BigInt *pNextTemp = &temp2;

    // initialize the result by looking up a 32-bit power of 10 corresponding to the first 3 bits
    uint32_t smallExponent = exponent & 0x7;
    pCurTemp->SetUInt32(g_PowerOf10_U32[smallExponent]);

    // remove the low bits that we used for the 32-bit lookup table
    exponent >>= 3;
    uint32_t tableIdx = 0;

    // while there are remaining bits in the exponent to be processed
    while (exponent != 0)
    {
        // if the current bit is set, multiply it with the corresponding power of 10
        if (exponent & 1)
        {
            // multiply into the next temporary
            BigInt_Multiply(pNextTemp, *pCurTemp, g_PowerOf10_Big[tableIdx]);

            // swap to the next temporary
            BigInt *pSwap = pCurTemp;
            pCurTemp = pNextTemp;
            pNextTemp = pSwap;
        }

        // advance to the next bit
        ++tableIdx;
        exponent >>= 1;
    }

    // output the result
    *pResult = *pCurTemp;
}

static void BigInt_MultiplyPow10(BigInt *pResult, const BigInt &in, uint32_t exponent)
{
    // make sure the exponent is within the bounds of the lookup table data
    assert(exponent < 512);

    // create two temporary values to reduce large integer copy operations
    BigInt temp1;
    BigInt temp2;
    BigInt *pCurTemp = &temp1;
    BigInt *pNextTemp = &temp2;

    // initialize the result by looking up a 32-bit power of 10 corresponding to the first 3 bits
    uint32_t smallExponent = exponent & 0x7;
    if (smallExponent != 0)
    {
        BigInt_Multiply(pCurTemp, in, g_PowerOf10_U32[smallExponent]);
    }
    else
    {
        *pCurTemp = in;
    }

    // remove the low bits that we used for the 32-bit lookup table
    exponent >>= 3;
    uint32_t tableIdx = 0;

    // while there are remaining bits in the exponent to be processed
    while (exponent != 0)
    {
        // if the current bit is set, multiply it with the corresponding power of 10
        if (exponent & 1)
        {
            // multiply into the next temporary
            BigInt_Multiply(pNextTemp, *pCurTemp, g_PowerOf10_Big[tableIdx]);

            // swap to the next temporary
            BigInt *pSwap = pCurTemp;
            pCurTemp = pNextTemp;
            pNextTemp = pSwap;
        }

        // advance to the next bit
        ++tableIdx;
        exponent >>= 1;
    }

    // output the result
    *pResult = *pCurTemp;
}

static inline void BigInt_Pow2(BigInt *pResult, uint32_t exponent)
{
    uint32_t blockIdx = exponent / 32;
    assert(blockIdx < c_BigInt_MaxBlocks);

    for (uint32_t i = 0; i <= blockIdx; ++i)
        pResult->m_blocks[i] = 0;

    pResult->m_length = blockIdx + 1;

    uint32_t bitIdx = (exponent % 32);
    pResult->m_blocks[blockIdx] |= (1 << bitIdx);
}

static uint32_t BigInt_DivideWithRemainder_MaxQuotient9(BigInt *pDividend, const BigInt &divisor)
{
    // Check that the divisor has been correctly shifted into range and that it is not
    // smaller than the dividend in length.
    assert(!divisor.IsZero() &&
           divisor.m_blocks[divisor.m_length - 1] >= 8 &&
           divisor.m_blocks[divisor.m_length - 1] < 0xFFFFFFFF &&
           pDividend->m_length <= divisor.m_length);

    // If the dividend is smaller than the divisor, the quotient is zero and the divisor is already
    // the remainder.
    uint32_t length = divisor.m_length;
    if (pDividend->m_length < divisor.m_length)
        return 0;

    const uint32_t *pFinalDivisorBlock = divisor.m_blocks + length - 1;
    uint32_t *pFinalDividendBlock = pDividend->m_blocks + length - 1;

    // Compute an estimated quotient based on the high block value. This will either match the actual quotient or
    // undershoot by one.
    uint32_t quotient = *pFinalDividendBlock / (*pFinalDivisorBlock + 1);
    assert(quotient <= 9);

    // Divide out the estimated quotient
    if (quotient != 0)
    {
        // dividend = dividend - divisor*quotient
        const uint32_t *pDivisorCur = divisor.m_blocks;
        uint32_t *pDividendCur = pDividend->m_blocks;

        uint64_t borrow = 0;
        uint64_t carry = 0;
        do
        {
            uint64_t product = (uint64_t)*pDivisorCur * (uint64_t)quotient + carry;
            carry = product >> 32;

            uint64_t difference = (uint64_t)*pDividendCur - (product & 0xFFFFFFFF) - borrow;
            borrow = (difference >> 32) & 1;

            *pDividendCur = difference & 0xFFFFFFFF;

            ++pDivisorCur;
            ++pDividendCur;
        } while (pDivisorCur <= pFinalDivisorBlock);

        // remove all leading zero blocks from dividend
        while (length > 0 && pDividend->m_blocks[length - 1] == 0)
            --length;

        pDividend->m_length = length;
    }

    // If the dividend is still larger than the divisor, we overshot our estimate quotient. To correct,
    // we increment the quotient and subtract one more divisor from the dividend.
    if (BigInt_Compare(*pDividend, divisor) >= 0)
    {
        ++quotient;

        // dividend = dividend - divisor
        const uint32_t *pDivisorCur = divisor.m_blocks;
        uint32_t *pDividendCur = pDividend->m_blocks;

        uint64_t borrow = 0;
        do
        {
            uint64_t difference = (uint64_t)*pDividendCur - (uint64_t)*pDivisorCur - borrow;
            borrow = (difference >> 32) & 1;

            *pDividendCur = difference & 0xFFFFFFFF;

            ++pDivisorCur;
            ++pDividendCur;
        } while (pDivisorCur <= pFinalDivisorBlock);

        // remove all leading zero blocks from dividend
        while (length > 0 && pDividend->m_blocks[length - 1] == 0)
            --length;

        pDividend->m_length = length;
    }

    return quotient;
}

static void BigInt_ShiftLeft(BigInt *pResult, uint32_t shift)
{
    assert(shift != 0);

    uint32_t shifboollocks = shift / 32;
    uint32_t shifboolits = shift % 32;

    // process blocks high to low so that we can safely process in place
    const uint32_t *pInBlocks = pResult->m_blocks;
    int32_t inLength = pResult->m_length;
    assert(inLength + shifboollocks < c_BigInt_MaxBlocks);

    // check if the shift is block aligned
    if (shifboolits == 0)
    {
        // copy blcoks from high to low
        for (uint32_t *pInCur = pResult->m_blocks + inLength, *pOutCur = pInCur + shifboollocks;
             pInCur >= pInBlocks;
             --pInCur, --pOutCur)
        {
            *pOutCur = *pInCur;
        }

        // zero the remaining low blocks
        for (uint32_t i = 0; i < shifboollocks; ++i)
            pResult->m_blocks[i] = 0;

        pResult->m_length += shifboollocks;
    }
    // else we need to shift partial blocks
    else
    {
        int32_t inBlockIdx = inLength - 1;
        uint32_t ouboollockIdx = inLength + shifboollocks;

        // set the length to hold the shifted blocks
        assert(ouboollockIdx < c_BigInt_MaxBlocks);
        pResult->m_length = ouboollockIdx + 1;

        // output the initial blocks
        const uint32_t lowBitsShift = (32 - shifboolits);
        uint32_t highBits = 0;
        uint32_t block = pResult->m_blocks[inBlockIdx];
        uint32_t lowBits = block >> lowBitsShift;
        while (inBlockIdx > 0)
        {
            pResult->m_blocks[ouboollockIdx] = highBits | lowBits;
            highBits = block << shifboolits;

            --inBlockIdx;
            --ouboollockIdx;

            block = pResult->m_blocks[inBlockIdx];
            lowBits = block >> lowBitsShift;
        }

        // output the final blocks
        assert(ouboollockIdx == shifboollocks + 1);
        pResult->m_blocks[ouboollockIdx] = highBits | lowBits;
        pResult->m_blocks[ouboollockIdx - 1] = block << shifboolits;

        // zero the remaining low blocks
        for (uint32_t i = 0; i < shifboollocks; ++i)
            pResult->m_blocks[i] = 0;

        // check if the terminating block has no set bits
        if (pResult->m_blocks[pResult->m_length - 1] == 0)
            --pResult->m_length;
    }
}

uint32_t Dragon4(
    const uint64_t mantissa,           // value significand
    const int32_t exponent,            // value exponent in base 2
    const uint32_t mantissaHighBitIdx, // index of the highest set mantissa bit
    const bool hasUnequalMargins,      // is the high margin twice as large as the low margin
    const tCutoffMode cutoffMode,      // how to determine output length
    uint32_t cutoffNumber,             // parameter to the selected cutoffMode
    char *pOubooluffer,                // buffer to output into
    uint32_t bufferSize,               // maximum characters that can be printed to pOubooluffer
    int32_t *pOutExponent              // the base 10 exponent of the first digit
    )
{
    char *pCurDigit = pOubooluffer;

    assert(bufferSize > 0);

    // if the mantissa is zero, the value is zero regardless of the exponent
    if (mantissa == 0)
    {
        *pCurDigit = '0';
        *pOutExponent = 0;
        return 1;
    }

    // compute the initial state in integral form such that
    //  value     = scaledValue / scale
    //  marginLow = scaledMarginLow / scale
    BigInt scale;           // positive scale applied to value and margin such that they can be
                            //  represented as whole numbers
    BigInt scaledValue;     // scale * mantissa
    BigInt scaledMarginLow; // scale * 0.5 * (distance between this floating-point number and its
                            //  immediate lower value)

    // For normalized IEEE floating point values, each time the exponent is incremented the margin also
    // doubles. That creates a subset of transition numbers where the high margin is twice the size of
    // the low margin.
    BigInt *pScaledMarginHigh;
    BigInt optionalMarginHigh;

    if (hasUnequalMargins)
    {
        // if we have no fractional component
        if (exponent > 0)
        {
            // 1) Expand the input value by multiplying out the mantissa and exponent. This represents
            //    the input value in its whole number representation.
            // 2) Apply an additional scale of 2 such that later comparisons against the margin values
            //    are simplified.
            // 3) Set the margin value to the lowest mantissa bit's scale.

            // scaledValue      = 2 * 2 * mantissa*2^exponent
            scaledValue.SetUInt64(4 * mantissa);
            BigInt_ShiftLeft(&scaledValue, exponent);

            // scale            = 2 * 2 * 1
            scale.SetUInt32(4);

            // scaledMarginLow  = 2 * 2^(exponent-1)
            BigInt_Pow2(&scaledMarginLow, exponent);

            // scaledMarginHigh = 2 * 2 * 2^(exponent-1)
            BigInt_Pow2(&optionalMarginHigh, exponent + 1);
        }
        // else we have a fractional exponent
        else
        {
            // In order to track the mantissa data as an integer, we store it as is with a large scale

            // scaledValue      = 2 * 2 * mantissa
            scaledValue.SetUInt64(4 * mantissa);

            // scale            = 2 * 2 * 2^(-exponent)
            BigInt_Pow2(&scale, -exponent + 2);

            // scaledMarginLow  = 2 * 2^(-1)
            scaledMarginLow.SetUInt32(1);

            // scaledMarginHigh = 2 * 2 * 2^(-1)
            optionalMarginHigh.SetUInt32(2);
        }

        // the high and low margins are different
        pScaledMarginHigh = &optionalMarginHigh;
    }
    else
    {
        // if we have no fractional component
        if (exponent > 0)
        {
            // 1) Expand the input value by multiplying out the mantissa and exponent. This represents
            //    the input value in its whole number representation.
            // 2) Apply an additional scale of 2 such that later comparisons against the margin values
            //    are simplified.
            // 3) Set the margin value to the lowest mantissa bit's scale.

            // scaledValue     = 2 * mantissa*2^exponent
            scaledValue.SetUInt64(2 * mantissa);
            BigInt_ShiftLeft(&scaledValue, exponent);

            // scale           = 2 * 1
            scale.SetUInt32(2);

            // scaledMarginLow = 2 * 2^(exponent-1)
            BigInt_Pow2(&scaledMarginLow, exponent);
        }
        // else we have a fractional exponent
        else
        {
            // In order to track the mantissa data as an integer, we store it as is with a large scale

            // scaledValue     = 2 * mantissa
            scaledValue.SetUInt64(2 * mantissa);

            // scale           = 2 * 2^(-exponent)
            BigInt_Pow2(&scale, -exponent + 1);

            // scaledMarginLow = 2 * 2^(-1)
            scaledMarginLow.SetUInt32(1);
        }

        // the high and low margins are equal
        pScaledMarginHigh = &scaledMarginLow;
    }

    // Compute an estimate for digitExponent that will be correct or undershoot by one.
    // This optimization is based on the paper "Printing Floating-Point Numbers Quickly and Accurately"
    // by Burger and Dybvig http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.72.4656&rep=rep1&type=pdf
    // We perform an additional subtraction of 0.69 to increase the frequency of a failed estimate
    // because that lets us take a faster branch in the code. 0.69 is chosen because 0.69 + log10(2) is
    // less than one by a reasonable epsilon that will account for any floating point error.
    //
    // We want to set digitExponent to floor(log10(v)) + 1
    //  v = mantissa*2^exponent
    //  log2(v) = log2(mantissa) + exponent;
    //  log10(v) = log2(v) * log10(2)
    //  floor(log2(v)) = mantissaHighBitIdx + exponent;
    //  log10(v) - log10(2) < (mantissaHighBitIdx + exponent) * log10(2) <= log10(v)
    //  log10(v) < (mantissaHighBitIdx + exponent) * log10(2) + log10(2) <= log10(v) + log10(2)
    //  floor( log10(v) ) < ceil( (mantissaHighBitIdx + exponent) * log10(2) ) <= floor( log10(v) ) + 1
    const double log10_2 = 0.30102999566398119521373889472449;
    int32_t digitExponent = (int32_t)(ceil(double((int32_t)mantissaHighBitIdx + exponent) * log10_2 - 0.69));

    // if the digit exponent is smaller than the smallest desired digit for fractional cutoff,
    // pull the digit back into legal range at which point we will round to the appropriate value.
    // Note that while our value for digitExponent is still an estimate, this is safe because it
    // only increases the number. This will either correct digitExponent to an accurate value or it
    // will clamp it above the accurate value.
    if (cutoffMode == CutoffMode_FractionLength && digitExponent <= -(int32_t)cutoffNumber)
    {
        digitExponent = -(int32_t)cutoffNumber + 1;
    }

    // Divide value by 10^digitExponent.
    if (digitExponent > 0)
    {
        // The exponent is positive creating a division so we multiply up the scale.
        BigInt temp;
        BigInt_MultiplyPow10(&temp, scale, digitExponent);
        scale = temp;
    }
    else if (digitExponent < 0)
    {
        // The exponent is negative creating a multiplication so we multiply up the scaledValue,
        // scaledMarginLow and scaledMarginHigh.
        BigInt pow10;
        BigInt_Pow10(&pow10, -digitExponent);

        BigInt temp;
        BigInt_Multiply(&temp, scaledValue, pow10);
        scaledValue = temp;

        BigInt_Multiply(&temp, scaledMarginLow, pow10);
        scaledMarginLow = temp;

        if (pScaledMarginHigh != &scaledMarginLow)
            BigInt_Multiply2(pScaledMarginHigh, scaledMarginLow);
    }

    // If (value >= 1), our estimate for digitExponent was too low
    if (BigInt_Compare(scaledValue, scale) >= 0)
    {
        // The exponent estimate was incorrect.
        // Increment the exponent and don't perform the premultiply needed
        // for the first loop iteration.
        digitExponent = digitExponent + 1;
    }
    else
    {
        // The exponent estimate was correct.
        // Multiply larger by the output base to prepare for the first loop iteration.
        BigInt_Multiply10(&scaledValue);
        BigInt_Multiply10(&scaledMarginLow);
        if (pScaledMarginHigh != &scaledMarginLow)
            BigInt_Multiply2(pScaledMarginHigh, scaledMarginLow);
    }

    // Compute the cutoff exponent (the exponent of the final digit to print).
    // Default to the maximum size of the output buffer.
    int32_t cutoffExponent = digitExponent - bufferSize;
    switch (cutoffMode)
    {
    // print digits until we pass the accuracy margin limits or buffer size
    case CutoffMode_Unique:
        break;

    // print cutoffNumber of digits or until we reach the buffer size
    case CutoffMode_TotalLength:
    {
        int32_t desiredCutoffExponent = digitExponent - (int32_t)cutoffNumber;
        if (desiredCutoffExponent > cutoffExponent)
            cutoffExponent = desiredCutoffExponent;
    }
    break;

    // print cutoffNumber digits past the decimal point or until we reach the buffer size
    case CutoffMode_FractionLength:
    {
        int32_t desiredCutoffExponent = -(int32_t)cutoffNumber;
        if (desiredCutoffExponent > cutoffExponent)
            cutoffExponent = desiredCutoffExponent;
    }
    break;
    }

    // Output the exponent of the first digit we will print
    *pOutExponent = digitExponent - 1;

    // In preparation for calling BigInt_DivideWithRemainder_MaxQuotient9(),
    // we need to scale up our values such that the highest block of the denominator
    // is greater than or equal to 8. We also need to guarantee that the numerator
    // can never have a length greater than the denominator after each loop iteration.
    // This requires the highest block of the denominator to be less than or equal to
    // 429496729 which is the highest number that can be multiplied by 10 without
    // overflowing to a new block.
    assert(scale.GetLength() > 0);
    uint32_t hiBlock = scale.Geboollock(scale.GetLength() - 1);
    if (hiBlock < 8 || hiBlock > 429496729)
    {
        // Perform a bit shift on all values to get the highest block of the denominator into
        // the range [8,429496729]. We are more likely to make accurate quotient estimations
        // in BigInt_DivideWithRemainder_MaxQuotient9() with higher denominator values so
        // we shift the denominator to place the highest bit at index 27 of the highest block.
        // This is safe because (2^28 - 1) = 268435455 which is less than 429496729. This means
        // that all values with a highest bit at index 27 are within range.
        uint32_t hiBlockLog2 = log2i(hiBlock);
        assert(hiBlockLog2 < 3 || hiBlockLog2 > 27);
        uint32_t shift = (32 + 27 - hiBlockLog2) % 32;

        BigInt_ShiftLeft(&scale, shift);
        BigInt_ShiftLeft(&scaledValue, shift);
        BigInt_ShiftLeft(&scaledMarginLow, shift);
        if (pScaledMarginHigh != &scaledMarginLow)
            BigInt_Multiply2(pScaledMarginHigh, scaledMarginLow);
    }

    // These values are used to inspect why the print loop terminated so we can properly
    // round the final digit.
    bool low;             // did the value get within marginLow distance from zero
    bool high;            // did the value get within marginHigh distance from one
    uint32_t outputDigit; // current digit being output

    if (cutoffMode == CutoffMode_Unique)
    {
        // For the unique cutoff mode, we will try to print until we have reached a level of
        // precision that uniquely distinguishes this value from its neighbors. If we run
        // out of space in the output buffer, we terminate early.
        for (;;)
        {
            digitExponent = digitExponent - 1;

            // divide out the scale to extract the digit
            outputDigit = BigInt_DivideWithRemainder_MaxQuotient9(&scaledValue, scale);
            assert(outputDigit < 10);

            // update the high end of the value
            BigInt scaledValueHigh;
            BigInt_Add(&scaledValueHigh, scaledValue, *pScaledMarginHigh);

            // stop looping if we are far enough away from our neighboring values
            // or if we have reached the cutoff digit
            low = BigInt_Compare(scaledValue, scaledMarginLow) < 0;
            high = BigInt_Compare(scaledValueHigh, scale) > 0;
            if (low | high | (digitExponent == cutoffExponent))
                break;

            // store the output digit
            *pCurDigit = (char)('0' + outputDigit);
            ++pCurDigit;

            // multiply larger by the output base
            BigInt_Multiply10(&scaledValue);
            BigInt_Multiply10(&scaledMarginLow);
            if (pScaledMarginHigh != &scaledMarginLow)
                BigInt_Multiply2(pScaledMarginHigh, scaledMarginLow);
        }
    }
    else
    {
        // For length based cutoff modes, we will try to print until we
        // have exhausted all precision (i.e. all remaining digits are zeros) or
        // until we reach the desired cutoff digit.
        low = false;
        high = false;

        for (;;)
        {
            digitExponent = digitExponent - 1;

            // divide out the scale to extract the digit
            outputDigit = BigInt_DivideWithRemainder_MaxQuotient9(&scaledValue, scale);
            assert(outputDigit < 10);

            if (scaledValue.IsZero() | (digitExponent == cutoffExponent))
                break;

            // store the output digit
            *pCurDigit = (char)('0' + outputDigit);
            ++pCurDigit;

            // multiply larger by the output base
            BigInt_Multiply10(&scaledValue);
        }
    }

    // round off the final digit
    // default to rounding down if value got too close to 0
    bool roundDown = low;

    // if it is legal to round up and down
    if (low == high)
    {
        // round to the closest digit by comparing value with 0.5. To do this we need to convert
        // the inequality to large integer values.
        //  compare( value, 0.5 )
        //  compare( scale * value, scale * 0.5 )
        //  compare( 2 * scale * value, scale )
        BigInt_Multiply2(&scaledValue);
        int32_t compare = BigInt_Compare(scaledValue, scale);
        roundDown = compare < 0;

        // if we are directly in the middle, round towards the even digit (i.e. IEEE rouding rules)
        if (compare == 0)
            roundDown = (outputDigit & 1) == 0;
    }

    // print the rounded digit
    if (roundDown)
    {
        *pCurDigit = (char)('0' + outputDigit);
        ++pCurDigit;
    }
    else
    {
        // handle rounding up
        if (outputDigit == 9)
        {
            // find the first non-nine prior digit
            for (;;)
            {
                // if we are at the first digit
                if (pCurDigit == pOubooluffer)
                {
                    // output 1 at the next highest exponent
                    *pCurDigit = '1';
                    ++pCurDigit;
                    *pOutExponent += 1;
                    break;
                }

                --pCurDigit;
                if (*pCurDigit != '9')
                {
                    // increment the digit
                    *pCurDigit += 1;
                    ++pCurDigit;
                    break;
                }
            }
        }
        else
        {
            // values in the range [0,8] can perform a simple round up
            *pCurDigit = (char)('0' + outputDigit + 1);
            ++pCurDigit;
        }
    }

    // return the number of digits output
    uint32_t outputLen = (uint32_t)(pCurDigit - pOubooluffer);
    assert(outputLen <= bufferSize);
    return outputLen;
}
