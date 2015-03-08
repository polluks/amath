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

#ifndef _REAL_FUNCTIONS_H
#define _REAL_FUNCTIONS_H

/**
 * @file  rfunc.h
 * @brief Functions in math library for handling real numbers.
 *
 * The library is based on fdlib by Sun Microsystems.
 * The original library can be downloaded at:
 * http://www.netlib.org/fdlibm/
 *
 * or from mirros site:
 * http://www.hensa.ac.uk/
 *
 * All headers and dates are preserved.
 *
 */

#ifdef NATIVEMATH
#include <math.h>
#endif

extern int finite(double x);

extern double floor(double x);
extern double ceil(double x);
extern double exp(double x);
extern double sqrt(double x);
extern double cbrt(double x);
extern double log(double x);
extern double log10(double x);

extern double cos(double x);
extern double sin(double x);
extern double tan(double x);
extern double acos(double x);
extern double asin(double x);
extern double atan(double x);
extern double cosh(double x);
extern double sinh(double x);
extern double tanh(double x);
extern double acosh(double x);
extern double asinh(double x);
extern double atanh(double x);

extern double pow(double x, double y);
extern double fmod(double x, double y);
extern double atan2(double y, double x);
extern double hypot(double x, double y);
extern double log1p(double x);
extern double expm1(double x);
extern double scalbn (double x, int n);
extern int rempio2(double x, double *y);
extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, int iy);
extern double __kernel_tan(double x, double y, int iy);
extern int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2);

#endif
