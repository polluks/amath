/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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

#ifndef AMATH_TEXT_LEX_H
#define AMATH_TEXT_LEX_H

/**
 * @file  lex.h
 * @brief Lexer defitions used by other classes.
 *
 */

/**
 * @brief Symbols generated by the Lexer.
 *
 */
typedef enum {
    symunknown, symident, symqident, symnumber,
    symplus, symminus, symtimes, symslash, sympower,
    symabsolute, symassign, symlparen, symrparen,
    symfuncsqrt, symfunccbrt, symfunclog, symfuncln,
    symhelp, symeval, symdelete, symall, symclear, symdef, symexit,
    symoperator, symstatement, symfunction, symvariable,
    symtrigon, symhyper, symcomplex,
    syme, sympi, symi,symins, symdelimiter, symend,
    symshow, symlist, symload, symsave, symexecute,
    syminput, symoutput, symdigits,
    symdec, symhex, symbin, symoct,
    symmem, symprefs, symprompt, symversion,
    symplot, symdraw
} Symbol;

/**
 * @brief Character representation of operator tied with its symbol.
 *
 */
struct operatordef {
    char chr;
    Symbol symbol;
};

static const operatordef operators[] = {
    { '+', symplus},
    { '-', symminus},
    { '/', symslash},
    { '*', symtimes},
    { '^', sympower},
    { '(', symlparen},
    { ')', symrparen},
    { '|', symabsolute},
    { '=', symassign},
    { '\n', symdelimiter},
    { ';', symdelimiter}
};

/*
static const keyworddef keywords[] = {
    { "clear", symclear},
    { "def", symdef},
    { "delete", symdelete},
    { "e", syme},
    { "i", symi},
    { "pi", sympi},
    { "ins", symins},
    { "eval", symeval},
    { "complex", symcomplex},
    { "execute", symexecute},
    { "exit", symexit},
    { "funcs", symfunction},
    { "functions", symfunction},
    { "trigon", symtrigon},
    { "trigonometric", symtrigon},
    { "hyper", symhyper},
    { "hyperbolic", symhyper},
    { "help", symhelp},
    { "list", symlist},
    { "load", symload},
    { "operators", symoperator},
    { "quit", symexit},
    { "save", symsave},
    { "show", symshow},
    { "statements", symstatement},
    { "vars", symvariable},
    { "variables", symvariable},
    { "version", symversion},
    { "digits", symdigits},
    { "mem", symmem},
    { "memory", symmem},
    { "prefs", symprefs},
    { "preferences", symprefs},
    { "prompt", symprompt},
    { "input", syminput},
    { "output", symoutput},
    { "bin", symbin},
    { "binary", symbin},
    { "oct", symoct},
    { "octal", symoct},
    { "dec", symdec},
    { "decimal", symdec},
    { "hex", symhex},
    { "hexadecimal", symhex},
    { "draw", symdraw},
    { "plot", symplot}
};
*/

#endif
