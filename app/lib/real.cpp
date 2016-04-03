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

#include "clib.h"
#include "math.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/cplex.h"

RealNumber::RealNumber() :
    Number(nsysreal) {
    x = 0;
}

RealNumber::RealNumber(double x) :
    Number(nsysreal) {
    this->x = x;
}

RealNumber::RealNumber(signed int i) :
    Number(nsysreal) {
    x = i * 1.0;
}

RealNumber::RealNumber(unsigned int i) :
    Number(nsysreal) {
    x = i * 1.0;
}

RealNumber::~RealNumber()
{ }

Number* RealNumber::Clone()
{
    return new RealNumber(x);
}

int RealNumber::GetIntegerValue()
{
    return (int) x;
}

double RealNumber::GetRealValue()
{
    return x;
}

void RealNumber::SetRealValue(double value)
{
    x = value;
}

bool RealNumber::PureComplexValue()
{
    return false;
}

int RealNumber::GetPrecedence()
{
    return (x < 0.0) ? -1 : 0;
}

int RealNumber::GetDefaultPrecedence()
{
    return 0;
}

int RealNumber::IsFinite()
{
    return finite(x);
}

int RealNumber::IsNaN()
{
    return isnan(x);
}

Number* RealNumber::Unary()
{
    return new RealNumber(-x);
}

Number* RealNumber::Add(Number *other)
{
    if (other->system == nsysreal) {
        RealNumber *a = (RealNumber*)other;
        return new RealNumber(x + a->x);
    } else {
        return other->Add(this);
    }
}

Number* RealNumber::Sub(Number *other)
{
    if (other->system == nsysreal) {
        RealNumber *a = (RealNumber*)other;
        return new RealNumber(x - a->x);
    } else {
        Number *y = other->Unary();
        Number *q = y->Add(this);
        delete y;
        return q;
    }
}

Number* RealNumber::Mul(Number *other)
{
    if (other->system == nsysreal) {
        RealNumber *a = (RealNumber*)other;
        return new RealNumber(x * a->x);
    } else {
        return other->Mul(this);
    }
}

Number* RealNumber::Div(Number *other)
{
    if (other->system == nsysreal) {
        RealNumber *a = (RealNumber*)other;
        return new RealNumber(x / a->x);
    } else {
        Number *y = other->Reciprocal();
        Number *q = Mul(y);
        delete y;
        return q;
    }
}

/**
 * @brief Expontation function.
 *
 * See implementation in pow(double, double)
 */
Number* RealNumber::Raise(Number *exponent)
{
    if (exponent->system == nsysreal) {
        return new RealNumber(pow(x, ((RealNumber*)exponent)->x));
    } else {
        ComplexNumber *y = new ComplexNumber(x, 0.0);
        Number *q = y->Raise(exponent);
        delete y;
        return q;
    }
}

/**
 * @brief Mathematical sign function.
 *
 * See implementation in sgn(double)
 */
Number* RealNumber::Signum()
{
    return new RealNumber(sgn(x));
}

/**
 * @brief Mathematical trunc function.
 *
 * See implementation in trunc(double)
 */
Number* RealNumber::Trunc()
{
    return new RealNumber(trunc(x));
}

/**
 * @brief Mathematical round function.
 *
 * See implementation in round(double)
 */
Number* RealNumber::Round()
{
    return new RealNumber(round(x));
}

/**
 * @brief Mathematical floor function.
 *
 * See implementation in floor(double)
 */
Number* RealNumber::Floor()
{
    return new RealNumber(floor(x));
}

/**
 * @brief Mathematical ceiling function.
 *
 * See implementation in ceil(double)
 */
Number* RealNumber::Ceiling()
{
    return new RealNumber(ceil(x));
}

/**
 * @brief Absolute value of number.
 *
 * See implementation in fabs(double)
 */
Number* RealNumber::Absolute()
{
    return new RealNumber(fabs(x));
}

/**
 * @brief Square root function.
 *
 * See implementation of square root in sqrt(double)
 */
Number* RealNumber::SquareRoot()
{
    if (x > 0.0) {
        return new RealNumber(sqrt(x));
    }

    Number *n = new ComplexNumber(x, 0);
    Number *r = n->SquareRoot();
    delete n;
    return r;
}

/**
 * @brief Cube root function.
 *
 * See implementation of cube root in cbrt(double)
 */
Number* RealNumber::CubeRoot()
{
    return new RealNumber(cbrt(x));
}

//TODO: Add comment
Number* RealNumber::Reciprocal()
{
    return new RealNumber(1/x);
}

/**
 * @brief Binary logarithm function (base 2).
 *
 * See implementation of natural logarithm in log(double)
 */
Number* RealNumber::Log2()
{
    return new RealNumber(log(x)/log(2.0));
}

/**
 * @brief Natural logarithm function (base e).
 *
 * See implementation of natural logarithm in log(double)
 */
Number* RealNumber::Log()
{
    return new RealNumber(log(x));
}

/**
 * @brief Base 10 logarithm function.
 *
 * See implementation of base 10 logarithm in log10(double)
 */
Number* RealNumber::Log10()
{
    return new RealNumber(log10(x));
}

/**
 * @brief Trigonometric cosine function.
 *
 * See implementation of cosine function in cos(double)
 */
Number* RealNumber::Cosine()
{
    return new RealNumber(cos(x));
}

/**
 * @brief Trigonometric secant function.
 *
 * See implementation of cosine function in cos(double)
 */
Number* RealNumber::Secant()
{
    return new RealNumber(1.0/cos(x));
}

/**
 * @brief Trigonometric tangent function.
 *
 * See implementation of tangent function in tan(double)
 */
Number* RealNumber::Tangent()
{
    return new RealNumber(tan(x));
}

/**
 * @brief Trigonometric cotangent function.
 *
 * See implementation of tangent function in tan(double)
 */
Number* RealNumber::Cotangent()
{
    return new RealNumber(1.0/tan(x));
}

/**
 * @brief Hyperbolic sine function.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* RealNumber::HypSine()
{
    return new RealNumber(sinh(x));
}

/**
 * @brief Hyperbolic cosecant function.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* RealNumber::HypCosecant()
{
    return new RealNumber(1.0/sinh(x));
}

/**
 * @brief Hyperbolic cosine function.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* RealNumber::HypCosine()
{
    return new RealNumber(cosh(x));
}

/**
 * @brief Hyperbolic secant function.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* RealNumber::HypSecant()
{
    return new RealNumber(1.0/cosh(x));
}

/**
 * @brief Hyperbolic tangent function.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* RealNumber::HypTangent()
{
    return new RealNumber(tanh(x));
}

/**
 * @brief Hyperbolic cotangent function.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* RealNumber::HypCotangent()
{
    return new RealNumber(1.0/tanh(x));
}

/**
 * @brief Trigonometric sine function.
 *
 * See implementation of sine function in sin(double)
 */
Number* RealNumber::Sine()
{
    return new RealNumber(sin(x));
}

/**
 * @brief Trigonometric cosecant function.
 *
 * See implementation of sine function in sin(double)
 */
Number* RealNumber::Cosecant()
{
    return new RealNumber(1.0/sin(x));
}

/**
 * @brief Inverse trigonometric cosine function.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* RealNumber::ArcCosine()
{
    return new RealNumber(acos(x));
}

/**
 * @brief Inverse trigonometric secant function.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* RealNumber::ArcSecant()
{
    return new RealNumber(acos(1.0/x));
}

/**
 * @brief Inverse trigonometric tangent function.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* RealNumber::ArcTangent()
{
    return new RealNumber(atan(x));
}

/**
 * @brief Inverse trigonometric cotangent function.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* RealNumber::ArcCotangent()
{
    return new RealNumber(atan(1.0/x));
}

/**
 * @brief Inverse trigonometric sine function.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* RealNumber::ArcSine()
{
    return new RealNumber(asin(x));
}

/**
 * @brief Inverse trigonometric cosecant function.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* RealNumber::ArcCosecant()
{
    return new RealNumber(asin(1.0/x));
}

/**
 * @brief Inverse hyperbolic cosine function.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* RealNumber::HypArcCosine()
{
    return new RealNumber(acosh(x));
}

/**
 * @brief Inverse hyperbolic secant function.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* RealNumber::HypArcSecant()
{
    return new RealNumber(acosh(1.0/x));
}

/**
 * @brief Inverse hyperbolic sine function.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* RealNumber::HypArcSine()
{
    return new RealNumber(asinh(x));
}

/**
 * @brief Inverse hyperbolic cosecant function.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* RealNumber::HypArcCosecant()
{
    return new RealNumber(asinh(1.0/x));
}

/**
 * @brief Inverse hyperbolic tangent function.
 *
 * See implementation hyperbolic tangent in atanh(double)
 */
Number* RealNumber::HypArcTangent()
{
    return new RealNumber(atanh(x));
}

/**
 * @brief Inverse hyperbolic cotangent function.
 *
 * See implementation hyperbolic tangent in atanh(double)
 */
Number* RealNumber::HypArcCotangent()
{
    return new RealNumber(atanh(1.0/x));
}
