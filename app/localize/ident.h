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
 * Generated with FlexCat. For more information, see:
 * http://sourceforge.net/projects/flexcat/
 *
 */

#ifndef AMATH_LOCALIZE_IDENT_HELP_H
#define AMATH_LOCALIZE_IDENT_HELP_H

/**
 * @file  ident.h
 * @brief Localized help text definitions.
 *
 */

#include "clib.h"

struct identhelpdef {
    int id;
    const char *ident;
    const char *text;
};

static const identhelpdef identtexts[] = {
    { 0, "abs", "The absolute value (or modulus) |x| of a real number x is the#NEWLINE#non-negative value of x without regard to its sign.#NEWLINE##SYNTAXHIGHLIGHT#Example: abs(-237.25)#NORMALTEXT##NEWLINE#" },
    { 1, "sgn", "The sign function or signum function is used to extract the sign of a number.#NEWLINE#Thus sgn(x) is 1 when x is positive, and sgn(x) is -1 when x is negative.#NEWLINE##SYNTAXHIGHLIGHT#Example: sgn(-23.94)#NORMALTEXT##NEWLINE#" },
    { 2, "round", "Rounding a numerical value means replacing it by another value that is#NEWLINE#approximately equal but has a shorter, simpler, or more explicit#NEWLINE#representation. Amath rounds a number to the nearest integer.#NEWLINE#" },
    { 3, "trunc", "Truncation is limiting the number of digits right of the decimal point,#NEWLINE#by discarding the least significant ones. Amath truncates a number to#NEWLINE#the nearest integer.#NEWLINE##SYNTAXHIGHLIGHT#Example: trunc(-23.94#NEWLINE#" },
    { 4, "floor", "No help is available for this function.#NEWLINE#" },
    { 5, "ceil", "No help is available for this function.#NEWLINE#" },
    { 6, "sqr", "No help is available for this function.#NEWLINE#" },
    { 7, "sqrt", "No help is available for this function.#NEWLINE#" },
    { 8, "cbr", "No help is available for this function.#NEWLINE#" },
    { 9, "cbrt", "No help is available for this function.#NEWLINE#" },
    { 10, "lb", "No help is available for this function.#NEWLINE#" },
    { 11, "log2", "No help is available for this function.#NEWLINE#" },
    { 12, "ln", "No help is available for this function.#NEWLINE#" },
    { 13, "lg", "No help is available for this function.#NEWLINE#" },
    { 14, "log", "No help is available for this function.#NEWLINE#" },
    { 15, "log10", "No help is available for this function.#NEWLINE#" },
    { 16, "sin", "Sine is the trigonometric function that for an acute angle is the#NEWLINE#ratio between the leg opposite the angle when it is considered#NEWLINE#part of a right triangle and the hypotenuse.#NEWLINE#" },
    { 17, "cos", "Cosine is the trigonometric function that for an acute angle is the#NEWLINE#ratio between the leg adjacent to the angle when it is considered#NEWLINE#part of a right triangle and the hypotenuse#NEWLINE#" },
    { 18, "tan", "Tangent is one of the trigonometry functions. In a right triangle,#NEWLINE#the tangent of an angle is the opposite side over the adjacent side.#NEWLINE#" },
    { 19, "cot", "No help is available for this function.#NEWLINE#" },
    { 20, "sec", "No help is available for this function.#NEWLINE#" },
    { 21, "csc", "No help is available for this function.#NEWLINE#" },
    { 22, "asin", "No help is available for this function.#NEWLINE#" },
    { 23, "acos", "No help is available for this function.#NEWLINE#" },
    { 24, "atan", "No help is available for this function.#NEWLINE#" },
    { 25, "acot", "No help is available for this function.#NEWLINE#" },
    { 26, "asec", "No help is available for this function.#NEWLINE#" },
    { 27, "acsc", "No help is available for this function.#NEWLINE#" },
    { 28, "arsin", "No help is available for this function.#NEWLINE#" },
    { 29, "arcos", "No help is available for this function.#NEWLINE#" },
    { 30, "artan", "No help is available for this function.#NEWLINE#" },
    { 31, "arcot", "No help is available for this function.#NEWLINE#" },
    { 32, "arsec", "No help is available for this function.#NEWLINE#" },
    { 33, "arcsc", "No help is available for this function.#NEWLINE#" },
    { 34, "arcsin", "No help is available for this function.#NEWLINE#" },
    { 35, "arccos", "No help is available for this function.#NEWLINE#" },
    { 36, "arctan", "No help is available for this function.#NEWLINE#" },
    { 37, "arccot", "No help is available for this function.#NEWLINE#" },
    { 38, "arcsec", "No help is available for this function.#NEWLINE#" },
    { 39, "arccsc", "No help is available for this function.#NEWLINE#" },
    { 40, "sinh", "No help is available for this function.#NEWLINE#" },
    { 41, "cosh", "No help is available for this function.#NEWLINE#" },
    { 42, "tanh", "No help is available for this function.#NEWLINE#" },
    { 43, "coth", "No help is available for this function.#NEWLINE#" },
    { 44, "sech", "No help is available for this function.#NEWLINE#" },
    { 45, "csch", "No help is available for this function.#NEWLINE#" },
    { 46, "asinh", "No help is available for this function.#NEWLINE#" },
    { 47, "acosh", "No help is available for this function.#NEWLINE#" },
    { 48, "atanh", "No help is available for this function.#NEWLINE#" },
    { 49, "acoth", "No help is available for this function.#NEWLINE#" },
    { 50, "asech", "No help is available for this function.#NEWLINE#" },
    { 51, "acsch", "No help is available for this function.#NEWLINE#" },
    { 52, "arsinh", "No help is available for this function.#NEWLINE#" },
    { 53, "arcosh", "No help is available for this function.#NEWLINE#" },
    { 54, "artanh", "No help is available for this function.#NEWLINE#" },
    { 55, "arcoth", "No help is available for this function.#NEWLINE#" },
    { 56, "arsech", "No help is available for this function.#NEWLINE#" },
    { 57, "arcsch", "No help is available for this function.#NEWLINE#" },
    { 58, "arcsinh", "No help is available for this function.#NEWLINE#" },
    { 59, "arccosh", "No help is available for this function.#NEWLINE#" },
    { 60, "arctanh", "No help is available for this function.#NEWLINE#" },
    { 61, "arccoth", "No help is available for this function.#NEWLINE#" },
    { 62, "arcsech", "No help is available for this function.#NEWLINE#" },
    { 63, "arccsch", "No help is available for this function.#NEWLINE#" },
    { -1, EMPTYSTRING, EMPTYSTRING }
};

#endif
