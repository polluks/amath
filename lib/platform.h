/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
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

#ifndef AMATH_LIB_PLATFORM_H
#define AMATH_LIB_PLATFORM_H

#include <stddef.h>
#include "mem.h"

#define EMPTYSTRING ""
#define SPACE       " "
#define DOT         "."

#ifdef _WIN32
#define NEWLINE     "\r\n"
#else
#define NEWLINE     "\n"
#endif

#define NOMEM       0

#define LONG_BIT    32
#define wsize       sizeof(unsigned int)
#define wmask       (wsize - 1)

#ifndef __cplusplus
typedef int bool;
#define true  1
#define false 0
#endif

#ifdef  __AMIGA__
# ifndef AOS3
# define AOS3
# endif
#endif

#ifdef  __AROS__
# ifndef AROS
# define AROS
# endif
#endif

#ifdef  __MORPHOS__
# ifndef MORPHOS
# define MORPHOS
# endif
#endif

#ifdef  __amigaos4__
# ifndef AOS4
# define AOS4
# endif
#endif

#ifdef __HAIKU__
# ifndef HAIKU
# define HAIKU
# endif
#endif

#if defined(AOS3) || defined(AOS4) || defined(AROS) || defined (MORPHOS)
# ifndef AMIGA
# define AMIGA
# endif
#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
# ifndef UNIX
# define UNIX
# endif
#endif

#if defined(AMIGA) || defined(HAIKU) || defined(UNIX)
# ifndef ANSICONSOLE
# define ANSICONSOLE
# endif
#endif

#ifdef AMIGA
# include <dos/var.h>
# include <dos/exall.h>
# include <exec/io.h>
# include <exec/types.h>
# include <exec/memory.h>
# include <exec/semaphores.h>
# include <clib/alib_protos.h>
# include <clib/exec_protos.h>
# include <clib/dos_protos.h>
# include <devices/console.h>
# include <devices/conunit.h>
#endif

#ifdef HAIKU
# include <stdint.h>
# include <unistd.h>
# include <dirent.h>
#endif

#ifdef UNIX
# include <stdint.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
#endif

#ifdef _WIN32
# include <stdint.h>
#endif

#ifdef AOS3
# include <sys/types.h>
#endif

#ifdef AROS
# include <stdint.h>
# include <sys/types.h>
#endif

#ifdef MORPHOS
# include <stdint.h>
# include <sys/types.h>
#endif

#ifdef AOS4
# error Includedes must be defined for Amiga OS 4+
#endif

#ifdef AOS3
#define IPTR      LONG*
typedef u_int8_t  uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
#endif

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

/* ANSI escape codes */
#if defined(ANSICONSOLE)
#define HEADLINE         "\x1B[1m"
#ifdef UNIX
#define SYNTAXHIGHLIGHT  "\x1B[3m\x1B[32m"
#else
#define SYNTAXHIGHLIGHT  "\x1B[32m"
#endif
#define NORMALTEXT       "\x1B[0m"
#define BOLD             "\x1B[1m"
#define ITALICS          "\x1B[3m"
#define UNDERLINE        "\x1B[4m"
#define COLOR01          "\x1B[31m"
#define COLOR02          "\x1B[32m"
#define COLOR03          "\x1B[33m"
#define CURSORFORWARD    "\x1B[1C"
#define CURSORBACKWARD   "\x1B[1D"
#define ERASEINLINE      "\x1B[K"
#define INSERT1CHAR      "\x1B[1@"
#define DELETE1CHAR      "\x1B[1P"
#define DELETELINE       "\x0D\x1B[K"
#define CLEARWINDOW      "\x1B[1;1H\x1B[J"
#else
#define HEADLINE         EMPTYSTRING
#define SYNTAXHIGHLIGHT  EMPTYSTRING
#define NORMALTEXT       EMPTYSTRING
#define BOLD             EMPTYSTRING
#define ITALICS          EMPTYSTRING
#define UNDERLINE        EMPTYSTRING
#define COLOR01          EMPTYSTRING
#define COLOR02          EMPTYSTRING
#define COLOR03          EMPTYSTRING
#define CURSORFORWARD    EMPTYSTRING
#define CURSORBACKWARD   EMPTYSTRING
#define ERASEINLINE      EMPTYSTRING
#define INSERT1CHAR      EMPTYSTRING
#define DELETE1CHAR      EMPTYSTRING
#define DELETELINE       EMPTYSTRING
#define CLEARWINDOW      EMPTYSTRING
#endif /* ANSICONSOLE */

#endif /* AMATH_LIB_PLATFORM_H */
