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

#ifndef AMATH_NON_NUMBER_H
#define AMATH_NON_NUMBER_H

/**
 * @file  nnumb.h
 * @brief Class based handling of Infinity and Not A Number
 */

#include "numb.h"

typedef enum
{
    nnnan,
    nninf,
    nnninf,
    nnnimp
} NonNumberType;

/**
 * @brief Represent a number which does not exists
 */
struct NonNumber : public Number
{
public:
    explicit NonNumber(NonNumberType type);
    ~NonNumber();

    Number* Clone();
    int GetIntegerValue();
    double GetRealValue();
    bool PureComplexValue();
    int GetPrecedence();
    int GetDefaultPrecedence();
    bool IsNegative();
    bool IsZero();
    bool IsNaN();
    bool IsInfinite();
    bool IsNotImplemented();

    Number* Unary();
    Number* Add(Number* other);
    Number* Sub(Number* other);
    Number* Mul(Number* other);
    Number* Div(Number* other);
    Number* Raise(Number* exponent);

    Number* Signum();
    Number* Trunc();
    Number* Round();
    Number* Floor();
    Number* Ceiling();
    Number* Absolute();
    Number* SquareRoot();
    Number* CubeRoot();
    Number* Reciprocal();
    Number* Factorial();

    Number* Log();
    Number* Log2();
    Number* Log10();

    Number* Sine();
    Number* Cosine();
    Number* Tangent();
    Number* Cosecant();
    Number* Secant();
    Number* Cotangent();
    Number* Chord();
    Number* ExSecant();
    Number* ExCosecant();
    Number* ArcSine();
    Number* ArcCosine();
    Number* ArcTangent();
    Number* ArcCosecant();
    Number* ArcSecant();
    Number* ArcCotangent();
    Number* ArcExSecant();
    Number* ArcExCosecant();
    Number* ArcChord();

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

    Number* VerSine();
    Number* VerCosine();
    Number* CoVerSine();
    Number* CoVerCosine();
    Number* HaVerSine();
    Number* HaVerCosine();
    Number* HaCoVerSine();
    Number* HaCoVerCosine();

    Number* ArcVerSine();
    Number* ArcVerCosine();
    Number* ArcCoVerSine();
    Number* ArcCoVerCosine();
    Number* ArcHaVerSine();
    Number* ArcHaVerCosine();
    Number* ArcHaCoVerSine();
    Number* ArcHaCoVerCosine();

private:
    NonNumberType type;
};

#endif
