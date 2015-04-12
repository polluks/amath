/*
 * Copyright (c) 2015 Carsten Larsen
 * All rights reserved.
 *
 * This code contains contributions from Stefan Haubenthal
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

#ifndef _DEF_TEXT_H
#define _DEF_TEXT_H

/**
 * @file  text.h
 * @brief Text defitions used by input / output classes.
 *
 */

#include "def/libc.h"

/**
 * @brief Empty NULL terminated string.
 *
 * Use to avoid compiler warnings.
 */
#define EMPTYSTRING ""

/**
 * @brief Environment dependent space string.
 *
 * Use to ensure portablility.
 */
#define SPACE       " "

/**
 * @brief Environment dependent new line string.
 *
 * Use to ensure portablility.
 */
#define NEWLINE     "\n"

// -----------------------------------------------------
// --------- Processor architecture defitions ----------
// -----------------------------------------------------

#ifdef mc68000
#define ACPU "68000+"
#endif

#ifdef mc68020
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "68020"
#endif

#ifdef mc68030
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "68030"
#endif

#ifdef mc68040
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "68040"
#endif

#ifdef mc68060
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "68060"
#endif

#if defined(INTELCPU)  || defined(i386)    || defined(i486)  ||  \
    defined(intel)     || defined(x86)     || defined(i86pc) ||  \
    defined(__i386__)  || defined(_M_IX86)
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "i386"
#endif

#ifdef __powerpc__
#define ACPU "PowerPC"
#endif

#if defined(__x86_64__)
#ifdef ACPU
#undef ACPU
#endif
#define ACPU "amd64"
#endif

#ifdef WITHTEST
#define ATEST SPACE "TEST"
#else
#define ATEST EMPTYSTRING
#endif

#if defined(ACPU) && defined(__HAVE_68881__)
#define AFPU SPACE "FPU"
#else
#define AFPU EMPTYSTRING
#endif

#ifndef ACPU
#define ACPU EMPTYSTRING
#endif

// -----------------------------------------------------
// ------------ Title and copyright texts --------------
// -----------------------------------------------------

#define ARCH         ACPU AFPU ATEST
#define ATITLE       "amath version 1.5.7"
#define ACOPYRIGHT   "(c) 2015 Carsten Sonne Larsen"
#define ASTARTMSG    ATITLE SPACE ARCH SPACE ACOPYRIGHT
#define AVERSION     "\0$VER: amath 1.57 (12-04-2015)"
#define DOSVERSION   AVERSION SPACE ACPU AFPU ATEST

// -----------------------------------------------------
// ------------ Console control characters -------------
// -----------------------------------------------------

#if defined(AMIGA) || defined(ANSICONSOLE)
#define HEADLINE         "\x1B[1m"
#define SYNTAXHIGHLIGHT  "\x1B[32m"
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

// -----------------------------------------------------
// ----------------- Console messages ------------------
// -----------------------------------------------------

#define AINTROMSG  NORMALTEXT BOLD ASTARTMSG NEWLINE  \
                   NORMALTEXT COLOR02 ITALICS         \
                   "Type help to show info." NEWLINE  \
                   NORMALTEXT
#define PROMPT     NORMALTEXT "> "

#define TXTLISTDIRHEADER \
    "Type        Name" NEWLINE \
    "-----------------------------------------------" \
    NEWLINE;

#define TXTLISTDIRTFILE    "[file]"
#define TXTLISTDIRTDIR     "[dir]"
#define TXTLISTDIRTUNKNOWN "[unknown]"

// -----------------------------------------------------
// ------------------ Error messages -------------------
// -----------------------------------------------------

#define HELPNOHELP   "No help is available for this topic." NEWLINE
#define HELPSYNTAX   "Syntax error:" SPACE
#define HELPUERROR   "Unexpected error:" SPACE
#define HELPVARNDEF  "Variable is not defined:" SPACE
#define HELPFUNNDEF  "Function is not defined:" SPACE
#define HELPFUNRDEF  "Function cannot be redefined: " SPACE
#define HELPPNUMERA  "Base value must be between 2 and 32:" SPACE
#define HELPPDIGITS  "Number of digist must be between 0 and 15:" SPACE
#define HELPINPUSHOW "Numeral input system is" SPACE
#define HELPOUTPSHOW "Numeral output system is" SPACE
#define HELPINPUSETT "Input changed to" SPACE
#define HELPOUTPSETT "Output changed to" SPACE
#define HELPDIGISETT "Number of digits changed to" SPACE
#define HELPDIGISHOW "Number of digits shown are" SPACE
#define HELPVARSNDEF "No variables are defined." NEWLINE
#define HELPFUNCNDEF "No functions are defined." NEWLINE
#define HELPLOADSUCC "Variable and functions loaded from file." NEWLINE
#define HELPSAVESUCC "Variable and functions saved to file." NEWLINE
#define HELPSAVEFAIL "Cannot save to file." NEWLINE
#define HELPSAVENOTH "Nothing to save." NEWLINE
#define MSGNODIR     "Could not open directory:" SPACE
#define MSGNOFILE    "Cannot open file."

#endif
