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
#include "numb.h"
#include "real.h"
#include "cplex.h"
#include "nnumb.h"
#include "integer.h"

IntegerNumber::IntegerNumber() :
    Number(nsysinteger)
{
    i = 0;
}

IntegerNumber::IntegerNumber(signed int i) :
    Number(nsysinteger)
{
    this->i = i;
}

IntegerNumber::IntegerNumber(unsigned int i) :
    Number(nsysinteger)
{
    this->i = i;
}

IntegerNumber::~IntegerNumber()
{
}

Number* IntegerNumber::Clone()
{
    return new IntegerNumber(i);
}

int IntegerNumber::GetIntegerValue()
{
    return i;
}

double IntegerNumber::GetRealValue()
{
    return static_cast<double>(i);
}

bool IntegerNumber::PureComplexValue()
{
    return false;
}

int IntegerNumber::GetPrecedence()
{
    return (i < 0) ? -1 : 0;
}

int IntegerNumber::GetDefaultPrecedence()
{
    return 0;
}

bool IntegerNumber::IsZero()
{
    return i == 0;
}

bool IntegerNumber::IsTooSmall()
{
    return false;
}

bool IntegerNumber::IsTooLarge()
{
    return false;
}

bool IntegerNumber::IsNaN()
{
    return false;
}

bool IntegerNumber::IsNotImplemented()
{
    return false;
}

Number* IntegerNumber::Unary()
{
    return new IntegerNumber(-i);
}

Number* IntegerNumber::Add(Number* other)
{
    if (other->IsNaN())
    {
        return new NonNumber(nnnan);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        if (a->i > MAX_INT_NUM / 2 || i > MAX_INT_NUM / 2)
            return new RealNumber(static_cast<double>(a->i) + static_cast<double>(i));

        return new IntegerNumber(i + a->i);
    }

    return other->Add(this);
}

Number* IntegerNumber::Sub(Number* other)
{
    if (other->IsNaN())
    {
        return new NonNumber(nnnan);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        if (a->i < -MAX_INT_NUM / 2 || i < -MAX_INT_NUM / 2)
            return new RealNumber(static_cast<double>(a->i) - static_cast<double>(i));

        return new IntegerNumber(i - a->i);
    }

    Number* y = other->Unary();
    Number* q = y->Add(this);
    delete y;
    return q;
}

Number* IntegerNumber::Mul(Number* other)
{
    if (other->IsNaN())
    {
        return new NonNumber(nnnan);
    }

    if (other->system == nsysinteger)
    {
        IntegerNumber* a = static_cast<IntegerNumber*>(other);
        double r = static_cast<double>(i) * static_cast<double>(a->i);
        if (r < static_cast<double>(MAX_INT_NUM))
            return new IntegerNumber(i * a->i);

        return new RealNumber(r);
    }

    return other->Mul(this);
}

Number* IntegerNumber::Div(Number* other)
{
    if (other->IsZero() || other->IsNaN())
        return new NonNumber(nnnan);

    Number* y = other->Reciprocal();
    Number* q = Mul(y);
    delete y;
    return q;
}

/**
 * @brief Exponentiation function.
 *
 * See implementation in pow(double, double)
 */
Number* IntegerNumber::Raise(Number* exponent)
{
    if (exponent->IsNaN())
    {
        return new NonNumber(nnnan);
    }

    if (exponent->system == nsysinteger)
    {
        return new RealNumber(pow(static_cast<double>(i), static_cast<IntegerNumber*>(exponent)->i));
    }

    if (exponent->system == nsysreal)
    {
        return new RealNumber(pow(static_cast<double>(i), static_cast<RealNumber*>(exponent)->GetRealValue()));
    }

    ComplexNumber* y = new ComplexNumber(i, 0.0);
    Number* q = y->Raise(exponent);
    delete y;
    return q;
}

/**
 * @brief Mathematical sign function.
 *
 */
Number* IntegerNumber::Signum()
{
    return new IntegerNumber(isgn(i));
}

/**
 * @brief Mathematical truncate function.
 *
 */
Number* IntegerNumber::Trunc()
{
    return new IntegerNumber(i);
}

/**
 * @brief Mathematical round function.
 *
 */
Number* IntegerNumber::Round()
{
    return new IntegerNumber(i);
}

/**
 * @brief Mathematical floor function.
 *
 */
Number* IntegerNumber::Floor()
{
    return new IntegerNumber(i);
}

/**
 * @brief Mathematical ceiling function.
 *
 */
Number* IntegerNumber::Ceiling()
{
    return new IntegerNumber(i);
}

/**
 * @brief Absolute value of number.
 *
 */
Number* IntegerNumber::Absolute()
{
    return new IntegerNumber(abs(i));
}

/**
 * @brief Square root function.
 *
 */
Number* IntegerNumber::SquareRoot()
{
    if (i == 0)
        return new IntegerNumber(0);

    if (i > 0)
        return new RealNumber(sqrt(static_cast<double>(i)));

    Number* n = new ComplexNumber(static_cast<double>(i), 0);
    Number* r = n->SquareRoot();
    delete n;
    return r;
}

/**
 * @brief Cube root function.
 *
 */
Number* IntegerNumber::CubeRoot()
{
    return new RealNumber(cbrt(static_cast<double>(i)));
}

/**
 * @brief Reciprocal function.
 *
 */
Number* IntegerNumber::Reciprocal()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / static_cast<double>(i));
}

/**
 * @brief Factorial function.
 *
 */
Number* IntegerNumber::Factorial()
{
    if (i < 0)
        return new NonNumber(nnnan);

    if (i == 0 || i == 1)
        return new IntegerNumber(1);

    int l = i > 1000 ? 1000 : i;
    double r = 1.0;

    for (int c = 1; c <= l; c++)
        r = r * c;

    if (r < static_cast<double>(MAX_INT_NUM))
        return new IntegerNumber(static_cast<int>(r));

    return new RealNumber(r);
}

/**
 * @brief Binary logarithm function (base 2).
 *
 * See implementation of natural logarithm in log(double)
 */
Number* IntegerNumber::Log2()
{
    if (i == 0)
        return new NonNumber(nnnan);

    if (i > 0)
        return new RealNumber(log(static_cast<double>(i)) / LOG2);

    Number* n = new ComplexNumber(static_cast<double>(i), 0);
    Number* r = n->Log2();
    delete n;
    return r;
}

/**
 * @brief Natural logarithm function (base e).
 *
 * See implementation of natural logarithm in log(double)
 */
Number* IntegerNumber::Log()
{
    if (i == 0)
        return new NonNumber(nnnan);

    if (i > 0)
        return new RealNumber(log(static_cast<double>(i)));

    Number* n = new ComplexNumber(static_cast<double>(i), 0);
    Number* r = n->Log();
    delete n;
    return r;
}

/**
 * @brief Base 10 logarithm function.
 *
 * See implementation of base 10 logarithm in log10(double)
 */
Number* IntegerNumber::Log10()
{

    if (i == 0)
        return new NonNumber(nnnan);

    if (i > 0)
        return new RealNumber(log10(static_cast<double>(i)));

    Number* n = new ComplexNumber(static_cast<double>(i), 0);
    Number* r = n->Log10();
    delete n;
    return r;
}

/**
 * @brief Trigonometric cosine function.
 *
 * See implementation of cosine function in cos(double)
 */
Number* IntegerNumber::Cosine()
{
    return new RealNumber(cos(static_cast<double>(i)), true);
}

/**
 * @brief Trigonometric secant function.
 *
 * See implementation of cosine function in cos(double)
 */
Number* IntegerNumber::Secant()
{
    double a = cos(static_cast<double>(i));

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Trigonometric tangent function.
 *
 * See implementation of tangent function in tan(double)
 */
Number* IntegerNumber::Tangent()
{
    return new RealNumber(tan(static_cast<double>(i)), true);
}

/**
 * @brief Trigonometric cotangent function.
 *
 * See implementation of tangent function in tan(double)
 */
Number* IntegerNumber::Cotangent()
{
    double a = tan(static_cast<double>(i));

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Hyperbolic sine function.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* IntegerNumber::HypSine()
{
    return new RealNumber(sinh(static_cast<double>(i)));
}

/**
 * @brief Hyperbolic cosecant function.
 *
 * See implementation of hyperbolic sine function in sinh(double)
 */
Number* IntegerNumber::HypCosecant()
{
    double a = sinh(static_cast<double>(i));

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Hyperbolic cosine function.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* IntegerNumber::HypCosine()
{
    return new RealNumber(cosh(static_cast<double>(i)));
}

/**
 * @brief Hyperbolic secant function.
 *
 * See implementation of hyperbolic cosine function in cosh(double)
 */
Number* IntegerNumber::HypSecant()
{
    return new RealNumber(1.0 / cosh(i));
}

/**
 * @brief Hyperbolic tangent function.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* IntegerNumber::HypTangent()
{
    return new RealNumber(tanh(static_cast<double>(i)));
}

/**
 * @brief Hyperbolic cotangent function.
 *
 * See implementation of hyperbolic tangent function in tanh(double)
 */
Number* IntegerNumber::HypCotangent()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / tanh(static_cast<double>(i)));
}

/**
 * @brief Trigonometric sine function.
 *
 * See implementation of sine function in sin(double)
 */
Number* IntegerNumber::Sine()
{
    return new RealNumber(sin(static_cast<double>(i)), true);
}

/**
 * @brief Trigonometric cosecant function.
 *
 * See implementation of sine function in sin(double)
 */
Number* IntegerNumber::Cosecant()
{
    double a = sin(static_cast<double>(i));

    if (a == 0.0)
        return new NonNumber(nnnan);

    return new RealNumber(1.0 / a);
}

/**
 * @brief Inverse trigonometric cosine function.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* IntegerNumber::ArcCosine()
{
    return new RealNumber(acos(static_cast<double>(i)));
}

/**
 * @brief Inverse trigonometric secant function.
 *
 * See implementation of inverse trigonometric cosine in acos(double)
 */
Number* IntegerNumber::ArcSecant()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(acos(1.0 / static_cast<double>(i)));
}

/**
 * @brief Inverse trigonometric tangent function.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* IntegerNumber::ArcTangent()
{
    return new RealNumber(atan(static_cast<double>(i)));
}

/**
 * @brief Inverse trigonometric cotangent function.
 *
 * See implementation of inverse trigonometric tangent in atan(double)
 */
Number* IntegerNumber::ArcCotangent()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(atan(1.0 / static_cast<double>(i)));
}

/**
 * @brief Inverse trigonometric sine function.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* IntegerNumber::ArcSine()
{
    return new RealNumber(asin(static_cast<double>(i)));
}

/**
 * @brief Inverse trigonometric cosecant function.
 *
 * See implementation of inverse trigonometric sine in asin(double)
 */
Number* IntegerNumber::ArcCosecant()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(asin(1.0 / static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic cosine function.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* IntegerNumber::HypArcCosine()
{
    return new RealNumber(acosh(static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic secant function.
 *
 * See implementation of inverse hyperbolic cosine in acosh(double)
 */
Number* IntegerNumber::HypArcSecant()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(acosh(1.0 / static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic sine function.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* IntegerNumber::HypArcSine()
{
    return new RealNumber(asinh(static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic cosecant function.
 *
 * See implementation of inverse hyperbolic sine in asinh(double)
 */
Number* IntegerNumber::HypArcCosecant()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(asinh(1.0 / static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic tangent function.
 *
 * See implementation hyperbolic tangent in atanh(double)
 */
Number* IntegerNumber::HypArcTangent()
{
    return new RealNumber(atanh(static_cast<double>(i)));
}

/**
 * @brief Inverse hyperbolic cotangent function.
 *
 * See implementation hyperbolic tangent in atanh(double)
 */
Number* IntegerNumber::HypArcCotangent()
{
    if (i == 0)
        return new NonNumber(nnnan);

    return new RealNumber(atanh(1.0 / static_cast<double>(i)));
}

Number* IntegerNumber::VerSine()
{
    return new RealNumber(1.0 - cos((double)i), true);
}

Number* IntegerNumber::VerCosine()
{
    return new RealNumber(1.0 + cos((double)i), true);
}

Number* IntegerNumber::CoVerSine()
{
    return new RealNumber(1.0 - sin((double)i), true);
}

Number* IntegerNumber::CoVerCosine()
{
    return new RealNumber(1.0 + sin((double)i), true);
}

Number* IntegerNumber::HaVerSine()
{
    return new RealNumber((1.0 - cos((double)i)) / 2.0, true);
}

Number* IntegerNumber::HaVerCosine()
{
    return new RealNumber((1.0 + cos((double)i)) / 2.0, true);
}

Number* IntegerNumber::HaCoVerSine()
{
    return new RealNumber((1.0 - sin((double)i)) / 2.0, true);
}

Number* IntegerNumber::HaCoVerCosine()
{
    return new RealNumber((1.0 + sin((double)i)) / 2.0, true);
}

Number* IntegerNumber::ArcVerSine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcVerSine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcVerCosine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcVerCosine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcCoVerSine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcCoVerSine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcCoVerCosine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcCoVerCosine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcHaVerSine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcHaVerSine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcHaVerCosine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcHaVerCosine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcHaCoVerSine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcHaCoVerSine();
    delete n;
    return x;
}

Number* IntegerNumber::ArcHaCoVerCosine()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcHaCoVerCosine();
    delete n;
    return x;
}

Number* IntegerNumber::ExSecant()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ExSecant();
    delete n;
    return x;
}

Number* IntegerNumber::ExCosecant()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ExCosecant();
    delete n;
    return x;
}

Number* IntegerNumber::ArcExSecant()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcExSecant();
    delete n;
    return x;
}

Number* IntegerNumber::ArcExCosecant()
{
    Number* n = new RealNumber(static_cast<double>(i));
    Number* x = n->ArcExCosecant();
    delete n;
    return x;
}
