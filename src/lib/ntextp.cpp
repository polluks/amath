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
 * https://amath.innolan.net
 * 
 */

#include "amath.h"
#include "amathc.h"
#include "mathr.h"
#include "mathi.h"
#include "real.h"
#include "cplex.h"
#include "ntext.h"
#include "ntextd.h"
#include "charbuf.h"

PositionalNumeralSystem::PositionalNumeralSystem(
    unsigned int base,
    unsigned int digits,
    const char fractionPoint) : base(base * 1.0), digits(digits)
{
    this->fractionPoint = fractionPoint;
}

PositionalNumeralSystem::~PositionalNumeralSystem()
{
}

const char *PositionalNumeralSystem::GetName()
{
    switch (static_cast<int>(base))
    {
    case 2:
        return "binary";
    case 8:
        return "octal";
    case 10:
        return "decimal";
    case 16:
        return "hexadecimal";
    }

    const char *text = "base ";
    Number *n = new RealNumber(base);
    NumeralSystem *ns = new DecimalSystem(2);
    const char *numtext = ns->GetText(n);

    buf->EnsureSize(StrLen(text) + StrLen(numtext) + 1);
    buf->Empty();
    buf->Append(text);
    buf->Append(numtext);

    delete ns;
    delete n;
    return buf->GetString();
}

const char *PositionalNumeralSystem::GetPrefix()
{
    // TODO: Consider using prefix with numral systems != base 10
    return EMPTYSTRING;
}

unsigned int PositionalNumeralSystem::GetDigits()
{
    return digits;
}

void PositionalNumeralSystem::SetDigits(unsigned int digits)
{
    this->digits = digits;
}

const char PositionalNumeralSystem::GetFractionPoint()
{
    return static_cast<const char>(this->fractionPoint);
}

void PositionalNumeralSystem::SetFractionPoint(const char fractionPoint)
{
    this->fractionPoint = fractionPoint;
}

const char *PositionalNumeralSystem::GetSpecialCase(Number *number)
{
    if (number->IsNaN())
    {
        buf->Empty();
        buf->Append("NaN");
        return buf->GetString();
    }

    if (number->IsNotImplemented())
    {
        buf->Empty();
        buf->Append("NotImplemented");
        return buf->GetString();
    }

    if (number->IsInfinite() && number->IsNegative())
    {
        buf->Empty();
        buf->Append("-Inf");
        return buf->GetString();
    }

    if (number->IsInfinite() && !number->IsNegative())
    {
        buf->Empty();
        buf->Append("Inf");
        return buf->GetString();
    }

    if (number->IsZero())
    {
        buf->Empty();
        buf->Append("0");
        return buf->GetString();
    }

    return nullptr;
}

const char *PositionalNumeralSystem::GetText(Number *number)
{
    const char *sc = GetSpecialCase(number);
    if (sc != nullptr)
    {
        return sc;
    }

    if (number->system == nsysreal)
    {
        return GetText(number->GetRealValue());
    }

    complex w = static_cast<ComplexNumber *>(number)->GetComplexValue();
    double a = creal(w);
    double b = cimag(w);

    if (a == 0.0 && b == 0.0)
    {
        buf->Empty();
        buf->Append('0');
        return buf->GetString();
    }

    CharBuffer *val = new CharBuffer(512);
    val->Empty();

    if (a != 0.0)
    {
        const char *real = GetText(a);
        val->Append(real);
    }

    const char *imag = GetText(b);
    if (a != 0.0 && b > 0.0)
    {
        val->Append('+');
    }

    if (b != 0.0)
    {
        val->Append(imag);
        val->Append('i');
    }

    buf->Copy(val);
    delete val;

    return buf->GetString();
}

const char *PositionalNumeralSystem::GetText(double number) const
{
    if (number == 0.0)
    {
        return "0";
    }

    buf->Empty();

    double dnumber = number;
    if (dnumber < 0.0)
    {
        buf->Append('-');
        dnumber = -dnumber;
    }

    double expbor = log2p(base, dnumber);
    double expacc = expbor > 0.0 ? 4e-14 : -1e-15;
    double expborder = trunc(expbor + expacc);

    int exponent = 0;
    double rounding;

    double bordermax = trunc(9.0 * 10 / base);
    double bordermin = trunc(-8.0 * 10 / base);

    // Find exponent
    if (expborder >= bordermax || expborder <= bordermin)
    {
        double dexp = trunc(log2p(base, dnumber) + expacc);
        dnumber = dnumber * pow(base, -dexp);

        // pow is inaccurate on small and large numbers
        if (dexp > 15 || dexp < -15)
        {
            dnumber += 2e-15;
        }

        // Adjust if below zero
        if (dnumber < 1.0)
        {
            dexp--;
            dnumber *= base;
        }

        exponent = static_cast<int>(dexp);
        rounding = 0;
    }
    else
    {
        double acc = exponent > 0 ? 15 : -15;
        rounding = pow(base, exponent + acc);
    }

    int digitout;
    int intdigits;

    double intvalue = trunc(dnumber + rounding);
    IntegerToBuffer(intvalue, digits, &intdigits);

    int fragdigits = digits - intdigits + (intvalue < 1.0 ? 1 : 0);
    if (fragdigits > 0)
    {
        buf->Append(fractionPoint);

        double fraction = fabs(round((dnumber - intvalue) * pow(base, fragdigits)));
        double temp1 = log2p(base, fraction);
        FloatUnion64 temp2;
        temp2.floatingPoint = temp1;
        bool fin = !temp2.IsInf();
        int actualdigits = static_cast<int>(trunc(temp1 + 3e-15));
        int padding = fragdigits - (fin == 1 ? actualdigits : 0) - 1;

        // Pad zeros if needed
        while (padding-- > 0)
        {
            buf->Append('0');
        }

        intvalue = static_cast<int64_t>(trunc(fraction * base) / base);
        IntegerToBuffer(intvalue, fragdigits, &digitout);

        // Remove trailing zeros
        // ReSharper disable once CppPossiblyErroneousEmptyStatements
        while (buf->RemoveTrailing('0'))
            ;

        buf->RemoveTrailing(fractionPoint);
    }

    // Add exponent
    if (exponent != 0)
    {
        buf->Append('e');
        buf->Append(exponent > 0 ? '+' : '-');
        IntegerToBuffer(abs(exponent), 3, &digitout);
    }

    // Make sure no rounding error is returned
    if (buf->Is("-0"))
    {
        buf->Empty();
        buf->Append('0');
    }

    return buf->GetString();
}

void PositionalNumeralSystem::IntegerToBuffer(double value, unsigned int digits, int *outdigits) const
{
    static const char *alphaNumerics = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int count = 0;
    char *chars = new char[128];
    char *start = chars;

    do
    {
        count++;
        unsigned int intremainder = static_cast<unsigned int>(trunc(fmod(value, base)));
        *chars++ = alphaNumerics[intremainder];
        value /= base;
    } while (value >= 1.0);

    unsigned int n = count;
    unsigned int q = digits;
    chars--;

    while (n-- != 0 && q-- != 0)
    {
        buf->Append(*chars--);
    }

    n++;
    while (n-- != 0)
    {
        buf->Append('0');
    }

    *outdigits = count;
    delete[] start;
}

Number *PositionalNumeralSystem::Parse(const char *text, unsigned int *length, char **end)
{
    unsigned int intbase = static_cast<unsigned int>(base);
    char maxNumeric = (intbase > 10 ? 10 : intbase) + '0' - 1;
    char maxAlpha = intbase > 10 ? intbase + 'A' - 11 : 0;

    unsigned int pos = 0;
    double integer = 0;
    double addition;

    while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != 0 && *text >= 'A' && *text <= maxAlpha)))
    {
        addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10)) * 1.0;
        integer = integer * base + addition;
        text++;
        pos++;
    }

    // Digits not found
    if (pos == 0)
    {
        *length = 0;
        *end = const_cast<char*>(text);
        return new RealNumber();
    }

    double fraction = 0.0;
    double divisor = 1.0;
    if (*text == fractionPoint && fractionPoint != '\0')
    {
        text++;
        pos++;

        while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != '\0' && *text >= 'A' && *text <= maxAlpha)))
        {
            addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10));
            fraction = fraction * base + addition;
            divisor *= base;
            text++;
            pos++;
        }
    }

    double exp = 0.0;
    if (*text == 'e' || *text == 'E')
    {
        text++;
        pos++;

        double sign = *text == '+' ? 1.0 : *text == '-' ? -1.0 : 0.0;

        if (sign != 0.0)
        {
            text++;
            pos++;

            while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != 0 && *text >= 'A' && *text <= maxAlpha)))
            {
                addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10)) * 1.0;
                exp = exp * base + addition;
                text++;
                pos++;
            }

            exp *= sign;
        }
        else
        {
            text--;
            pos--;
        }
    }

    *length = pos;
    *end = const_cast<char*>(text);

    double dnumber = (integer + (fraction / divisor));

    if (exp != 0.0)
    {
        // pow seems a bit off
        dnumber *= pow(base, exp + 4e-15);
    }

    return new RealNumber(dnumber);
}
