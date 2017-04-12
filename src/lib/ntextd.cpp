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

#include "ntextd.h"
#include "bigint.h"
#include "amathc.h"
#include "amath.h"
#include "mathr.h"
#include "mathi.h"
#include "cplex.h"

DecimalSystem::DecimalSystem() : PositionalNumeralSystem(10, 5, '\0')
{
}

DecimalSystem::DecimalSystem(unsigned int digits) :
    PositionalNumeralSystem(10, digits, '\0')
{
}

DecimalSystem::DecimalSystem(unsigned int digits, const char fractionPoint) :
    PositionalNumeralSystem(10, digits, fractionPoint)
{
}

DecimalSystem::~DecimalSystem()
{
}

const char *DecimalSystem::GetText(Number *number)
{
    const char *sc = GetSpecialCase(number);
    if (sc != nullptr)
    {
        return sc;
    }

    if (number->system == nsysreal)
    {
        buf->Empty();
        return GetText(number->GetRealValue());
    }

    complex w = ((ComplexNumber *)number)->GetComplexValue();
    double a = creal(w);
    double b = cimag(w);

    buf->Empty();
    if (a != 0.0)
    {
        GetText(a);
    }

    if (a != 0.0 && b > 0.0)
    {
        buf->Append('+');
    }

    if (b != 0.0)
    {
        GetText(b);
        buf->Append('i');
    }

    return buf->GetString();
}

const char *DecimalSystem::GetText(double number) const
{
    int32_t printExponent = 0;
    double dexponent = log10(fabs(number));
    int32_t precision = digits - (int32_t)trunc(dexponent) - 1;
    int32_t lim = 15;
    bool sci = (dexponent > 9.0 || dexponent < -8.0);    
    if (sci)
    {
        precision = digits;
    }
    else if (dexponent < 0.0)
    {
        precision++;
        lim--;
    }

    if (precision > lim)
    {
        precision = lim;
    }
    
    static const int size = 64;
    char *out = new char[size];
    char *pOutBuffer = out;
    uint32_t bufferSize = size;

    FloatUnion64 floatUnion;
    floatUnion.floatingPoint = number;
    uint32_t floatExponent = floatUnion.GetExponent();
    uint64_t floatMantissa = floatUnion.GetMantissa();

    if (floatUnion.IsNegative())
    {
        pOutBuffer[0] = '-';
        ++pOutBuffer;
        --bufferSize;
    }

    uint64_t mantissa;
    int32_t exponent;
    uint32_t mantissaHighBitIdx;
    bool hasUnequalMargins;

    if (floatExponent != 0)
    {
        // normal
        mantissa = (1ull << 52) | floatMantissa;
        exponent = floatExponent - 1023 - 52;
        mantissaHighBitIdx = 52;
        hasUnequalMargins = (floatExponent != 1) && (floatMantissa == 0);
    }
    else
    {
        // subnormal
        mantissa = floatMantissa;
        exponent = 1 - 1023 - 52;
        mantissaHighBitIdx = log2i(mantissa);
        hasUnequalMargins = false;
    }

    if (!sci)
    {
        int32_t printExponent;
        uint32_t numPrintDigits;
        uint32_t maxPrintLen = bufferSize - 1;
        numPrintDigits = Dragon4(mantissa,
                                 exponent,
                                 mantissaHighBitIdx,
                                 hasUnequalMargins,
                                 CutoffMode_FractionLength,
                                 precision,
                                 pOutBuffer,
                                 maxPrintLen,
                                 &printExponent);

        // track the number of digits past the decimal point that have been printed
        uint32_t numFractionDigits = 0;

        // if output has a whole number
        if (printExponent >= 0)
        {
            // leave the whole number at the start of the buffer
            uint32_t numWholeDigits = printExponent + 1;
            if (numPrintDigits < numWholeDigits)
            {
                // don't overflow the buffer
                if (numWholeDigits > maxPrintLen)
                    numWholeDigits = maxPrintLen;

                // add trailing zeros up to the decimal point
                for (; numPrintDigits < numWholeDigits; ++numPrintDigits)
                    pOutBuffer[numPrintDigits] = '0';
            }
            // insert the decimal point prior to the fraction
            else if (numPrintDigits > (uint32_t)numWholeDigits)
            {
                numFractionDigits = numPrintDigits - numWholeDigits;
                uint32_t maxFractionDigits = maxPrintLen - numWholeDigits - 1;
                if (numFractionDigits > maxFractionDigits)
                    numFractionDigits = maxFractionDigits;

                MemCopy(pOutBuffer + numWholeDigits + 1, pOutBuffer + numWholeDigits, numFractionDigits);
                pOutBuffer[numWholeDigits] = fractionPoint;
                numPrintDigits = numWholeDigits + 1 + numFractionDigits;
            }
        }
        else
        {
            // shift out the fraction to make room for the leading zeros
            if (maxPrintLen > 2)
            {
                uint32_t numFractionZeros = (uint32_t)-printExponent - 1;
                uint32_t maxFractionZeros = maxPrintLen - 2;
                if (numFractionZeros > maxFractionZeros)
                    numFractionZeros = maxFractionZeros;

                uint32_t digitsStartIdx = 2 + numFractionZeros;

                // shift the significant digits right such that there is room for leading zeros
                numFractionDigits = numPrintDigits;
                uint32_t maxFractionDigits = maxPrintLen - digitsStartIdx;
                if (numFractionDigits > maxFractionDigits)
                    numFractionDigits = maxFractionDigits;

                MemCopy(pOutBuffer + digitsStartIdx, pOutBuffer, numFractionDigits);

                // insert the leading zeros
                for (uint32_t i = 2; i < digitsStartIdx; ++i)
                    pOutBuffer[i] = '0';

                // update the counts
                numFractionDigits += numFractionZeros;
                numPrintDigits = numFractionDigits;
            }

            // add the decimal point
            if (maxPrintLen > 1)
            {
                pOutBuffer[1] = fractionPoint;
                numPrintDigits += 1;
            }

            // add the initial zero
            if (maxPrintLen > 0)
            {
                pOutBuffer[0] = '0';
                numPrintDigits += 1;
            }
        }

        // add trailing zeros up to precision length
        if (precision > (int32_t)numFractionDigits && numPrintDigits < maxPrintLen)
        {
            // add a decimal point if this is the first fractional digit we are printing
            if (numFractionDigits == 0)
            {
                pOutBuffer[numPrintDigits++] = fractionPoint;
            }

            // compute the number of trailing zeros needed
            uint32_t totalDigits = numPrintDigits + (precision - numFractionDigits);
            if (totalDigits > maxPrintLen)
                totalDigits = maxPrintLen;

            for (; numPrintDigits < totalDigits; ++numPrintDigits)
                pOutBuffer[numPrintDigits] = '0';
        }

        pOutBuffer[numPrintDigits] = '\0';
    }
    else
    {
        uint32_t numPrintDigits;
        numPrintDigits = Dragon4(mantissa,
                                 exponent,
                                 mantissaHighBitIdx,
                                 hasUnequalMargins,
                                 CutoffMode_TotalLength,
                                 precision + 1,
                                 pOutBuffer,
                                 bufferSize,
                                 &printExponent);

        char *pCurOut = pOutBuffer;
        pCurOut += 1;

        // insert the decimal point prior to the fractional number
        uint32_t numFractionDigits = numPrintDigits - 1;
        if (numFractionDigits > 0 && bufferSize > 1)
        {
            uint32_t maxFractionDigits = bufferSize - 2;
            if (numFractionDigits > maxFractionDigits)
                numFractionDigits = maxFractionDigits;

            MemCopy(pCurOut + 1, pCurOut, numFractionDigits);
            pCurOut[0] = fractionPoint;
            pCurOut += (1 + numFractionDigits);
        }

        pCurOut[0] = '\0';
    }

    buf->EnsureGrowth(size);
    buf->Append(out);

    if (fractionPoint != '\0' && buf->Contains(fractionPoint))
    {
        while (buf->RemoveTrailing('0'))
            ;
        buf->RemoveTrailing(fractionPoint);
    }

    if (printExponent != 0)
    {
        buf->Append('e');
        if (printExponent >= 0)
        {
            buf->Append('+');
        }
        else
        {
            buf->Append('-');
            printExponent = -printExponent;
        }
        int temp;
        IntegerToBuffer(printExponent, 3, &temp);
    }

    if (fractionPoint != '\0' && buf->Contains(fractionPoint) && !buf->Contains('e'))
    {
        while (buf->RemoveTrailing('0'))
            ;
        buf->RemoveTrailing(fractionPoint);
    }

    delete[] out;
    return buf->GetString();
}
