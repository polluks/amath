/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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

#ifndef _NUMERAL_H
#define _NUMERAL_H

/**
 * @file  ntext.h
 * @brief Text to numbers handling.
 *
 * Converts both between text and numbers AND between numbers and text.
 *
 */

#include "lib/numb.h"
#include "lib/charbuf.h"

/**
* @brief Base class for all numeral systems.
*
* More info on numeral systems is available at Wikipedia:
* http://en.wikipedia.org/wiki/Numeral_system
*
*/
class NumeralSystem {
public:
    NumeralSystem();
    virtual ~NumeralSystem();
    virtual const char* GetName() = 0;
    virtual const char* GetPrefix() = 0;
    virtual unsigned int GetDigits() = 0;
    virtual void SetDigits(unsigned int digits) = 0;
    virtual const char GetFractionPoint() = 0;
    virtual void SetFractionPoint(const char fractionpoint) = 0;
    virtual const char* GetText(Number *number) = 0;
    virtual Number* Parse(const char *text, unsigned int *length, char **end) = 0;
    virtual Number* Parse(const char *text);

protected:
    CharBuffer *buf;
};

/**
* @brief Base class for all numeral systems with a
*        positional notation.
*
* More info on positional notation is available at Wikipedia:
* http://en.wikipedia.org/wiki/Positional_notation
*
*/
class PositionalNumeralSystem : public NumeralSystem {
public:
    PositionalNumeralSystem(unsigned int base, unsigned int digits, const char fractionpoint);
    ~PositionalNumeralSystem();

    virtual const char* GetName();
    virtual const char* GetPrefix();
    virtual unsigned int GetDigits();
    virtual void SetDigits(unsigned int digits);
    virtual const char GetFractionPoint();
    virtual void SetFractionPoint(const char fractionpoint);
    virtual const char* GetText(Number *number);
    virtual Number* Parse(const char *text, unsigned int *length, char** end);

protected:
    double base;
    unsigned int digits;
    char fractionpoint;

private:
    const char* GetText(double number);
    void IntegerToBuffer(double value, unsigned int digits, int *outdigits) ;
};

class DecimalSystem : public PositionalNumeralSystem {
public:
    DecimalSystem();
    DecimalSystem(unsigned int digits);
    DecimalSystem(unsigned int digits, const char fractionpoint);
    ~DecimalSystem();

    virtual const char* GetText(Number *number);

private:
    const char *GetRealText(double value);
};

#endif
