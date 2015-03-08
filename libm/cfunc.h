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

#ifndef _COMPLEX_FUNCTIONS_H
#define _COMPLEX_FUNCTIONS_H

/**
 * @file  cfunc.h
 * @brief Functions in math library for handling complex numbers.
 *
 */

#include "libm/cprim.h"

extern complex cadd(complex a, complex z);
extern complex csub(complex a, complex z);
extern complex cmul(complex a, complex z);
extern complex cdiv(complex a, complex z);
extern complex cpow(complex a, complex z);

extern complex csgn(complex z);
extern complex ctrunc(complex z);
extern complex cfloor(complex z);
extern complex cceil(complex z);
extern complex cround(complex z);
extern complex creci(complex z);
extern complex csqrt(complex z);
extern complex ccbrt(complex z);
extern complex cexp(complex z);
extern complex clog(complex z);
extern complex clogb(complex z);
extern complex clog10(complex z);

extern complex ccos(complex z);
extern complex csin(complex z);
extern complex ctan(complex z);
extern complex csec(complex z);
extern complex ccsc(complex z);
extern complex ccot(complex z);
extern complex cacos(complex z);
extern complex casin(complex z);
extern complex catan(complex z);
extern complex casec(complex z);
extern complex cacsc(complex z);
extern complex cacot(complex z);

extern complex ccosh(complex z);
extern complex csinh(complex z);
extern complex ctanh(complex z);
extern complex csech(complex z);
extern complex ccsch(complex z);
extern complex ccoth(complex z);
extern complex cacosh(complex z);
extern complex casinh(complex z);
extern complex catanh(complex z);
extern complex casech(complex z);
extern complex cacsch(complex z);
extern complex cacoth(complex z);

extern void cchsh(double x, double *c, double *s);
extern double redupi(double x);
extern double ctans(complex z);

#endif
