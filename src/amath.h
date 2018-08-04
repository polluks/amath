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

#ifndef AMATH_H
#define AMATH_H
/******************************************************************************/
#ifdef  __AMIGA__
# ifndef AOS3
# define AOS3
# endif
#endif
/******************************************************************************/
#ifdef  __AROS__
# ifndef AROS
# define AROS
# endif
#endif
/******************************************************************************/
#ifdef  __MORPHOS__
# ifndef MORPHOS
# define MORPHOS
# endif
#endif
/******************************************************************************/
#ifdef  __amigaos4__
# ifndef AOS4
# define AOS4
# endif
#endif
/******************************************************************************/
#ifdef __HAIKU__
# ifndef HAIKU
# define HAIKU
# endif
#endif
/******************************************************************************/
#ifdef __APPLE__
# ifndef APPLE
# define APPLE
# endif
#endif
/******************************************************************************/
#if defined(_WIN32) || defined(_WIN64)
# ifndef WINDOWS
# define WINDOWS
# endif
#endif
/******************************************************************************/
#if defined(AOS3) || defined(AOS4) || defined(AROS) || defined (MORPHOS)
# ifndef AMIGA
# define AMIGA
# endif
#endif
/******************************************************************************/
#if defined(unix) || defined(__unix__) || defined(__unix)
# ifndef UNIX
# define UNIX
# endif
#endif
/******************************************************************************/
#if defined(HAIKU) || defined(UNIX) || defined(APPLE)
# ifndef TERMIOS
# define TERMIOS
# endif
# include <stdint.h>
# include <unistd.h>
#endif
/******************************************************************************/
#if defined(WINDOWS)
# include <stdint.h>
#endif
/******************************************************************************/
#if defined(AROS) || defined(MORPHOS) || defined(AOS4)
# include <stdint.h>
# include <sys/types.h>
#endif
/******************************************************************************/
#if defined(AOS3)
# include <sys/types.h>
# define IPTR      LONG*
# define uintptr_t uint32_t
typedef u_int8_t   uint8_t;
typedef u_int16_t  uint16_t;
typedef u_int32_t  uint32_t;
typedef u_int64_t  uint64_t;
#endif
/******************************************************************************/
#if (__cplusplus <= 199711L && !defined(WINDOWS)) || !defined(__cplusplus)
#ifndef nullptr
#define nullptr 0
#endif
#elif (__cplusplus <= 199711L) && (defined(__GNUC__) || defined(__GNUG__))
#ifndef nullptr
#define nullptr 0
#endif
#endif
/******************************************************************************/
#define assert(x)
/******************************************************************************/
/* Compilers*/
#if defined(__clang__)
/* Clang */
# if defined(__apple_build_version__)
#  define COMP_NAME      "XCode Clang"
# else
#  define COMP_NAME      "Clang/LLVM"
# endif
# define str(x)          #x
# define CL_VER_STR(x)   str(x)
# ifdef __clang_patchlevel__
#  define COMP_VERS      CL_VER_STR(__clang_major__) DOT \
                         CL_VER_STR(__clang_minor__) DOT \
                         CL_VER_STR(__clang_patchlevel__)
# else
#  define COMP_VERS      CL_VER_STR(__clang_major__) DOT \
                         CL_VER_STR(__clang_minor__)
# endif

/* Intel ICC/ICPC */
#elif defined(__ECC) || defined(__ICC) || defined(__INTEL_COMPILER)
# define COMP_NAME       "Intel ICC/ICPC"
# define COMP_VERS       __VERSION__

/* IBM XL C/C++ */
#elif defined(__IBMC__) || defined(__IBMCPP__)
# define COMP_NAME       "IBM XL"
# define COMP_VERS       __xlc__

/* Microsoft Visual Studio */
#elif defined(_MSC_VER)
# define COMP_NAME       "MSVC++"
# if (_MSC_VER == 1100)
#  define COMP_VERS      "5.0"
# elif (_MSC_VER == 1200)
#  define COMP_VERS      "6.0"
# elif (_MSC_VER == 1300)
#  define COMP_VERS      "7.0"
# elif (_MSC_VER == 1310)
#  define COMP_VERS      "7.1"
# elif (_MSC_VER == 1400)
#  define COMP_VERS      "8.0"
# elif (_MSC_VER == 1500)
#  define COMP_VERS      "9.0"
# elif (_MSC_VER == 1600)
#  define COMP_VERS      "10.0"
# elif (_MSC_VER == 1700)
#  define COMP_VERS      "11.0"
# elif (_MSC_VER == 1800)
#  define COMP_VERS      "12.0"
# elif (_MSC_VER == 1900)
#  define COMP_VERS      "14.0"
# elif (_MSC_VER > 1900)
#  define COMP_VERS      "15.0+"
# else
#  define str(x)         #x
#  define MSC_VER_STR(x) str(x)
#  define COMP_VERS      MSC_VER_STR(_MSC_VER)
# endif

/* Portland Group PGCC/PGCPP */
#elif defined(__PGI)
# define COMP_NAME       "PGCC/PGCPP"
# define str(x)          #x
# define PGCC_VER_STR(x) str(x)
# ifdef __PGIC_PATCHLEVEL__
#  define COMP_VERS      PGCC_VER_STR(__PGIC__) DOT \
                         PGCC_VER_STR(__PGIC_MINOR) DOT \
                         PGCC_VER_STR(__PGIC_PATCHLEVEL__)
# else
#  define COMP_VERS      PGCC_VER_STR(__PGIC__) DOT \
                         PGCC_VER_STR(__PGIC_MINOR)
# endif

/* GNU GCC/G++ */
#elif defined(__GNUC__) || defined(__GNUG__)
# define COMP_NAME       "GCC"
# define str(x)          #x
# define GCC_VER_STR(x)  str(x)
# ifdef __GNUC_PATCHLEVEL__
#  define COMP_VERS      GCC_VER_STR(__GNUC__) DOT GCC_VER_STR(__GNUC_MINOR__) DOT \
                         GCC_VER_STR(__GNUC_PATCHLEVEL__)
# else
#  define COMP_VERS      GCC_VER_STR(__GNUC__) DOT GCC_VER_STR(__GNUC_MINOR__)
# endif
#endif
/******************************************************************************/
#define EMPTYSTRING ""
#define SPACE       " "
#define DOT         "."
/******************************************************************************/
#if defined(WINDOWS)
#define NEWLINE     "\r\n"
#elif defined(APPLE)
#define NEWLINE     "\r"
#else
#define NEWLINE     "\n"
#endif
/******************************************************************************/
#ifndef __cplusplus
typedef int bool;
#define true  1
#define false 0
#endif
/******************************************************************************/
#define LONG_BIT    32
#define wsize       sizeof(unsigned int)
#define wmask       (wsize - 1)
/******************************************************************************/
#if defined(INTELCPU)  || defined(i386)    || defined(i486)  ||  \
    defined(intel)     || defined(x86)     || defined(i86pc) ||  \
    defined(__i386__)  || defined(_M_IX86)
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU          "i386"
#endif
#if defined(__x86_64__) || defined(_M_AMD64)
# define TXTCPU          "amd64"
#endif
/******************************************************************************/
#if defined(__powerpc__) || defined(__powerpc64__)
# define TXTCPU          "PowerPC"
#endif
/******************************************************************************/
#if defined(__arm__) || defined(_M_ARM) || defined(__ARM_ARCH_6__)
# define TXTCPU          "arm"
#endif
#if defined(__aarch64__) || defined(_M_ARM64)
# define TXTCPU          "arm64"
#endif
/******************************************************************************/
#if defined(m68060) || defined(mc68060)
# define TXTCPU          "68060"
#elif defined(m68040) || defined(mc68040)
# define TXTCPU          "68040"
#elif defined(m68030) || defined(mc68030)
# define TXTCPU          "68030"
#elif defined(m68020) || defined(mc68020)
# define TXTCPU          "68020"
#elif defined(m68010) || defined(mc68010)
# define TXTCPU          "68010"
#elif defined(m68000) || defined(mc68000)
# define TXTCPU          "68000+"
#endif
/******************************************************************************/
#ifndef TXTCPU
//#error what cpu is this ?!
# define TXTCPU EMPTYSTRING
#endif
/******************************************************************************/
#if defined(TXTCPU) && defined(__HAVE_68881__)
# define TXTFPU SPACE    "FPU"
#else
# define TXTFPU EMPTYSTRING
#endif
/******************************************************************************/
#define TXTARCH          TXTCPU TXTFPU
#define RELDATESTAMP     "(21-07-2017)"
#define TXTDOSVERSION    "\0$VER: amath 1.83" SPACE RELDATESTAMP SPACE TXTARCH
#define TXTTITLE         "amath version 1.8.3"
#define TXTCOPYRIGHT     "(c) 2018 Carsten Sonne Larsen"
#define TXTSTARTMSG      TXTTITLE SPACE TXTCOPYRIGHT
/******************************************************************************/
#define TXTVERSMSG       TXTTITLE SPACE RELDATESTAMP SPACE TXTARCH
#define TXTCOMPMSG       "Compiled with " COMP_NAME SPACE COMP_VERS
/******************************************************************************/
#define CPROCNAME        "amath_console"
/******************************************************************************/
#if defined(AMIGA)
#define AMIGADOS_NAME    "dos.library"
#define AMIGADOS_REV     33L
#define INTUITION_REV    37L
#define INTUITION_NAME   "intuition.library"
#define GRAPHICS_REV     37L
#define GRAPHICS_NAME    "graphics.library"
#define LOCALE_REV       38L
#define LOCALE_NAME      "locale.library"
#define DEVCONSOLE       "console.device"
#define PORTCR           "RKM.console.read"
#define PORTCW           "RKM.console.write"
#define CATALOG_HELP     "amath-help.catalog"
#define CATALOG_IDEN     "amath-ident.catalog"
#define CATALOG_TEXT     "amath-text.catalog"
#define CATALOG_KEYW     "amath-keyword.catalog"
#define CATALOG_DEF      OC_BuiltInLanguage, "english"
#endif
/******************************************************************************/
#endif
