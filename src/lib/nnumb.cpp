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

#include "numb.h"
#include "nnumb.h"

NonNumber::NonNumber(NonNumberType type) :
    Number(nsysreal)
{
    this->type = type;
}

NonNumber::~NonNumber()
{
}

Number* NonNumber::Clone()
{
    return new NonNumber(type);
}

int NonNumber::GetIntegerValue()
{
    return 0;
}

double NonNumber::GetRealValue()
{
    return 0.0;
}

bool NonNumber::PureComplexValue()
{
    return false;
}

int NonNumber::GetPrecedence()
{
    return 0;
}

int NonNumber::GetDefaultPrecedence()
{
    return 0;
}

bool NonNumber::IsZero()
{
    return false;
}

bool NonNumber::IsTooSmall()
{
    return type == nnninf;
}

bool NonNumber::IsTooLarge()
{
    return type == nninf;
}

bool NonNumber::IsNaN()
{
    return type == nnnan;
}

bool NonNumber::IsNotImplemented()
{
    return type == nnnimp;
}

Number* NonNumber::Unary()
{
    return new NonNumber(type);
}

Number* NonNumber::Add(Number* other)
{
    return new NonNumber(type);
}

Number* NonNumber::Sub(Number* other)
{
    return new NonNumber(type);
}

Number* NonNumber::Mul(Number* other)
{
    return new NonNumber(type);
}

Number* NonNumber::Div(Number* other)
{
    return new NonNumber(type);
}

Number* NonNumber::Raise(Number* exponent)
{
    return new NonNumber(type);
}

Number* NonNumber::Signum()
{
    return new NonNumber(type);
}

Number* NonNumber::Trunc()
{
    return new NonNumber(type);
}

Number* NonNumber::Round()
{
    return new NonNumber(type);
}

Number* NonNumber::Floor()
{
    return new NonNumber(type);
}

Number* NonNumber::Ceiling()
{
    return new NonNumber(type);
}

Number* NonNumber::Absolute()
{
    return new NonNumber(type);
}

Number* NonNumber::SquareRoot()
{
    return new NonNumber(type);
}

Number* NonNumber::CubeRoot()
{
    return new NonNumber(type);
}

Number* NonNumber::Reciprocal()
{
    return new NonNumber(type);
}

Number* NonNumber::Factorial()
{
    return new NonNumber(type);
}

Number* NonNumber::Log2()
{
    return new NonNumber(type);
}

Number* NonNumber::Log()
{
    return new NonNumber(type);
}

Number* NonNumber::Log10()
{
    return new NonNumber(type);
}

Number* NonNumber::Cosine()
{
    return new NonNumber(type);
}

Number* NonNumber::Secant()
{
    return new NonNumber(type);
}

/**
 * @brief Trigonometric tangent function
 * 
 * Tangent of +INF and -INF is NaN (with signals).
 * Tangent of NaN is NaN.
 * 
 * Signals are not implemented.
 * 
 */
Number* NonNumber::Tangent()
{
    return new NonNumber(nnnan);
}

Number* NonNumber::Cotangent()
{
    return new NonNumber(type);
}

Number* NonNumber::HypSine()
{
    return new NonNumber(type);
}

Number* NonNumber::HypCosecant()
{
    return new NonNumber(type);
}

Number* NonNumber::HypCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::HypSecant()
{
    return new NonNumber(type);
}

Number* NonNumber::HypTangent()
{
    return new NonNumber(type);
}

Number* NonNumber::HypCotangent()
{
    return new NonNumber(type);
}

Number* NonNumber::Sine()
{
    return new NonNumber(type);
}

Number* NonNumber::Cosecant()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcSecant()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcTangent()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcCotangent()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcSine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcCosecant()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcSecant()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcSine()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcCosecant()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcTangent()
{
    return new NonNumber(type);
}

Number* NonNumber::HypArcCotangent()
{
    return new NonNumber(type);
}

Number* NonNumber::VerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::VerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::CoVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::CoVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::HaVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::HaVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::HaCoVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::HaCoVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcCoVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcCoVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcHaVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcHaVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcHaCoVerSine()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcHaCoVerCosine()
{
    return new NonNumber(type);
}

Number* NonNumber::ExSecant()
{
    return new NonNumber(type);
}

Number* NonNumber::ExCosecant()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcExSecant()
{
    return new NonNumber(type);
}

Number* NonNumber::ArcExCosecant()
{
    return new NonNumber(type);
}
