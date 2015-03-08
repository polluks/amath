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

#ifndef _COMPLEX_PRIMITIVES_H
#define _COMPLEX_PRIMITIVES_H

/**
 * @file  cprim.h
 * @brief Primitives in math library for handling complex numbers.
 *
 */

#include "libm/rprim.h"
#include "libm/rfunc.h"

#define REAL_PART(z) ((z).parts[0])
#define IMAG_PART(z) ((z).parts[1])

typedef union {
    double parts[2];
} complex;

/**
 * @brief Real part of complex number.
 *
 */
static inline double
creal(complex z)
{
    return (REAL_PART(z));
}

/**
 * @brief Imaginary part of complex number.
 *
 */
static inline double
cimag(complex z)
{
    return (IMAG_PART(z));
}

/**
 * @brief Absolute value of complex number.
 *
 */
static inline double
abs(complex z)
{
    return hypot(creal(z), cimag(z));
}

static inline double
conj(complex z)
{
    IMAG_PART(z) = -IMAG_PART(z);
    return (IMAG_PART(z));
}

/**
 * @brief Pack two real numbers into a complex number.
 *
 */
static inline complex
cpack(double x, double y)
{
    complex z;

    REAL_PART(z) = x;
    IMAG_PART(z) = y;
    return (z);
}

/**
 * @brief Signum value of complex number.
 *
 */
static inline complex
csgn(complex z)
{
    complex w;
    w = cpack(sgn(creal(z)), sgn(cimag(z)));
    return w;
}

/**
 * @brief Truncated value of complex number.
 *
 */
static inline complex
ctrunc(complex z)
{
    complex w;
    w = cpack(trunc(creal(z)), trunc(cimag(z)));
    return w;
}

/**
 * @brief Floor value of complex number.
 *
 */
static inline complex
cfloor(complex z)
{
    complex w;
    w = cpack(floor(creal(z)), floor(cimag(z)));
    return w;
}

/**
 * @brief Ceiling value of complex number.
 *
 */
static inline complex
cceil(complex z)
{
    complex w;
    w = cpack(ceil(creal(z)), ceil(cimag(z)));
    return w;
}

/**
 * @brief Division of two complex numbers.
 *
 */
static inline complex
cround(complex z)
{
    complex w;
    w = cpack(round(creal(z)), round(cimag(z)));
    return w;
}

/**
 * @brief Addition of two complex numbers.
 *
 */
static inline complex
cadd(complex y, complex z)
{
    complex w;
    w = cpack(creal(y) + creal(z), cimag(y) + cimag(z));
    return w;
}

/**
 * @brief Subtraction of two complex numbers.
 *
 */
static inline complex
csub(complex y, complex z)
{
    complex w;
    w = cpack(creal(y) - creal(z), cimag(y) - cimag(z));
    return w;
}

/**
 * @brief Multiplication of two complex numbers.
 *
 */
static inline complex
cmul(complex y, complex z)
{
    complex w;
    double a, b, c, d;

    // (a+bi)(c+di)
    a = creal(y);
    b = cimag(y);
    c = creal(z);
    d = cimag(z);

    // (ac -bd) + (ad + bc)i
    w = cpack(a * c - b * d, a * d + b * c);
    return w;
}

/**
 * @brief Division of two complex numbers.
 *
 */
static inline complex
cdiv(complex y, complex z)
{
    complex w;
    double a, b, c, d;
    double q, v, x;

    a = creal(y);
    b = cimag(y);
    c = creal(z);
    d = cimag(z);

    q = c * c + d * d;
    v = a * c + b * d;
    x = b * c - a * d;

    w = cpack(v / q, x / q);
    return w;
}

/**
 * @brief Reciprocal value of complex number.
 *
 */
static inline complex
creci(complex z)
{
    complex w;
    double q, a, b;

    a = creal(z);
    b = conj(z);
    q = a * a + b * b;
    w = cpack(a / q, b / q);

    return w;
}

/**
 * @brief Calculate cosh and sinh
 *
 */
static inline void
cchsh(double x, double *c, double *s)
{
    double e, ei;

    if (fabs(x) <= 0.5) {
        *c = cosh(x);
        *s = sinh(x);
    } else {
        e = exp(x);
        ei = 0.5 / e;
        e = 0.5 * e;
        *s = e - ei;
        *c = e + ei;
    }
}

/**
 * @brief Calculate cosh and cos
 *
 */
static inline void
cchc(double x, double *ch, double *c)
{
    *ch = cosh(2.0 * x);
    *c = cos(2.0 * x);
}

#endif
