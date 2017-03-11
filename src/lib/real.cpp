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

#include "math.h"
#include "amath.h"
#include "numb.h"
#include "real.h"
#include "cplex.h"
#include "nnumb.h"
#include "integer.h"

RealNumber::RealNumber() :
    Number(nsysreal)
{
    x = 0;
}

RealNumber::RealNumber(double x) :
    Number(nsysreal)
{
    this->x = x;
}

RealNumber::RealNumber(double x, bool round) :
    Number(nsysreal)
{
    if ((round && ((x > 0 && x < 1e-15) || (x < 0 && x > -1e-15))))
    {
        this->x = 0.0;
    }
    else
    {
        this->x = x;
    }
}

RealNumber::RealNumber(signed int i) :
    Number(nsysreal)
{
    x = i * 1.0;
}

RealNumber::RealNumber(unsigned int i) :
    Number(nsysreal)
{
    x = i * 1.0;
}

RealNumber::~RealNumber()
{
}

Number* RealNumber::Clone()
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

/**
 * @brief Returns true if number is zero.
 *
 */
bool RealNumber::IsZero()
{
    return x == 0.0;
}

/**
 * @brief Returns true if number is finite.
 *
 */
bool RealNumber::IsTooSmall()
{
    return (x > 0 && x < D_INFN) || (x < 0 && x > -D_INFN);
}

/**
 * @brief Returns true if number is finite.
 *
 */
bool RealNumber::IsTooLarge()
{
    return x > D_INFP;
}

/**
 * @brief Always return false for real numbers.
 *
 */
bool RealNumber::IsNaN()
{
    return false;
}

/**
 * @brief Always return false for real numbers.
 *
 */
bool RealNumber::IsNotImplemented()
{
    return false;
}

/**
 * @brief Change sign of real number.
 *
 */
Number* RealNumber::Unary()
{
    return new RealNumber(-x);
}

/**
 * @brief Addition of two real numbers.
 *
 */
Number* RealNumber::Add(Number* other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber* a = static_cast<RealNumber*>(other);
        return new RealNumber(x + a->x);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        return new RealNumber(x + static_cast<double>(a->i));
    }

    return other->Add(this);
}

/**
 * @brief Subtraction of two real numbers.
 *
 */
Number* RealNumber::Sub(Number* other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber* a = static_cast<RealNumber*>(other);
        return new RealNumber(x - a->x);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        return new RealNumber(x - static_cast<double>(a->i));
    }

    Number* y = other->Unary();
    Number* q = y->Add(this);
    delete y;
    return q;
}

/**
 * @brief Multiplication of two real numbers.
 *
 */
Number* RealNumber::Mul(Number* other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber* a = static_cast<RealNumber*>(other);
        return new RealNumber(x * a->x);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        return new RealNumber(x * static_cast<double>(a->i));
    }

    return other->Mul(this);
}

/**
 * @brief Division of two real numbers.
 *
 */
Number* RealNumber::Div(Number* other)
{
    if (other->IsZero() || other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsysreal)
    {
        RealNumber* a = static_cast<RealNumber*>(other);
        return new RealNumber(x / a->x);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        return new RealNumber(x / static_cast<double>(a->i));
    }

    Number* y = other->Reciprocal();
    Number* q = Mul(y);
    delete y;
    return q;
}

/**
 * @brief Exponentiation function for real numbers.
 *
 * See implementation in pow(double, double)
 */
Number* RealNumber::Raise(Number* exponent)
{
    if (exponent->IsNaN())
        return new NonNumber(nnnan);

    if (exponent->system == nsysreal)
        return new RealNumber(pow(x, static_cast<RealNumber*>(exponent)->x));

    if (exponent->system == nsysinteger)
        return new RealNumber(pow(x, static_cast<double>(static_cast<IntegerNumber*>(exponent)->i)));

    ComplexNumber* y = new ComplexNumber(x, 0.0);
    Number* q = y->Raise(exponent);
    delete y;
    return q;
}

/**
 * @brief Mathematical sign function for real numbers.
 *
 * See implementation in sgn(double)
 */
Number* RealNumber::Signum()
{
    return new RealNumber(sgn(x));
}

/**
 * @brief Mathematical trunc function for real numbers.
 *
 * See implementation in trunc(double)
 */
Number* RealNumber::Trunc()
{
    return new RealNumber(trunc(x));
}

/**
 * @brief Mathematical round function for real numbers.
 *
 * See implementation in round(double)
 */
Number* RealNumber::Round()
{
    return new RealNumber(round(x));
}

/**
 * @brief Mathematical floor function for real numbers.
 *
 * See implementation in floor(double)
 */
Number* RealNumber::Floor()
{
    return new RealNumber(floor(x));
}

/**
 * @brief Mathematical ceiling function for real numbers.
 *
 * See implementation in ceil(double)
 */
Number* RealNumber::Ceiling()
{
    return new RealNumber(ceil(x));
}

/**
 * @brief Absolute value of number for real numbers.
 *
 * See implementation in fabs(double)
 */
Number* RealNumber::Absolute()
{
    return new RealNumber(fabs(x));
}

/**
 * @brief Square root function for real numbers.
 *
 * See implementation of square root in sqrt(double)
 */
Number* RealNumber::SquareRoot()
{
    if (x > 0.0)
        return new RealNumber(sqrt(x));

    Number* n = new ComplexNumber(x, 0);
    Number* r = n->SquareRoot();
    delete n;
    return r;
}

/**
 * @brief Cube root function for real numbers.
 *
 * See implementation of cube root in cbrt(double)
 */
Number* RealNumber::CubeRoot()
{
    return new RealNumber(cbrt(x));
}

/**
 * @brief Reciprocal function for real numbers.
 *
 */
Number* RealNumber::Reciprocal()
{
    if (x != 0.0)
        return new RealNumber(1.0 / x);

    return new NonNumber(nnnan);
}

/**
 * @brief Factorial function for real numbers.
 *
 */
Number* RealNumber::Factorial()
{
    return new NonNumber(nnnimp);
}

/**
 * @brief Binary logarithm function (base 2) for real numbers.
 *
 * See implementation of natural logarithm in log(double)
 */
Number* RealNumber::Log2()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log(x) / LOG2);

    Number* n = new ComplexNumber(x, 0);
    Number* r = n->Log2();
    delete n;
    return r;
}

/**
 * @brief Natural logarithm function (base e) for real numbers.
 *
 * See implementation of natural logarithm in log(double)
 */
Number* RealNumber::Log()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log(x));

    Number* n = new ComplexNumber(x, 0);
    Number* r = n->Log();
    delete n;
    return r;
}

/**
 * @brief Base 10 logarithm function for real numbers.
 *
 * See implementation of base 10 logarithm in log10(double)
 */
Number* RealNumber::Log10()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    if (x > 0.0)
        return new RealNumber(log10(x));

    Number* n = new ComplexNumber(x, 0);
    Number* r = n->Log10();
    delete n;
    return r;
}

/**
 * @brief Trigonometric cosine function for real numbers.
 *
 * See implementation of cosine function in cos(double)
 */
Number* RealNumber::Cosine()
{
    return new RealNumber(cos(x), true);
}

/**
 * @brief Trigonometric secant function for real numbers.
 *
 * See implementation of cosine function in cos(double)
 */
Number* RealNumber::Secant()
{
    double a = cos(x);

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Trigonometric tangent function for real numbers.
 *
 * See implementation of tangent function in tan(double)
 */
Number* RealNumber::Tangent()
{
    return new RealNumber(tan(x), true);
}

/**
 * @brief Trigonometric cotangent function for real numbers.
 *
 * See implementation of tangent function in tan(double)
 */
Number* RealNumber::Cotangent()
{
    double a = tan(x);

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Hyperbolic sine function for real numbers.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* RealNumber::HypSine()
{
    return new RealNumber(sinh(x));
}

/**
 * @brief Hyperbolic cosecant function for real numbers.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* RealNumber::HypCosecant()
{
    double a = sinh(x);

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Hyperbolic cosine function for real numbers.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* RealNumber::HypCosine()
{
    return new RealNumber(cosh(x));
}

/**
 * @brief Hyperbolic secant function for real numbers.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* RealNumber::HypSecant()
{
    return new RealNumber(1.0 / cosh(x));
}

/**
 * @brief Hyperbolic tangent function for real numbers.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* RealNumber::HypTangent()
{
    return new RealNumber(tanh(x));
}

/**
 * @brief Hyperbolic cotangent function for real numbers.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* RealNumber::HypCotangent()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / tanh(x));
}

/**
 * @brief Trigonometric sine function for real numbers.
 *
 * See implementation of sine function in sin(double)
 */
Number* RealNumber::Sine()
{
    return new RealNumber(sin(x), true);
}

/**
 * @brief Trigonometric cosecant function for real numbers.
 *
 * See implementation of sine function in sin(double)
 */
Number* RealNumber::Cosecant()
{
    double a = sin(x);

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Inverse trigonometric cosine function for real numbers.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* RealNumber::ArcCosine()
{
    return new RealNumber(acos(x));
}

/**
 * @brief Inverse trigonometric secant function for real numbers.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* RealNumber::ArcSecant()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(acos(1.0 / x));
}

/**
 * @brief Inverse trigonometric tangent function for real numbers.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* RealNumber::ArcTangent()
{
    return new RealNumber(atan(x));
}

/**
 * @brief Inverse trigonometric cotangent function for real numbers.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* RealNumber::ArcCotangent()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(atan(1.0 / x));
}

/**
 * @brief Inverse trigonometric sine function for real numbers.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* RealNumber::ArcSine()
{
    return new RealNumber(asin(x));
}

/**
 * @brief Inverse trigonometric cosecant function for real numbers.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* RealNumber::ArcCosecant()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(asin(1.0 / x));
}

/**
 * @brief Inverse hyperbolic cosine function for real numbers.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* RealNumber::HypArcCosine()
{
    return new RealNumber(acosh(x));
}

/**
 * @brief Inverse hyperbolic secant function for real numbers.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* RealNumber::HypArcSecant()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(acosh(1.0 / x));
}

/**
 * @brief Inverse hyperbolic sine function for real numbers.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* RealNumber::HypArcSine()
{
    return new RealNumber(asinh(x));
}

/**
 * @brief Inverse hyperbolic cosecant function for real numbers.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* RealNumber::HypArcCosecant()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(asinh(1.0 / x));
}

/**
 * @brief Inverse hyperbolic tangent function for real numbers.
 *
 * See implementation of hyperbolic tangent in atanh(double)
 */
Number* RealNumber::HypArcTangent()
{
    return new RealNumber(atanh(x));
}

/**
 * @brief Inverse hyperbolic cotangent function for real numbers.
 *
 * See implementation of hyperbolic tangent in atanh(double)
 */
Number* RealNumber::HypArcCotangent()
{
    if (x == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(atanh(1.0 / x));
}

/**
 * @brief Versed sine function for real numbers.
 *
 * See implementation of cosine in cos(double)
 */
Number* RealNumber::VerSine()
{
    return new RealNumber(1.0 - cos(x), true);
}

/**
 * @brief Versed cosine function for real numbers.
 *
 * See implementation of cosine in cos(double)
 */
Number* RealNumber::VerCosine()
{
    return new RealNumber(1.0 + cos(x), true);
}

/**
 * @brief Coversed sine function for real numbers.
 *
 * See implementation of sine in sin(double)
 */
Number* RealNumber::CoVerSine()
{
    return new RealNumber(1.0 - sin(x), true);
}

/**
 * @brief Coversed cosine function for real numbers.
 *
 * See implementation of sine in sin(double)
 */
Number* RealNumber::CoVerCosine()
{
    return new RealNumber(1.0 + sin(x), true);
}

Number* RealNumber::HaVerSine()
{
    return new RealNumber((1.0 - cos(x)) / 2.0, true);
}

Number* RealNumber::HaVerCosine()
{
    return new RealNumber((1.0 + cos(x)) / 2.0, true);
}

Number* RealNumber::HaCoVerSine()
{
    return new RealNumber((1.0 - sin(x)) / 2.0, true);
}

Number* RealNumber::HaCoVerCosine()
{
    return new RealNumber((1.0 + sin(x)) / 2.0, true);
}

Number* RealNumber::ArcVerSine()
{
    if (x < 0.0 || x > 2.0)
        return new NonNumber(nnnan);

    return new RealNumber(aver(x));
}

Number* RealNumber::ArcVerCosine()
{
    return new RealNumber(acos(1.0 + x));
}

Number* RealNumber::ArcCoVerSine()
{
    if (x < 0.0 || x > 2.0)
        return new NonNumber(nnnan);

    return new RealNumber(acvs(x));
}

Number* RealNumber::ArcCoVerCosine()
{
    return new RealNumber(asin(1.0 + x));
}

Number* RealNumber::ArcHaVerSine()
{
    if (x < 0.0 || x > 1.0)
        return new NonNumber(nnnan);

    return new RealNumber(ahv(x));
}

Number* RealNumber::ArcHaVerCosine()
{
    return new RealNumber(ahvc(x));
}

Number* RealNumber::ArcHaCoVerSine()
{
    return new NonNumber(nnnimp);
}

Number* RealNumber::ArcHaCoVerCosine()
{
    return new NonNumber(nnnimp);
}

Number* RealNumber::ExSecant()
{
    return new RealNumber(1.0 / cos(x) - 1);
}

Number* RealNumber::ExCosecant()
{
    return new RealNumber(1.0 / sin(x) - 1);
}

Number* RealNumber::ArcExSecant()
{
    if (x > -2.0 && x < 0.0)
        return new NonNumber(nnnan);

    double a = x * x + 2 * x;
    double b = sqrt(a);
    return new RealNumber(atan(b));
}

Number* RealNumber::ArcExCosecant()
{
    return new RealNumber(asin(1.0 / (x + 1)));
}
