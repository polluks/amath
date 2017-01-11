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
 * Generated with FlexCat. For more information, see:
 * http://sourceforge.net/projects/flexcat/
 *
 */

#ifndef AMATH_LOCALIZE_KEYWORD_H
#define AMATH_LOCALIZE_KEYWORD_H

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
    int id;
    Symbol symbol;
    const char *name;
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
    { 22, symhelp, "help" },
    { 23, symprompt, "prompt" },
    { 24, symversion, "version" },
    { 25, symmem, "mem" },
    { 26, symmem, "memory" },
    { 27, symprefs, "prefs" },
    { 28, symprefs, "preferences" },
    { 29, symlist, "list" },
    { 30, symload, "load" },
    { 31, symsave, "save" },
    { 32, symshow, "show" },
    { 33, symvariable, "vars" },
    { 34, symvariable, "variables" },
    { 35, symdigits, "digits" },
    { 36, syminput, "input" },
    { 37, symoutput, "output" },
    { 38, symbin, "bin" },
    { 39, symbin, "binary" },
    { 40, symoct, "oct" },
    { 41, symoct, "octal" },
    { 42, symdec, "dec" },
    { 43, symdec, "decimal" },
    { 44, symhex, "hex" },
    { 45, symhex, "hexadecimal" },
    { -1, Symbol(0), EMPTYSTRING }
};

#endif
