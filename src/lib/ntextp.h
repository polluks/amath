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

#ifndef AMATH_NUMERAL_POSITIONAL_H
#define AMATH_NUMERAL_POSITIONAL_H

#include "ntext.h"

/**
* @brief Base class for all numeral systems with a positional notation
* @details
* More info on positional notation is available at Wikipedia:
* https://wikipedia.org/wiki/Positional_notation
*/
class PositionalNumeralSystem : public NumeralSystem
{
public:
    PositionalNumeralSystem(unsigned int base, unsigned int digits, const char fractionPoint);
    ~PositionalNumeralSystem();

    virtual const char* GetName();
    virtual const char* GetPrefix();
    virtual unsigned int GetDigits();
    virtual void SetDigits(unsigned int digits);
    virtual const char GetFractionPoint();
    virtual void SetFractionPoint(const char fractionPoint);
    virtual const char* GetText(Number* number);
    virtual Number* Parse(const char* text, unsigned int* length, char** end);

protected:
    const char* GetSpecialCase(Number *number);
    void IntegerToBuffer(double value, unsigned int digits, int* outdigits) const;

    double base;
    unsigned int digits;
    char fractionPoint;

private:
    const char* GetText(double number) const;
};

#endif
