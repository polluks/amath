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

#ifndef AMATH_LIB_PLATFROM_H
#define AMATH_LIB_PLATFROM_H

#include <stddef.h>

#ifdef  __AMIGA__
#ifndef AOS3
#define AOS3
#endif
#endif

#ifdef  __AROS__
#ifndef AROS
#define AROS
#endif
#endif

#ifdef  __MORPHOS__
#ifndef MORPHOS
#define MORPHOS
#endif
#endif

#ifdef  __amigaos4__
#ifndef AOS4
#define AOS4
#endif
#endif

// Check weather an AmigaOS compatible API is available
#if defined(AOS3) || defined(AOS4) || defined(AROS) || defined (MORPHOS)
#ifndef AMIGA
#define AMIGA
#endif
#include <exec/io.h>
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/semaphores.h>
#include <clib/exec_protos.h>
#endif

/* POSIX */
#ifndef AMIGA
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#endif

/* GCC 2.95 etc */
#ifdef AOS3
#include <sys/types.h>
typedef u_int8_t    uint8_t;
typedef u_int16_t   uint16_t;
typedef u_int32_t   uint32_t;
typedef u_int64_t   uint64_t;
#endif

/* GCC 4.x & AROS API */
#ifdef AROS
#include <stdint.h>
#include <sys/types.h>
#endif

#ifdef MORPHOS
#include <stdint.h>
#include <sys/types.h>
#endif

#ifdef AOS4
#error Includedes must be defined for Amiga OS 4+
#endif

#endif