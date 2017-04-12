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

#include "mathr.h"
#include "mathi.h"
#include "real.h"
#include "cplex.h"
#include "nnumb.h"

ComplexNumber::ComplexNumber() : Number(nsyscomplex)
{
    z = cpack(0.0, 0.0);
}

ComplexNumber::ComplexNumber(complex z) : Number(nsyscomplex)
{
    this->z = z;
}

ComplexNumber::ComplexNumber(double real, double imag) : Number(nsyscomplex)
{
    z = cpack(real, imag);
}

ComplexNumber::~ComplexNumber()
{
}

Number *ComplexNumber::Clone()
{
    return new ComplexNumber(z);
}

int ComplexNumber::GetIntegerValue()
{
    return static_cast<int>(creal(z));
}

double ComplexNumber::GetRealValue()
{
    return creal(z);
}

double ComplexNumber::GetImagValue() const
{
    return cimag(z);
}

complex ComplexNumber::GetComplexValue() const
{
    return z;
}

bool ComplexNumber::PureComplexValue()
{
    return (creal(z) == 0.0);
}

int ComplexNumber::GetPrecedence()
{
    if ((creal(z) < 0.0) || (creal(z) == 0.0 && cimag(z) < 0.0))
    {
        return -1;
    }
    else if (creal(z) != 0.0 && cimag(z) != 0.0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int ComplexNumber::GetDefaultPrecedence()
{
    return (creal(z) != 0.0 && cimag(z) != 0.0) ? 2 : 0;
}

bool ComplexNumber::IsNegative()
{
    FloatUnion64 d, e;
    d.floatingPoint = creal(z);
    e.floatingPoint = cimag(z);
    return d.IsNegative() && e.IsNegative();
}

bool ComplexNumber::IsZero()
{
    FloatUnion64 d, e;
    d.floatingPoint = creal(z);
    e.floatingPoint = cimag(z);
    return d.IsZero() && e.IsZero();
}

/**
 * @brief Returns true if number is NaN
 */
bool ComplexNumber::IsNaN()
{
    FloatUnion64 d, e;
    d.floatingPoint = creal(z);
    e.floatingPoint = cimag(z);
    return d.IsNaN() || e.IsNaN();
}

/**
 * @brief Returns true if number is infinite
 */
bool ComplexNumber::IsInfinite()
{
    double a = creal(z);
    double b = cimag(z);

    // Handle subnormal values
    bool subInf = 
        (a > 0 && a <= 1e-308) || (a < 0 && a >= -1e-308) ||
        (b > 0 && b <= 1e-308) || (b < 0 && b >= -1e-308);

    if (subInf)
    {
        return true;
    }

    FloatUnion64 d, e;
    d.floatingPoint = a;
    e.floatingPoint = b;
    return d.IsInf() || e.IsInf() ||
           d.IsMaxPositive() || d.IsMaxNegative() ||
           e.IsMaxPositive() || e.IsMaxNegative();
}

bool ComplexNumber::IsNotImplemented()
{
    return false;
}

Number *ComplexNumber::Unary()
{
    complex w = cpack(-creal(z), -cimag(z));
    return new ComplexNumber(w);
}

Number *ComplexNumber::Add(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsyscomplex)
    {
        ComplexNumber *w = static_cast<ComplexNumber *>(other);
        return new ComplexNumber(cadd(z, w->z));
    }

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new ComplexNumber(cadd(z, cpack(a->x, 0.0)));
    }

    return new ComplexNumber();
}

Number *ComplexNumber::Sub(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsyscomplex)
    {
        ComplexNumber *w = static_cast<ComplexNumber *>(other);
        return new ComplexNumber(csub(z, w->z));
    }

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new ComplexNumber(csub(z, cpack(a->x, 0.0)));
    }

    return new ComplexNumber();
}

Number *ComplexNumber::Mul(Number *other)
{
    if (other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsyscomplex)
    {
        ComplexNumber *w = static_cast<ComplexNumber *>(other);
        return new ComplexNumber(cmul(z, w->z));
    }

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new ComplexNumber(cmul(z, cpack(a->x, 0.0)));
    }

    return new ComplexNumber();
}

Number *ComplexNumber::Div(Number *other)
{
    if (other->IsZero() || other->IsNaN())
        return new NonNumber(nnnan);

    if (other->system == nsyscomplex)
    {
        ComplexNumber *w = static_cast<ComplexNumber *>(other);
        return new ComplexNumber(cdiv(z, w->z));
    }

    if (other->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(other);
        return new ComplexNumber(cdiv(z, cpack(a->x, 0.0)));
    }

    return new ComplexNumber();
}

Number *ComplexNumber::Raise(Number *exponent)
{
    if (exponent->IsNaN())
        return new NonNumber(nnnan);

    if (exponent->system == nsyscomplex)
    {
        ComplexNumber *w = static_cast<ComplexNumber *>(exponent);
        return new ComplexNumber(cpow(z, w->z));
    }

    if (exponent->system == nsysreal)
    {
        RealNumber *a = static_cast<RealNumber *>(exponent);
        return new ComplexNumber(cpow(z, cpack(a->x, 0.0)));
    }

    return new ComplexNumber();
}

Number *ComplexNumber::Factorial()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::Signum()
{
    return new RealNumber(csgn(z));
}

Number *ComplexNumber::Absolute()
{
    return new RealNumber(cabs(z));
}

Number *ComplexNumber::Trunc()
{
    return new ComplexNumber(ctrunc(z));
}

Number *ComplexNumber::Round()
{
    return new ComplexNumber(cround(z));
}

Number *ComplexNumber::Floor()
{
    return new ComplexNumber(cfloor(z));
}

Number *ComplexNumber::Ceiling()
{
    return new ComplexNumber(cceil(z));
}

Number *ComplexNumber::SquareRoot()
{
    return new ComplexNumber(csqrt(z));
}

Number *ComplexNumber::Reciprocal()
{
    return new ComplexNumber(creci(z));
}

Number *ComplexNumber::CubeRoot()
{
    return new ComplexNumber(ccbrt(z));
}

Number *ComplexNumber::Log()
{
    if (creal(z) == 0.0 && cimag(z) == 0.0)
        return new NonNumber(nnnan);

    return new ComplexNumber(clog(z));
}

Number *ComplexNumber::Log2()
{
    if (creal(z) == 0.0 && cimag(z) == 0.0)
        return new NonNumber(nnnan);

    return new ComplexNumber(clogb(z));
}

Number *ComplexNumber::Log10()
{
    if (creal(z) == 0.0 && cimag(z) == 0.0)
        return new NonNumber(nnnan);

    return new ComplexNumber(clog10(z));
}

Number *ComplexNumber::Sine()
{
    return new ComplexNumber(csin(z));
}

Number *ComplexNumber::Cosine()
{
    return new ComplexNumber(ccos(z));
}

Number *ComplexNumber::Tangent()
{
    return new ComplexNumber(ctan(z));
}

Number *ComplexNumber::Secant()
{
    return new ComplexNumber(csec(z));
}

Number *ComplexNumber::Cosecant()
{
    return new ComplexNumber(ccsc(z));
}

Number *ComplexNumber::Cotangent()
{
    return new ComplexNumber(ccot(z));
}

Number *ComplexNumber::Chord()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ExSecant()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ExCosecant()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcSine()
{
    return new ComplexNumber(casin(z));
}

Number *ComplexNumber::ArcCosine()
{
    return new ComplexNumber(cacos(z));
}

Number *ComplexNumber::ArcTangent()
{
    return new ComplexNumber(catan(z));
}

Number *ComplexNumber::ArcSecant()
{
    return new ComplexNumber(casec(z));
}

Number *ComplexNumber::ArcCosecant()
{
    return new ComplexNumber(cacsc(z));
}

Number *ComplexNumber::ArcCotangent()
{
    return new ComplexNumber(cacot(z));
}

Number *ComplexNumber::ArcChord()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcExSecant()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcExCosecant()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::HypSine()
{
    return new ComplexNumber(csinh(z));
}

Number *ComplexNumber::HypCosine()
{
    return new ComplexNumber(ccosh(z));
}

Number *ComplexNumber::HypTangent()
{
    return new ComplexNumber(ctanh(z));
}

Number *ComplexNumber::HypSecant()
{
    return new ComplexNumber(csech(z));
}

Number *ComplexNumber::HypCosecant()
{
    return new ComplexNumber(ccsch(z));
}

Number *ComplexNumber::HypCotangent()
{
    return new ComplexNumber(ccoth(z));
}

Number *ComplexNumber::HypArcSine()
{
    return new ComplexNumber(casinh(z));
}

Number *ComplexNumber::HypArcCosine()
{
    return new ComplexNumber(cacosh(z));
}

Number *ComplexNumber::HypArcTangent()
{
    return new ComplexNumber(catanh(z));
}

Number *ComplexNumber::HypArcSecant()
{
    return new ComplexNumber(casech(z));
}

Number *ComplexNumber::HypArcCosecant()
{
    return new ComplexNumber(cacsch(z));
}

Number *ComplexNumber::HypArcCotangent()
{
    return new ComplexNumber(cacoth(z));
}

Number *ComplexNumber::VerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::VerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::CoVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::CoVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::HaVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::HaVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::HaCoVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::HaCoVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcCoVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcCoVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcHaVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcHaVerCosine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcHaCoVerSine()
{
    return new NonNumber(nnnimp);
}

Number *ComplexNumber::ArcHaCoVerCosine()
{
    return new NonNumber(nnnimp);
}
