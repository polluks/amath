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

#include "clib.h"
#include "math.h"
#include "dprint.h"
#include "complex.h"
#include "lib/real.h"
#include "lib/cplex.h"
#include "lib/ntext.h"
#include "lib/charbuf.h"

/******************************************************************************/

NumeralSystem::NumeralSystem()
{
    buf = new CharBuffer();
    buf->Empty();
}

NumeralSystem::~NumeralSystem()
{
    delete buf;
}

Number* NumeralSystem::Parse(const char *text)
{
    unsigned int length;
    char *end;
    return Parse(text, &length, &end);
}

/******************************************************************************/

PositionalNumeralSystem::PositionalNumeralSystem(
    unsigned int base,
    unsigned int digits,
    const char fractionpoint) :
    base(base * 1.0), digits(digits) {
    this->fractionpoint = fractionpoint;
}

PositionalNumeralSystem::~PositionalNumeralSystem()
{ }

const char* PositionalNumeralSystem::GetName()
{
    switch ((int)base) {
    case 2:
        return "binary";
        break;
    case 8:
        return "octal";
        break;
    case 10:
        return "decimal";
        break;
    case 16:
        return "hexadecimal";
        break;
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

const char* PositionalNumeralSystem::GetPrefix()
{
    // TODO: Implement
    return "";
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
    return (const char)this->fractionpoint;
}

void PositionalNumeralSystem::SetFractionPoint(const char fractionpoint)
{
    this->fractionpoint = fractionpoint;
}

const char* PositionalNumeralSystem::GetText(Number *number)
{
    if (number->system == nsysreal) {
        return GetText(number->GetRealValue());
    }

    complex w = ((ComplexNumber*)number)->GetComplexValue();
    double a = creal(w);
    double b = cimag(w);

    if (a == 0.0 && b == 0.0) {
        buf->Empty();
        buf->Append('0');
        return buf->GetString();
    }

    CharBuffer *val = new CharBuffer(512);
    val->Empty();

    if (a != 0.0) {
        const char *real = GetText(a);
        val->Append(real);
    }

    const char *imag = GetText(b);
    if (a != 0.0 && b > 0.0) {
        val->Append('+');
    }

    if (b != 0.0) {
        val->Append(imag);
        val->Append('i');
    }

    buf->Copy(val);
    delete val;

    return buf->GetString();
}

const char* PositionalNumeralSystem::GetText(double number)
{
    if (!finite(number)) {
        return "Inf";
    } else if (isnan(number)) {
        return "NaN";
    } else if (number == 0.0) {
        return "0";
    }

    buf->Empty();

    double dnumber = number;
    if (dnumber < 0.0) {
        buf->Append('-');
        dnumber = -dnumber;
    }

    double expborder = log2p(base, dnumber);
    int exponent = 0;

    // Find exponent
    if (expborder > 6.0 || expborder < -5.0) {
        double dexp = trunc(log2p(base, dnumber));

        // Adjust to keep one digits before dot.
        if (dexp < 0.0) {
            dexp -= 1.0;
        }

        dnumber = dnumber * pow(base, -dexp);
        exponent = (int)dexp;
    }

    int digitout;
    int intdigits;

    // NOTICE: 1.5.3 Scaled trunc
    int intvalue = (int)(trunc(dnumber * base) / base);
    IntegerToBuffer(intvalue, digits, &intdigits);

    int fragdigits = digits - intdigits;
    if (fragdigits > 0) {
        buf->Append('.');

        // TODO: Fix fraction error (try 1.5439)
        double fraction = fabs(round((dnumber - round(dnumber)) * pow(base, fragdigits)));

        // NOTICE: 1.5.3 Changed from trunc to round
        double actualdigits = round(log2p(base, fraction));
        int padding = fragdigits - (finite(actualdigits) == 1 ? (int)actualdigits : 0) - 1;

        // Pad zeros if needed
        while (padding-- > 0) {
            buf->Append('0');
        }

        // NOTICE: 1.5.3 Scaled trunc
        intvalue = (int)(trunc(fraction * base) / base);
        IntegerToBuffer(intvalue, digits - intdigits, &digitout);

        // Remove trailing zeros
        while (buf->RemoveTrailing('0'))
            ;

        buf->RemoveTrailing(fractionpoint);
    }

    // Add exponent
    if (exponent != 0) {
        buf->Append('e');
        buf->Append(exponent > 0 ? '+' : '-');
        IntegerToBuffer(abs(exponent), 3, &digitout);
    }

    // Make sure no rounding error is returned
    if (buf->Is("-0")) {
        buf->Empty();
        buf->Append('0');
    }

    return buf->GetString();
}

void PositionalNumeralSystem::IntegerToBuffer(double value, unsigned int digits, int *outdigits)
{
    static const char *alphaNumerics = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int count = 0;
    char *chars = new char[128]; // TODO: Find correct size
    char *start = chars;

    do {
        count++;
        unsigned int intremainder = (unsigned int) trunc(fmod(value, base));
        *chars++ = alphaNumerics[intremainder];
        value /= base;
    } while (value >= 1.0);

    unsigned int n = count;
    unsigned int q = digits;
    chars--;

    while (n-- != 0 && q-- != 0) {
        buf->Append(*chars--);
    }

    n++;
    while (n-- != 0) {
        buf->Append('0');
    }

    *outdigits = count;
    delete [] start;
}

Number* PositionalNumeralSystem::Parse(const char *text, unsigned int *length, char **end)
{
    unsigned int intbase = (unsigned int)base;
    char maxNumeric = (intbase > 10 ? 10 : intbase) + '0' - 1;
    char maxAlpha = intbase > 10 ? intbase + 'A' - 11 : 0;

    unsigned int pos = 0;
    double integer = 0;
    double addition;

    while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != 0 && *text >= 'A' && *text <= maxAlpha))) {
        addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10)) * 1.0;
        integer = integer * base + addition;
        text++;
        pos++;
    }

    // Digits not found
    if (pos == 0) {
        *length = 0;
        *end = (char*)text;
        return new RealNumber();
    }

    double fraction = 0.0;
    double divisor = 1.0;
    if (*text == fractionpoint) {
        text++;
        pos++;

        while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != '\0' && *text >= 'A' && *text <= maxAlpha))) {
            addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10));
            fraction = fraction * base + addition;
            divisor *= base;
            text++;
            pos++;
        }
    }

    double exp = 0;
    if (*text == 'e' || *text == 'E') {
        text++;
        pos++;

        double sign = *text == '+' ? 1.0 : *text == '-' ? -1.0 : 0.0;

        if (sign != 0.0) {
            text++;
            pos++;

            while (*text != '\0' && ((*text >= '0' && *text <= maxNumeric) || (maxAlpha != 0 && *text >= 'A' && *text <= maxAlpha))) {
                addition = ((*text >= '0' && *text <= maxNumeric) ? (*text - '0') : (*text - 'A' + 10)) * 1.0;
                exp = exp * base + addition;
                text++;
                pos++;
            }

            exp *= sign;
        } else {
            text--;
            pos--;
        }
    }

    *length = pos;
    *end = (char*)text;
    double dnumber = (integer + (fraction / divisor)) * pow(base, exp);

    return new RealNumber(dnumber);
}

/******************************************************************************/

DecimalSystem::DecimalSystem() :
    PositionalNumeralSystem(10, 5, '\0')
{ }

DecimalSystem::DecimalSystem(unsigned int digits) :
    PositionalNumeralSystem(10, digits, '.')
{ }

DecimalSystem::DecimalSystem(
    unsigned int digits,
    const char fractionpoint) :
    PositionalNumeralSystem(10, digits, fractionpoint)
{ }

DecimalSystem::~DecimalSystem()
{ }

const char* DecimalSystem::GetText(Number* number)
{
    buf->Empty();

    if (number->system == nsysreal) {
        return GetRealText(number->GetRealValue());
    }

    complex w = ((ComplexNumber*)number)->GetComplexValue();
    double a = creal(w);
    double b = cimag(w);

    if (a == 0.0 && b == 0.0) {
        buf->Append('0');
        return buf->GetString();
    }

    if (a != 0.0) {
        GetRealText(a);
    }

    if (a != 0.0 && b > 0.0) {
        buf->Append('+');
    }

    if (b != 0.0) {
        GetRealText(b);
        buf->Append('i');
    }

    return buf->GetString();
}

const char* DecimalSystem::GetRealText(double value)
{
    double exponent = log10(fabs(value));
    int formatdigits = digits - (int)trunc(exponent) - 1;

    double rounddigits = digits - 1;
    if (exponent < 0.0) {
        rounddigits++;
        formatdigits++;
    }

    // Remove output of inaccuracy
    if (formatdigits > (int)digits) {
        formatdigits = digits;
    }

    double roundfactor = pow(10.0, rounddigits);
    double roundedvalue = round(value * roundfactor) / roundfactor;

    if (roundedvalue == 0.0) {
        return "0";
    }

    double ulimit = pow(10.0, (double)digits);
    double llimit = pow(10.0, -(double)digits);

    if (fabs(roundedvalue) > ulimit) {
        return "INF";
    } else if (fabs(roundedvalue) < llimit) {
        return "-INF";
    }

    double expborder = log10(fabs(roundedvalue));
    tPrintFloatFormat format = (expborder > 6.0 || expborder < -5.0) ?
                               PrintFloatFormat_Scientific :
                               PrintFloatFormat_Positional;

    static const int size = 32;
    char *out = new char[size];
    PrintFloat64(out, size, roundedvalue, format, formatdigits, fractionpoint);
    buf->EnsureGrowth(size);
    buf->Append(out);
    while (buf->RemoveTrailing('0'))
        ;
    buf->RemoveTrailing(fractionpoint);
    delete[] out;

    return buf->GetString();
}

