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

#include "mathr.h"
#include "amath.h"
#include "numb.h"
#include "real.h"
#include "cplex.h"
#include "nnumb.h"

RealNumber::RealNumber() : Number(nsysreal)
{
    x = 0;
}

RealNumber::RealNumber(double x) : Number(nsysreal)
{
    this->x = x;
}

RealNumber::RealNumber(double x, bool round) : Number(nsysreal)
{
    if ((round && ((x > 0 && x < 1e-15) || (x < 0 && x > -1e-15))))
    {
        this->x = 0.0;
    }
    else if (round && x > 1e+16)
    {
        FloatUnion64 d;
        d.integer = INFP;
        this->x = d.floatingPoint;
    }
    else if (round && x < -1e+16)
    {
        FloatUnion64 d;
        d.integer = INFN;
        this->x = d.floatingPoint;
    }
    else
    {
        this->x = x;
    }
}

RealNumber::RealNumber(signed int i) : Number(nsysreal)
{
    x = i * 1.0;
}

RealNumber::RealNumber(unsigned int i) : Number(nsysreal)
{
    x = i * 1.0;
}

RealNumber::~RealNumber()
{
}

Number *RealNumber::Clone()
{
    return new RealNumber(x);
}

int RealNumber::GetIntegerValue()
{
    return static_cast<int>(x);
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

bool RealNumber::IsNegative()
{
    FloatUnion64 d;
    d.floatingPoint = x;
    return d.IsNegative();
}

/**
 * @brief Returns true if number is zero
 */
bool RealNumber::IsZero()
{
    FloatUnion64 d;
    d.floatingPoint = x;
    return d.IsZero();
}

/**
 * @brief Returns true if number is NaN
 */
bool RealNumber::IsNaN()
{
    FloatUnion64 d;
    d.floatingPoint = x;
    return d.IsNaN();
}

/**
 * @brief Returns true if number is infinite
 */
bool RealNumber::IsInfinite()
{
    // Handle subnormal values
    if ((x > 0 && x <= 1e-308) || (x < 0 && x >= -1e-308))
    {
        return true;
    }

    FloatUnion64 d;
    d.floatingPoint = x;
    return d.IsInf() || d.IsMaxPositive() || d.IsMaxNegative();
}

/**
 * @brief Always returns false for real numbers
 */
bool RealNumber::IsNotImplemented()
{
    return false;
}

/**
 * @brief Change sign of real number
 */
Number *RealNumber::Unary()
{
    return new RealNumber(-x);
}

/**
 * @brief Addition of two real numbers
 */
Number *RealNumber::Add(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new RealNumber(x + a->x);
    }

    return other->Add(this);
}

/**
 * @brief Subtraction of two real numbers
 */
Number *RealNumber::Sub(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new RealNumber(x - a->x);
    }

    Number *y = other->Unary();
    Number *q = y->Add(this);
    delete y;
    return q;
}

/**
 * @brief Multiplication of two real numbers
 */
Number *RealNumber::Mul(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new RealNumber(x * a->x);
    }

    return other->Mul(this);
}

/**
 * @brief Division of two real numbers
 */
Number *RealNumber::Div(Number *other)
{
    if (other->IsZero() || other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new RealNumber(x / a->x);
    }

    Number *y = other->Reciprocal();
    Number *q = Mul(y);
    delete y;
    return q;
}

/**
 * @brief   Exponentiation function for real numbers
 * @details See implementation in pow(double, double)
 */
Number *RealNumber::Raise(Number *exponent)
{
    if (exponent->IsNaN())
        return new NonNumber(nnnan);

    if (exponent->system == nsysreal)
        return new RealNumber(pow(x, static_cast<RealNumber *>(exponent)->x));

    ComplexNumber *y = new ComplexNumber(x, 0.0);
    Number *q = y->Raise(exponent);
    delete y;
    return q;
}

/**
 * @brief   Mathematical sign function for real numbers
 * @details See implementation in sgn(double)
 */
Number *RealNumber::Signum()
{
    return new RealNumber(sgn(x));
}

/**
 * @brief   Mathematical trunc function for real numbers
 * @details See implementation in trunc(double)
 */
Number *RealNumber::Trunc()
{
    return new RealNumber(trunc(x));
}

/**
 * @brief   Mathematical round function for real numbers
 * @details See implementation in round(double)
 */
Number *RealNumber::Round()
{
    return new RealNumber(round(x));
}

/**
 * @brief   Mathematical floor function for real numbers
 * @details See implementation in floor(double)
 */
Number *RealNumber::Floor()
{
    return new RealNumber(floor(x));
}

/**
 * @brief   Mathematical ceiling function for real numbers
 * @details See implementation in ceil(double)
 */
Number *RealNumber::Ceiling()
{
    return new RealNumber(ceil(x));
}

/**
 * @brief   Absolute value of number for real numbers
 * @details See implementation in fabs(double)
 */
Number *RealNumber::Absolute()
{
    return new RealNumber(fabs(x));
}

/**
 * @brief   Square root function for real numbers
 * @details See implementation of square root in sqrt(double)
 */
Number *RealNumber::SquareRoot()
{
    if (x > 0.0)
        return new RealNumber(sqrt(x));

    Number *n = new ComplexNumber(x, 0);
    Number *r = n->SquareRoot();
    delete n;
    return r;
}

/**
 * @brief   Cube root function for real numbers
 * @details See implementation of cube root in cbrt(double)
 */
Number *RealNumber::CubeRoot()
{
    if (x >= 0.0)
        return new RealNumber(cbrt(x));
    
    Number *n = new ComplexNumber(x, 0);
    Number *r = n->CubeRoot();
    delete n;
    return r;
}

/**
 * @brief Reciprocal function for real numbers
 */
Number *RealNumber::Reciprocal()
{
    if (x != 0.0)
        return new RealNumber(1.0 / x);

    return new NonNumber(nnnan);
}

/**
 * @brief Factorial function for real numbers
 */
Number *RealNumber::Factorial()
{
    return new NonNumber(nnnimp);
}

/**
 * @brief   Binary logarithm function (base 2) for real numbers
 * @details See implementation of natural logarithm in log(double)
 */
Number *RealNumber::Log2()
{
    static const double log2value = 0.69314718055994530942;
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log(x) / log2value);

    Number *n = new ComplexNumber(x, 0);
    Number *r = n->Log2();
    delete n;
    return r;
}

/**
 * @brief   Natural logarithm function (base e) for real numbers
 * @details See implementation of natural logarithm in log(double)
 */
Number *RealNumber::Log()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log(x));

    Number *n = new ComplexNumber(x, 0);
    Number *r = n->Log();
    delete n;
    return r;
}

/**
 * @brief   Base 10 logarithm function for real numbers
 * @details See implementation of base 10 logarithm in log10(double)
 */
Number *RealNumber::Log10()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log10(x));

    Number *n = new ComplexNumber(x, 0);
    Number *r = n->Log10();
    delete n;
    return r;
}

/**
 * @brief   Trigonometric sine function for real numbers
 * @details See implementation of sine function in sin(double)
 */
Number *RealNumber::Sine()
{
    return new RealNumber(sin(x), true);
}

/**
 * @brief   Trigonometric cosine function for real numbers
 * @details See implementation of cosine function in cos(double)
 */
Number *RealNumber::Cosine()
{
    return new RealNumber(cos(x), true);
}

/**
 * @brief   Trigonometric tangent function for real numbers
 * @details See implementation of tangent function in tan(double)
 */
Number *RealNumber::Tangent()
{
    return new RealNumber(tan(x), true);
}

/**
 * @brief   Trigonometric secant function for real numbers
 * @details See implementation of secant function in sec(double)
 */
Number *RealNumber::Secant()
{
    double a = sec(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Trigonometric cosecant function for real numbers
 * @details See implementation of cosecant function in csc(double)
 */
Number *RealNumber::Cosecant()
{
    double a = csc(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Trigonometric cotangent function for real numbers
 * @details See implementation of cotangent function in cot(double)
 */
Number *RealNumber::Cotangent()
{
    double a = cot(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Trigonometric chord function for real numbers
 * @details See implementation of chord function in crd(double)
 */
Number *RealNumber::Chord()
{
    return new RealNumber(crd(x), true);
}

/**
 * @brief   Trigonometric exsecant function for real numbers
 * @details See implementation of exsecant function in exs(double)
 */
Number *RealNumber::ExSecant()
{
    return new RealNumber(exs(x), true);
}

/**
 * @brief   Trigonometric excosecant function for real numbers
 * @details See implementation of excosecant function in exc(double)
 */
Number *RealNumber::ExCosecant()
{
    return new RealNumber(exc(x), true);
}

/**
 * @brief   Inverse trigonometric sine function for real numbers
 * @details See implementation of inverse trigonometric sine in asin(double)
 */
Number *RealNumber::ArcSine()
{
    return new RealNumber(asin(x), true);
}

/**
 * @brief   Inverse trigonometric cosine function for real numbers
 * @details See implementation of inverse trigonometric cosine in acos(double)
 */
Number *RealNumber::ArcCosine()
{
    return new RealNumber(acos(x), true);
}

/**
 * @brief   Inverse trigonometric tangent function for real numbers
 * @details See implementation of inverse trigonometric tangent in atan(double)
 */
Number *RealNumber::ArcTangent()
{
    return new RealNumber(atan(x), true);
}

/**
 * @brief   Inverse trigonometric secant function for real numbers
 * @details See implementation of inverse trigonometric secant in asec(double)
 */
Number *RealNumber::ArcSecant()
{
    double a = asec(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse trigonometric cosecant function for real numbers
 * @details See implementation of inverse trigonometric cosecant in acsc(double)
 */
Number *RealNumber::ArcCosecant()
{
    double a = acsc(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse trigonometric cotangent function for real numbers
 * @details See implementation of inverse trigonometric cotangent in acot(double)
 */
Number *RealNumber::ArcCotangent()
{
    double a = acot(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse trigonometric chord function for real numbers
 * @details See implementation of Inverse chord function in acrd(double)
 */
Number *RealNumber::ArcChord()
{
    return new RealNumber(acrd(x), true);
}

/**
 * @brief   Inverse trigonometric exsecant function for real numbers
 * @details See implementation of Inverse exsecant function in aexs(double)
 */
Number *RealNumber::ArcExSecant()
{
    return new RealNumber(aexs(x), true);
}

/**
 * @brief   Inverse trigonometric excosecant function for real numbers
 * @details See implementation of Inverse excosecant function in aexc(double)
 */
Number *RealNumber::ArcExCosecant()
{
    return new RealNumber(aexc(x), true);
}

/**
 * @brief   Hyperbolic sine function for real numbers
 * @details See implementation of hyperbolic sine function in sinh(double)
 */
Number *RealNumber::HypSine()
{
    return new RealNumber(sinh(x), true);
}

/**
 * @brief   Hyperbolic cosine function for real numbers
 * @details See implementation of hyperbolic cosine function in cosh(double)
 */
Number *RealNumber::HypCosine()
{
    return new RealNumber(cosh(x), true);
}

/**
 * @brief   Hyperbolic tangent function for real numbers
 * @details See implementation of hyperbolic tangent function in tanh(double)
 */
Number *RealNumber::HypTangent()
{
    return new RealNumber(tanh(x), true);
}

/**
 * @brief   Hyperbolic secant function for real numbers
 * @details See implementation of hyperbolic secant function in sech(double)
 */
Number *RealNumber::HypSecant()
{
    double a = sech(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Hyperbolic cosecant function for real numbers
 * @details See implementation of hyperbolic sine function in csch(double)
 */
Number *RealNumber::HypCosecant()
{
    double a = csch(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Hyperbolic cotangent function for real numbers
 * @details See implementation of hyperbolic tangent function in coth(double)
 */
Number *RealNumber::HypCotangent()
{
    double a = coth(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse hyperbolic sine function for real numbers
 * @details See implementation of inverse hyperbolic sine in asinh(double)
 */
Number *RealNumber::HypArcSine()
{
    return new RealNumber(asinh(x), true);
}

/**
 * @brief   Inverse hyperbolic cosine function for real numbers
 * @details See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number *RealNumber::HypArcCosine()
{
    return new RealNumber(acosh(x), true);
}

/**
 * @brief   Inverse hyperbolic tangent function for real numbers
 * @details See implementation of hyperbolic tangent in atanh(double)
 */
Number *RealNumber::HypArcTangent()
{
    return new RealNumber(atanh(x), true);
}

/**
 * @brief   Inverse hyperbolic secant function for real numbers
 * @details See implementation of inverse hyperbolic secant in asech(double)
 */
Number *RealNumber::HypArcSecant()
{
    double a = asech(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse hyperbolic cosecant function for real numbers
 * @details See implementation of inverse hyperbolic cosecant in acsch(double)
 */
Number *RealNumber::HypArcCosecant()
{
    double a = acsch(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse hyperbolic cotangent function for real numbers
 * @details See implementation of hyperbolic cotangent in acoth(double)
 */
Number *RealNumber::HypArcCotangent()
{
    double a = acoth(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Versed sine function for real numbers
 * @details See implementation of versed sine in ver(double)
 */
Number *RealNumber::VerSine()
{
    return new RealNumber(ver(x), true);
}

/**
 * @brief   Versed cosine function for real numbers
 * @details See implementation of versed cosine in vcs(double)
 */
Number *RealNumber::VerCosine()
{
    return new RealNumber(vcs(x), true);
}

/**
 * @brief   Coversed sine function for real numbers
 * @details See implementation of coversed sine in cvs(double)
 */
Number *RealNumber::CoVerSine()
{
    return new RealNumber(cvs(x), true);
}

/**
 * @brief   Coversed cosine function for real numbers
 * @details See implementation of coversed cosine in cvc(double)
 */
Number *RealNumber::CoVerCosine()
{
    return new RealNumber(cvc(x), true);
}

/**
 * @brief   Haversed sine function for real numbers
 * @details See implementation of haversed sine in hv(double)
 */
Number *RealNumber::HaVerSine()
{
    return new RealNumber(hv(x), true);
}

/**
 * @brief   Haversed cosine function for real numbers
 * @details See implementation of haversed cosine in hvc(double)
 */
Number *RealNumber::HaVerCosine()
{
    return new RealNumber(hvc(x), true);
}

/**
 * @brief   Hacoversed sine function for real numbers
 * @details See implementation of hacoversed cosine in hcv(double)
 */
Number *RealNumber::HaCoVerSine()
{
    return new RealNumber(hcv(x), true);
}

/**
 * @brief   Hacoversed cosine function for real numbers
 * @details See implementation of hacoversed cosine in hcc(double)
 */
Number *RealNumber::HaCoVerCosine()
{
    return new RealNumber(hcc(x), true);
}

/**
 * @brief   Inverse versed sine function for real numbers
 * @details See implementation of inverse versed sine in aver(double)
 */
Number *RealNumber::ArcVerSine()
{
    double a = aver(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse versed cosine function for real numbers
 * @details See implementation of inverse versed cosine sine in avcs(double)
 */
Number *RealNumber::ArcVerCosine()
{
    double a = avcs(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse coversed sine function for real numbers
 * @details See implementation of inverse coversed sine in acvs(double)
 */
Number *RealNumber::ArcCoVerSine()
{
    double a = acvs(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse coversed cosine function for real numbers
 * @details See implementation of inverse coversed cosine in acvc(double)
 */
Number *RealNumber::ArcCoVerCosine()
{
    double a = acvc(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse haversed sine function for real numbers
 * @details See implementation of inverse haversed sine in ahv(double)
 */
Number *RealNumber::ArcHaVerSine()
{
    double a = ahv(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse haversed cosine function for real numbers
 * @details See implementation of inverse haversed cosine in ahvc(double)
 */
Number *RealNumber::ArcHaVerCosine()
{
    double a = ahvc(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse hacoversed sine function for real numbers
 * @details See implementation of inverse hacoversed sine in ahcv(double)
 */
Number *RealNumber::ArcHaCoVerSine()
{
    double a = ahcv(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}

/**
 * @brief   Inverse hacoversed cosine function for real numbers
 * @details See implementation of inverse hacoversed cosine in ahcc(double)
 */
Number *RealNumber::ArcHaCoVerCosine()
{
    double a = ahcc(x);
    return a != NAN
        ? (Number *)new RealNumber(a, true)
        : (Number *)new NonNumber(nnnan);
}
