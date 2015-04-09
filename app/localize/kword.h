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
 * Generated with FlexCat. For more information, see:
 * http://sourceforge.net/projects/flexcat/
 *
 */

#ifndef AMATH_TEXT_KEYWORD_H
#define AMATH_TEXT_KEYWORD_H

/**
 * @file  kword.h
 * @brief Keywords used by lexer.
 *
 */

#include "clib.h"
#include "localize/lex.h"

/**
 * @brief Character representation of keyword tied with its symbol.
 *
 */
struct keyworddef {
    const char *name;
    Symbol symbol;
};

static const keyworddef keywords[] = {
    { "clear", symclear },
    { "def", symdef },
    { "delete", symdelete },
    { "e", syme },
    { "i", symi },
    { "pi", sympi },
    { "ins", symins },
    { "eval", symeval },
    { "draw", symdraw },
    { "plot", symplot },
    { "execute", symexecute },
    { "exit", symexit },
    { "quit", symexit },
    { "statements", symstatement },
    { "operators", symoperator },
    { "complex", symcomplex },
    { "funcs", symfunction },
    { "functions", symfunction },
    { "trigon", symtrigon },
    { "trigonometric", symtrigon },
    { "hyper", symhyper },
    { "hyperbolic", symhyper },
    { "help", symhelp },
    { "prompt", symprompt },
    { "version", symversion },
    { "mem", symmem },
    { "memory", symmem },
    { "prefs", symprefs },
    { "preferences", symprefs },
    { "list", symlist },
    { "load", symload },
    { "save", symsave },
    { "show", symshow },
    { "vars", symvariable },
    { "variables", symvariable },
    { "digits", symdigits },
    { "input", syminput },
    { "output", symoutput },
    { "bin", symbin },
    { "binary", symbin },
    { "oct", symoct },
    { "octal", symoct },
    { "dec", symdec },
    { "decimal", symdec },
    { "hex", symhex },
    { "hexadecimal", symhex },
    { EMPTYSTRING, Symbol(0) }
};

#endif
