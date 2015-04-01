/*-
 * Copyright (c) 2015 Carsten Larsen
 * All rights reserved.
 *
 * This code contains contributions to amath by Stefan Haubenthal
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

#ifndef LIBAMATH_REAL_PRIM_H
#define LIBAMATH_REAL_PRIM_H

/**
 * @file  prim.h
 * @brief Primitives in math library for handling real numbers.
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

// ---------------------------------------------------------------------------
// ------------------------- High precision constants ------------------------
// ---------------------------------------------------------------------------

#ifndef HUGE
#define HUGE       1.7976931348623157e+308
#endif

double __kernel_cos(double x, double y);
double __kernel_sin(double x, double y, int iy);
double __kernel_tan(double x, double y, int iy);
int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2);

// ---------------------------------------------------------------------------
// ------------------ Define endianness for IEEE arithmetic ------------------
// ---------------------------------------------------------------------------

#if defined(mc68000)|| defined(__mc68000) || defined(_M68000) || \
    defined(mc68020)|| defined(__mc68020) || defined(_M68020) || \
    defined(mc68030)|| defined(__mc68030) || defined(_M68030) || \
    defined(mc68040)|| defined(__mc68040) || defined(_M68040) || \
    defined(mc68060)|| defined(__mc68060) || defined(_M68060)
#define __IEEE_BIG_ENDIAN
#endif

#if defined(INTELCPU) || defined(i386)     || defined(i486)    || \
    defined(intel)    || defined(x86)      || defined(i86pc)   || \
    defined(__i386__) || defined(__alpha)  || defined(__osf__) || \
    defined(__x86_64__)
#define __IEEE_LITTLE_ENDIAN
#endif

#if defined(PPCCPU) || defined(__PPC__) || defined(__powerpc__)
#define __IEEE_BIG_ENDIAN
#endif

#if defined(ARMCPU) || defined(__arm__)
#define __IEEE_BIG_ENDIAN
#endif

#ifndef __IEEE_BIG_ENDIAN
#ifndef __IEEE_LITTLE_ENDIAN
#error Must define endianness  
#endif
#endif

// ---------------------------------------------------------------------------
// -------------- Endianness implementation for IEEE arithmetic --------------
// ---------------------------------------------------------------------------

/**
 * @brief 32 bit unsigned integer.
 *
 */
typedef unsigned int uword;

/**
 * @brief 32 bit signed integer.
 *
 */
typedef signed int sword;

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
// ------------------- End of real primitive definitions ---------------------
// ---------------------------------------------------------------------------

#endif
