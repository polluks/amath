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

#ifndef AMATH_LIB_REAL_H
#define AMATH_LIB_REAL_H

/**
 * @file    mathr.h
 * @brief   Real numbers math library
 * @details The library is based on fdlib by Sun Microsystems.
 * 
 * The original library can be downloaded at netlib.org:<BR>
 * http://www.netlib.org/fdlibm/
 *
 * or from mirror site hensa.ac.uk:<BR>
 * http://www.hensa.ac.uk/
 *
 * More info on double precision floating point at Wikipedia:<BR>
 * https://wikipedia.org/wiki/Double-precision_floating-point_format
 * @author  Carsten Sonne Larsen \<cs@innolan.net>
 */

#define PI         3.1415926535897932384626433832795028841971693994
#define EULERS     2.7182818284590452353602874713526624977572470937
#define INFP       0x7FF0000000000000ull
#define INFN       0xFFF0000000000000ull
#define NAN        0x7FFFFFFFFFFFFFFFull
#define sgn(x)     (x > 0 ? 1 : x < 0 ? -1 : 0)
#define abs(x)     (x > 0 ? x : -x)

#ifdef __cplusplus
extern "C" {
#endif

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
double sec(double x);
double csc(double x);
double cot(double x);
double exs(double x);
double exc(double x);
double crd(double x);
double acos(double x);
double asin(double x);
double atan(double x);
double asec(double x);
double acsc(double x);
double acot(double x);
double aexs(double x);
double aexc(double x);
double acrd(double x);

double cosh(double x);
double sinh(double x);
double tanh(double x);
double sech(double x);
double csch(double x);
double coth(double x);
double acosh(double x);
double asinh(double x);
double atanh(double x);
double asech(double x);
double acsch(double x);
double acoth(double x);

double ver(double x);
double vcs(double x);
double cvs(double x);
double cvc(double x);
double hv(double x);
double hvc(double x);
double hcv(double x);
double hcc(double x);
double aver(double x);
double avcs(double x);
double acvs(double x);
double acvc(double x);
double ahv(double x);
double ahvc(double x);
double ahcv(double x);
double ahcc(double x);

double pow(double x, double y);
double fmod(double x, double y);
double atan2(double y, double x);
double hypot(double x, double y);
double log2p(double x, double y);
double log1p(double x);
double expm1(double x);
double scalbn(double x, int n);
double copysign(double x, double y);
int rempio2(double x, double* y);
unsigned int log2i(unsigned int x);

#ifdef __cplusplus
}
#endif

#endif
