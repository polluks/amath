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

#ifndef _REAL_PRIMITIVES_H
#define _REAL_PRIMITIVES_H

// ---------------------------------------------------------------------------
// ------------------------- High precision constants ------------------------
// ---------------------------------------------------------------------------

#define PI         3.141592653589793238462643383279
#define EULERS     2.718281828459045235360287471352

/**
 * @file  rprim.h
 * @brief Primitives in math library for handling real numbers.
 *
 * The library is based on fdlib by Sun Microsystems.
 * The original library can be downloaded at:
 * http://www.netlib.org/fdlibm/<BR>
 *
 * or from mirros site:<BR>
 * http://www.hensa.ac.uk/
 *
 * All headers and dates are preserved.
 *
 */

/**
 * @brief 32 bit unsigned integer.
 *
 */
typedef unsigned int uword;

/**
 * @brief 32 bit signed integer.
 *
 */
typedef int sword;

// ---------------------------------------------------------------------------
// ------------------ Define endianness for IEEE arithmetic ------------------
// ---------------------------------------------------------------------------

#ifdef AOS
#define __IEEE_BIG_ENDIAN
#endif

// Needed by math library
#if defined(INTELCPU) || defined(i386) || defined(i486) || \
    defined(intel) || defined(x86) || defined(i86pc) || \
    defined(__alpha) || defined(__osf__)

// AROS
#ifdef __IEEE_BIG_ENDIAN
#undef __IEEE_BIG_ENDIAN
#endif

#define __IEEE_LITTLE_ENDIAN
#endif


#ifndef __IEEE_BIG_ENDIAN
#ifndef __IEEE_LITTLE_ENDIAN
#error Must define endianness  
#endif
#endif

// ---------------------------------------------------------------------------
// -------------- Endianness implementation for IEEE arithmetic --------------
// ---------------------------------------------------------------------------

#ifdef __IEEE_BIG_ENDIAN
/**
 * @brief A union which permits us to convert between a double and two 32 bit ints.
 *
 * Big endian version.
 *
 */
typedef union
{
    double value;
    struct
    {
        uword msw;
        uword lsw;
    } parts;
} ieee_double_shape_type;
#endif

#ifdef __IEEE_LITTLE_ENDIAN
/**
 * @brief A union which permits us to convert between a double and two 32 bit ints.
 *
 * Little endian version.
 *
 */
typedef union
{
    double value;
    struct
    {
        uword lsw;
        uword msw;
    } parts;
} ieee_double_shape_type;
#endif

// ---------------------------------------------------------------------------
// ---------- Endianness implementation for 64 bit IEEE arithmetic -----------
// ---------------------------------------------------------------------------

/**
 * @brief Get two 32 bit ints from a double.
 *
 */
#define EXTRACT_WORDS(ix0,ix1,d)   \
  do {                             \
    ieee_double_shape_type ew_u;   \
    ew_u.value = (d);              \
    (ix0) = ew_u.parts.msw;        \
    (ix1) = ew_u.parts.lsw;        \
  } while (0)

/**
 * @brief Get the more significant 32 bit int from a double.
 *
 */
#define GET_HIGH_WORD(i,d)         \
  do {                             \
    ieee_double_shape_type gh_u;   \
    gh_u.value = (d);              \
    (i) = gh_u.parts.msw;          \
  } while (0)

/**
 * @brief Get the less significant 32 bit int from a double.
 *
 */
#define GET_LOW_WORD(i,d)          \
  do {                             \
    ieee_double_shape_type gl_u;   \
    gl_u.value = (d);              \
    (i) = gl_u.parts.lsw;          \
  } while (0)

/**
 * @brief Set a double from two 32 bit ints.
 *
 */
#define INSERT_WORDS(d,ix0,ix1)    \
  do {                             \
    ieee_double_shape_type iw_u;   \
    iw_u.parts.msw = (ix0);        \
    iw_u.parts.lsw = (ix1);        \
    (d) = iw_u.value;              \
  } while (0)

/**
 * @brief Set the more significant 32 bits of a double from an int.
 *
 */
#define SET_HIGH_WORD(d,v)         \
  do {                             \
    ieee_double_shape_type sh_u;   \
    sh_u.value = (d);              \
    sh_u.parts.msw = (v);          \
    (d) = sh_u.value;              \
  } while (0)

/**
 * @brief Set the less significant 32 bits of a double from an int.
 *
 */
#define SET_LOW_WORD(d,v)          \
  do {                             \
    ieee_double_shape_type sl_u;   \
    sl_u.value = (d);              \
    sl_u.parts.lsw = (v);          \
    (d) = sl_u.value;              \
  } while (0)

// ---------------------------------------------------------------------------
// ---------- Endianness implementation for 32 bit IEEE arithmetic -----------
// ---------------------------------------------------------------------------

/**
 * @brief A union which permits us to convert between a float and a 32 bit int.
 *
 */
typedef union
{
    float value;
    uword word;
} ieee_float_shape_type;

/**
 * @brief Get a 32 bit int from a float.
 *
 */
#define GET_FLOAT_WORD(i,d)        \
do {                               \
  ieee_float_shape_type gf_u;      \
  gf_u.value = (d);                \
  (i) = gf_u.word;                 \
} while (0)

/**
 * @brief Set a float from a 32 bit int.
 *
 */
#define SET_FLOAT_WORD(d,i)        \
do {                               \
  ieee_float_shape_type sf_u;      \
  sf_u.word = (i);                 \
  (d) = sf_u.value;                \
} while (0)

// ---------------------------------------------------------------------------
// --------------- Define inline functions for IEEE arithmetic ---------------
// ---------------------------------------------------------------------------

#ifndef NATIVEMATH

#define HUGE       1.7976931348623157e+308

/**
 * @brief Not a number.
 *
 * isnan(x) returns 1 is x is nan, else 0.
 * NOTICE: No branching!
 *
 */
static inline int
isnan(double x)
{
    return ((x) != (x));
}

/**
 * @brief Returns a value with the magnitude of x and
 *        with the sign bit of y.
 *
 */
static inline double
copysign(double x, double y)
{
    uword hx, hy;
    GET_HIGH_WORD(hx, x);
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(x, (hx&0x7fffffff)|(hy&0x80000000));
    return x;
}

/**
 * @brief Returns the absolute value of x.
 *
 */
static inline double
fabs(double x)
{
    uword hx;
    GET_HIGH_WORD(hx,x);
    SET_HIGH_WORD(x, hx & 0x7fffffff);
    return x;
}

double ceil(double x);
double floor(double x);
double log(double x);

#else
#include <math.h>
#endif

double sgn(double x)
{
    return x > 0.0 ? 1.0 : x < 0.0 ? -1.0 : 0.0;
}

double trunc(double x)
{
    return x > 0.0 ? floor(x) : ceil(x);
}
#endif

double round(double x)
{
    return x > 0.0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#endif

double log(double y, double x)
{
    return log(x)/log(y);
}

// ---------------------------------------------------------------------------
// ------------------- End of real primitive definitions ---------------------
// ---------------------------------------------------------------------------

#endif
