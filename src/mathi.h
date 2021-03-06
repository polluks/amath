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

#ifndef AMATH_LIB_COMPLEX_H
#define AMATH_LIB_COMPLEX_H

#if __GNUC__ > 6
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif

/**
 * @file    mathi.h
 * @brief   Complex numbers math library
 * @details Mostly as specified in [IEEE Std 1003.1, 2013 Edition]:
 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/complex.h.html
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef union
{
    double parts[2];
} complex;

double csgn(complex z);
double cabs(complex z);
double creal(complex z);
double cimag(complex z);
double cabs(complex z);
complex cpack(double x, double y);
complex cadd(complex a, complex z);
complex csub(complex a, complex z);
complex cmul(complex a, complex z);
complex cdiv(complex a, complex z);
complex cpow(complex x, complex z);
complex cceil(complex z);
complex cfloor(complex z);
complex ctrunc(complex z);
complex cround(complex z);
complex creci(complex z);
complex conj(complex z);
complex cexp(complex z);
complex csqrt(complex z);
complex ccbrt(complex z);
complex clog(complex z);
complex clogb(complex z);
complex clog10(complex z);
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
