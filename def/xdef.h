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

#ifndef _DEF_XDEF_H
#define _DEF_XDEF_H

/**
 * @file  xdef.h
 * @brief OS specific definies and special undefs to prevent namespace clash.
 *
 */

#define CPROCNAME "amath_console"

#ifdef AMIGA

#ifdef Node
#undef Node
#endif
#ifdef Exit
#undef Exit
#endif
#ifdef Execute
#undef Execute
#endif

#ifdef AOS
#define DEVCONSOLE     (UBYTE*)"console.device"
#define INTUITION_REV  33L
#define INTUITION_NAME (UBYTE*)"intuition.library"
#define GRAPHICS_REV   33L
#define GRAPHICS_NAME  (UBYTE*)"graphics.library"
#define PORTCR         "RKM.console.read"
#define PORTCW         "RKM.console.write"
#endif

#if defined(AROS) || defined(AOS4)
#define DEVCONSOLE     "console.device"
#define INTUITION_REV  33L
#define INTUITION_NAME "intuition.library"
#define GRAPHICS_REV   33L
#define GRAPHICS_NAME  "graphics.library"
#define PORTCR         (STRPTR)"RKM.console.read"
#define PORTCW         (STRPTR)"RKM.console.write"
#endif

#ifndef DEVCONSOLE
#error Must define library dependencies
#endif

#endif
#endif
