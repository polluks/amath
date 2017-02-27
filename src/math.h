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

#ifndef AMATH_LIB_MATH_H
#define AMATH_LIB_MATH_H

/**
 * @file    math.h
 * @brief   Functions in math library for handling real numbers.
 * @details The library is based on fdlib by Sun Microsystems.
 * 
 * The original library can be downloaded at [netlib.org]:
 * http://www.netlib.org/fdlibm/
 *
 * or from mirror site [hensa.ac.uk]:
 * http://www.hensa.ac.uk/
 *
 * All headers and dates are preserved.
 *
 * More info on double precision floating point at [Wikipedia]:
 * https://wikipedia.org/wiki/Double-precision_floating-point_format
 */

#define PI         3.14159265358979323846
#define EULERS     2.71828182845904523536
#define LOG2       0.69314718055994530942
#define sgn(x)     (x > 0.0 ? 1.0 : x < 0.0 ? -1.0 : 0.0)
#define isgn(x)    (x > 0 ? 1 : x < 0 ? -1 : 0)
#define log2p(x,y) (y != 1.0 ? log(y)/log(x) : 0.0)
#define abs(x)     (x > 0 ? x : -x)

#define D_INFN      1.0e-308
#define D_INFP      1.0e+308

#ifdef __cplusplus
extern "C" {
#endif

int isnan(double x);
int finite(double x);

double fabs(double x);
double ceil(double x);
double floor(double x);
double round(double x);
double trunc(double x);
double exp(double x);
double sqrt(double x);
double cbrt(double x);
double log(double x);
double log10(double x);

double cos(double x);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double acosh(double x);
double asinh(double x);
double atanh(double x);

double aver(double x);
double acvs(double x);
double ahv(double x);
double ahvc(double x);

double pow(double x, double y);
double fmod(double x, double y);
double atan2(double y, double x);
double hypot(double x, double y);
double log1p(double x);
double expm1(double x);
double scalbn(double x, int n);
double copysign(double x, double y);
int rempio2(double x, double* y);

#ifdef __cplusplus
}
#endif

#endif
