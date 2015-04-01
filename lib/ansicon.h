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

#ifndef AMATH_ANSICON_H
#define AMATH_ANSICON_H

/**
 *
 *
 *
 */

#include "text.h"

// -----------------------------------------------------
// ------------ Console control characters -------------
// -----------------------------------------------------

#if defined(ANSICONSOLE)
#define HEADLINE         "\x1B[1m"
#define SYNTAXHIGHLIGHT  "\x1B[3m\x1B[32m"
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
#endif

#endif
