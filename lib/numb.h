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

#ifndef _NUMBER_H
#define _NUMBER_H

#ifndef AMIGA
#pragma GCC diagnostic ignored "-Wshadow"
#endif

/**
 * @file  numb.h
 * @brief Classbase handling of numbers.
 *
 */

typedef enum {
    nsysnatural,
    nsysintegers,
    nsysrational,
    nsysreal,
    nsyscomplex
} NumberSystem;

struct Number {
public:
    Number(NumberSystem system) : system(system)  { }
    virtual ~Number() { }
    virtual Number* Clone() = 0;
    virtual int GetIntegerValue() = 0;
    virtual double GetRealValue() = 0;
    virtual bool PureComplexValue() = 0;
    virtual int GetPrecedence() = 0;
    virtual int GetDefaultPrecedence() = 0;

    virtual Number* Unary() = 0;
    virtual Number* Add(Number *other) = 0;
    virtual Number* Sub(Number *other) = 0;
    virtual Number* Mul(Number *other) = 0;
    virtual Number* Div(Number *other) = 0;
    virtual Number* Raise(Number *exponent) = 0;

    virtual Number* Signum() = 0;
    virtual Number* Trunc() = 0;
    virtual Number* Round() = 0;
    virtual Number* Floor() = 0;
    virtual Number* Ceiling() = 0;
    virtual Number* Absolute() = 0;
    virtual Number* SquareRoot() = 0;
    virtual Number* CubeRoot() = 0;
    virtual Number* Reciprocal() = 0;

    virtual Number* Log() = 0;
    virtual Number* Log2() = 0;
    virtual Number* Log10() = 0;

    virtual Number* Sine() = 0;
    virtual Number* Cosine() = 0;
    virtual Number* Tangent() = 0;
    virtual Number* Cosecant() = 0;
    virtual Number* Secant() = 0;
    virtual Number* Cotangent() = 0;

    virtual Number* ArcSine() = 0;
    virtual Number* ArcCosine() = 0;
    virtual Number* ArcTangent() = 0;
    virtual Number* ArcCosecant() = 0;
    virtual Number* ArcSecant() = 0;
    virtual Number* ArcCotangent() = 0;

    virtual Number* HypSine() = 0;
    virtual Number* HypCosine() = 0;
    virtual Number* HypTangent() = 0;
    virtual Number* HypCosecant() = 0;
    virtual Number* HypSecant() = 0;
    virtual Number* HypCotangent() = 0;

    virtual Number* HypArcSine() = 0;
    virtual Number* HypArcCosine() = 0;
    virtual Number* HypArcTangent() = 0;
    virtual Number* HypArcCosecant() = 0;
    virtual Number* HypArcSecant() = 0;
    virtual Number* HypArcCotangent() = 0;

    friend class PositionalNumeralSystem;
    friend class DecimalSystem;
    friend struct RealNumber;
    friend struct ComplexNumber;

protected:
    NumberSystem system;
};

#endif /* _NUMBER_H */
