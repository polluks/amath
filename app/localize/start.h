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

#ifndef AMATH_TEXT_START_H
#define AMATH_TEXT_START_H
/******************************************************************************/
/**
 * @file  start.h
 * @brief Start message and version text
 *
 */
/******************************************************************************/
#include "clib.h"
#ifdef mc68000
# define TXTCPU "68000+"
#endif
#ifdef mc68020
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU "68020"
#endif
#ifdef mc68030
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU "68030"
#endif
#ifdef mc68040
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU "68040"
#endif
#ifdef mc68060
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU "68060"
#endif
/******************************************************************************/
#if defined(INTELCPU)  || defined(i386)    || defined(i486)  ||  \
    defined(intel)     || defined(x86)     || defined(i86pc) ||  \
    defined(__i386__)  || defined(_M_IX86)
# ifdef TXTCPU
# undef TXTCPU
# endif
# define TXTCPU "i386"
#endif
#ifdef __powerpc__
# define TXTCPU "PowerPC"
#endif
#if defined(__x86_64__)
# define TXTCPU "amd64"
#endif
#ifndef TXTCPU
#error what cpu is this ?!
//#define TXTCPU EMPTYSTRING
#endif
/******************************************************************************/
#ifdef WITHTEST
# define TXTTEST SPACE "TEST"
#else
# define TXTTEST EMPTYSTRING
#endif
/******************************************************************************/
#if defined(TXTCPU) && defined(__HAVE_68881__)
# define TXTFPU SPACE "FPU"
#else
# define TXTFPU EMPTYSTRING
#endif
/******************************************************************************/
#define TXTTITLE       "amath version 1.6.0"
#define TXTDOSVERSION  "\0$VER: amath 1.60 (01-04-2015)"
#define TXTCOPYRIGHT   "(c) 2015 Carsten Sonne Larsen"
#define TXTSTARTMSG    TXTTITLE SPACE TXTCPU TXTFPU TXTTEST SPACE TXTCOPYRIGHT
/******************************************************************************/
#endif