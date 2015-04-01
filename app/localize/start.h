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
#define ACPU "68000+"
#endif
#ifdef mc68020
#define ACPU "68020"
#endif
#ifdef mc68030
#define ACPU "68030"
#endif
#ifdef mc68040
#define ACPU "68040"
#endif
#ifdef mc68060
#define ACPU "68060"
#endif
/******************************************************************************/
#if defined(INTELCPU) || defined(i386) || defined(i486)  || \
    defined(intel)    || defined(x86)  || defined(i86pc) || \
    defined(__i386__)
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "i386"
#endif
#ifdef __powerpc__
#define ACPU "PowerPC"
#endif
#if defined(__x86_64__)
#define ACPU "amd64"
#endif
#ifndef ACPU
#error what cpu is this ?!
//#define ACPU EMPTYSTRING
#endif
/******************************************************************************/
#if defined(AROS)
#define ASYSNAME SPACE "AROS"
#endif
#if defined(MORPHOS)
#define ASYSNAME SPACE "MorphOS"
#endif
#if defined(AOS3) || defined(AOS4)
#define ASYSNAME SPACE "AmigaOS"
#endif
#ifndef ASYSNAME
#define ASYSNAME EMPTYSTRING
#endif
/******************************************************************************/
#ifdef WITHTEST
#define ATEST SPACE "TEST"
#else
#define ATEST EMPTYSTRING
#endif
/******************************************************************************/
#if defined(ACPU) && defined(__HAVE_68881__)
#define AFPU SPACE "FPU"
#else
#define AFPU EMPTYSTRING
#endif
/******************************************************************************/
#define ARCH        ACPU AFPU ASYSNAME ATEST
#define ATITLE      "amath version 1.6.0"
#define ACOPYRIGHT  "(c) 2015 Carsten Sonne Larsen"
#define ASTARTMSG   ATITLE SPACE ARCH SPACE ACOPYRIGHT
#define ADOSVERSION "\0$VER: amath 1.60 (01-04-2015)"
/******************************************************************************/
#endif
