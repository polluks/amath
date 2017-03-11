/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#ifndef AMATH_LOCALIZE_KEYWORD_H
#define AMATH_LOCALIZE_KEYWORD_H

/**
 * @file  localize/kword.h
 * @brief Keywords used by lexer.
 *
 */

#include "amath.h"
#include "amathc.h"
#include "localize/lex.h"

/**
 * @brief Character representation of keyword tied with its symbol.
 *
 */
struct keyworddef
{
    int id;
    Symbol symbol;
    const char* name;
};

static const keyworddef keywords[] = {
    { 0, symclear, "clear" },
    { 1, symdef, "def" },
    { 2, symdelete, "delete" },
    { 3, syme, "e" },
    { 4, symi, "i" },
    { 5, sympi, "pi" },
    { 6, symins, "ins" },
    { 7, symeval, "eval" },
    { 8, symdraw, "draw" },
    { 9, symplot, "plot" },
    { 10, symexecute, "execute" },
    { 11, symexit, "exit" },
    { 12, symexit, "quit" },
    { 13, symstatement, "statements" },
    { 14, symoperator, "operators" },
    { 15, symcomplex, "complex" },
    { 16, symfunction, "funcs" },
    { 17, symfunction, "functions" },
    { 18, symtrigon, "trigon" },
    { 19, symtrigon, "trigonometric" },
    { 20, symhyper, "hyper" },
    { 21, symhyper, "hyperbolic" },
    { 22, symearly, "early" },
    { 23, symhelp, "help" },
    { 24, symprompt, "prompt" },
    { 25, symversion, "version" },
    { 26, symmem, "mem" },
    { 27, symmem, "memory" },
    { 28, symprefs, "prefs" },
    { 29, symprefs, "preferences" },
    { 30, symlist, "list" },
    { 31, symload, "load" },
    { 32, symsave, "save" },
    { 33, symshow, "show" },
    { 34, symvariable, "vars" },
    { 35, symvariable, "variables" },
    { 36, symdigits, "digits" },
    { 37, syminput, "input" },
    { 38, symoutput, "output" },
    { 39, symbin, "bin" },
    { 40, symbin, "binary" },
    { 41, symoct, "oct" },
    { 42, symoct, "octal" },
    { 43, symdec, "dec" },
    { 44, symdec, "decimal" },
    { 45, symhex, "hex" },
    { 46, symhex, "hexadecimal" },
    { 47, symabout, "about" },
    { 48, symlicense, "license" },
    { -1, Symbol(0), EMPTYSTRING }
};

#endif
