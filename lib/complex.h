/*-
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

#ifndef LIBAMATH_COMPLEX_H
#define LIBAMATH_COMPLEX_H

/**
 * @file  complex.h
 * @brief Functions in math library for handling complex numbers.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    double parts[2];
} complex;

/**
 * Mostly as specified in IEEE Std 1003.1, 2013 Edition
 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/complex.h.html
 *
 */
double  csgn(complex z);
double  cabs(complex z);
double  creal(complex z);
double  cimag(complex z);
double  cabs(complex z);
double  carg(complex z);
complex cexp(complex z);
complex clog(complex z);
complex conj(complex z);
complex cproj(complex z);
complex csqrt(complex z);
complex cpow(complex x, complex z);
complex cpack(double x, double y);

/* Internal functions */
complex cadd(complex a, complex z);
complex csub(complex a, complex z);
complex cmul(complex a, complex z);
complex cdiv(complex a, complex z);

/* Standard math functions */
complex cceil(complex z);
complex cfloor(complex z);
complex ctrunc(complex z);
complex cround(complex z);
complex creci(complex z);
complex ccbrt(complex z);
complex clogb(complex z);
complex clog10(complex z);

/* Trigonometric functions */
complex ccos(complex z);
complex csin(complex z);
complex ctan(complex z);
complex csec(complex z);
complex ccsc(complex z);
complex ccot(complex z);
complex cacos(complex z);
complex casin(complex z);
complex catan(complex z);
complex casec(complex z);
complex cacsc(complex z);
complex cacot(complex z);

/* Hyperbolic functions */
complex ccosh(complex z);
complex csinh(complex z);
complex ctanh(complex z);
complex csech(complex z);
complex ccsch(complex z);
complex ccoth(complex z);
complex cacosh(complex z);
complex casinh(complex z);
complex catanh(complex z);
complex casech(complex z);
complex cacsch(complex z);
complex cacoth(complex z);

#ifdef __cplusplus
}
#endif

#endif










