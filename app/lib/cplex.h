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

#ifndef _COMPLEX_NUMBER_H
#define _COMPLEX_NUMBER_H

/**
 * @file  cplex.h
 * @brief Classbase handling of complex numbers.
 *
 */

#include "complex.h"
#include "lib/numb.h"

/**
 * @brief Represent a complex number with 2 componts of 15
 *        siginificant digits.
 *
 * Calculations are done using 64 bit IEEE 754 arithmetics.
 *
 */
struct ComplexNumber : public Number {
public:
    ComplexNumber();
    ComplexNumber(complex z);
    ComplexNumber(double real, double imag);
    ~ComplexNumber();

    Number* Clone();
    int GetIntegerValue();
    double GetRealValue();
    double GetImagValue();
    complex GetComplexValue();
    bool PureComplexValue();
    int GetPrecedence();
    int GetDefaultPrecedence();

    Number* Unary();
    Number* Add(Number *other);
    Number* Sub(Number *other);
    Number* Mul(Number *other);
    Number* Div(Number *other);
    Number* Raise(Number *exponent);

    Number* Signum();
    Number* Trunc();
    Number* Round();
    Number* Floor();
    Number* Ceiling();
    Number* Absolute();
    Number* SquareRoot();
    Number* CubeRoot();
    Number* Reciprocal();

    Number* Log();
    Number* Log2();
    Number* Log10();

    Number* Sine();
    Number* Cosine();
    Number* Tangent();
    Number* Cosecant();
    Number* Secant();
    Number* Cotangent();

    Number* ArcSine();
    Number* ArcCosine();
    Number* ArcTangent();
    Number* ArcCosecant();
    Number* ArcSecant();
    Number* ArcCotangent();

    Number* HypSine();
    Number* HypCosine();
    Number* HypTangent();
    Number* HypCosecant();
    Number* HypSecant();
    Number* HypCotangent();

    Number* HypArcSine();
    Number* HypArcCosine();
    Number* HypArcTangent();
    Number* HypArcCosecant();
    Number* HypArcSecant();
    Number* HypArcCotangent();

private:
    complex z;
};

#endif
