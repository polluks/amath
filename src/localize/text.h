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

#ifndef AMATH_LOCALIZE_TEXT_H
#define AMATH_LOCALIZE_TEXT_H

/**
 * @file  localize/text.h
 * @brief Static texts in amath.
 *
 */

#include "main.h"
#include "amath.h"
#include "amathc.h"
#include "amatht.h"
#include "system/program.h"

#define INTROMSG (Program->Language->GetText(0))
#define STATEMENTLINE (Program->Language->GetText(1))
#define STATEMENTCLEAR (Program->Language->GetText(2))
#define STATEMENTDEF (Program->Language->GetText(3))
#define STATEMENTDELETE (Program->Language->GetText(4))
#define STATEMENTDIGITS (Program->Language->GetText(5))
#define STATEMENTEVAL (Program->Language->GetText(6))
#define STATEMENTEXECUTE (Program->Language->GetText(7))
#define STATEMENTFUNCS (Program->Language->GetText(8))
#define STATEMENTINPUT (Program->Language->GetText(9))
#define STATEMENTHELP (Program->Language->GetText(10))
#define STATEMENTOUTPUT (Program->Language->GetText(11))
#define STATEMENTLIST (Program->Language->GetText(12))
#define STATEMENTSHOW (Program->Language->GetText(13))
#define STATEMENTLOAD (Program->Language->GetText(14))
#define STATEMENTSAVE (Program->Language->GetText(15))
#define STATEMENTVARS (Program->Language->GetText(16))
#define STATEMENTVERSION (Program->Language->GetText(17))
#define STATEMENTMEMORY (Program->Language->GetText(18))
#define STATEMENTEXIT (Program->Language->GetText(19))
#define STATEMENTFOOTER (Program->Language->GetText(20))
#define TXTLISTDIRHEADER (Program->Language->GetText(21))
#define TXTLISTDIRTFILE (Program->Language->GetText(22))
#define TXTLISTDIRTDIR (Program->Language->GetText(23))
#define TXTLISTDIRTUNKNOWN (Program->Language->GetText(24))
#define TXTMEMBLOCKS (Program->Language->GetText(25))
#define TXTMEMSIZE (Program->Language->GetText(26))
#define TXTMEMMAXSIZE (Program->Language->GetText(27))
#define HELPNOHELP (Program->Language->GetText(28))
#define HELPSYNTAX (Program->Language->GetText(29))
#define HELPUERROR (Program->Language->GetText(30))
#define HELPVARNDEF (Program->Language->GetText(31))
#define HELPFUNNDEF (Program->Language->GetText(32))
#define HELPFUNRDEF (Program->Language->GetText(33))
#define HELPPNUMERA (Program->Language->GetText(34))
#define HELPPDIGITS (Program->Language->GetText(35))
#define HELPINPUSHOW (Program->Language->GetText(36))
#define HELPOUTPSHOW (Program->Language->GetText(37))
#define HELPINPUSETT (Program->Language->GetText(38))
#define HELPOUTPSETT (Program->Language->GetText(39))
#define HELPDIGISETT (Program->Language->GetText(40))
#define HELPDIGISHOW (Program->Language->GetText(41))
#define HELPVARSNDEF (Program->Language->GetText(42))
#define HELPFUNCNDEF (Program->Language->GetText(43))
#define HELPLOADSUCC (Program->Language->GetText(44))
#define HELPSAVESUCC (Program->Language->GetText(45))
#define HELPSAVEFAIL (Program->Language->GetText(46))
#define HELPSAVENOTH (Program->Language->GetText(47))
#define HELPPREFLOAD (Program->Language->GetText(48))
#define HELPPREFNOLO (Program->Language->GetText(49))
#define HELPPREFSAVE (Program->Language->GetText(50))
#define HELPPREFNOSA (Program->Language->GetText(51))
#define MSGNODIR (Program->Language->GetText(52))
#define MSGNOFILE (Program->Language->GetText(53))

static const textdef textdefs[] = {
    { 0, "#NORMALTEXT##BOLD##STARTMSG##NEWLINE##NORMALTEXT##COLOR02#Type help to show info.#NEWLINE#" }, /* INTROMSG */
    { 1, "---------------------------------------------------------#NEWLINE#" }, /* STATEMENTLINE */
    { 2, "clear      Clear console window.#NEWLINE#" }, /* STATEMENTCLEAR */
    { 3, "def        Define function.#NEWLINE#" }, /* STATEMENTDEF */
    { 4, "delete     Delete variable or function.#NEWLINE#" }, /* STATEMENTDELETE */
    { 5, "digits     Set number of significant digits.#NEWLINE#" }, /* STATEMENTDIGITS */
    { 6, "eval       Evaluate arithmetic expression.#NEWLINE#" }, /* STATEMENTEVAL */
    { 7, "execute    Execute statements in a file.#NEWLINE#" }, /* STATEMENTEXECUTE */
    { 8, "functions  Show list of user defined functions.#NEWLINE#" }, /* STATEMENTFUNCS */
    { 9, "input      Change numeral input system.#NEWLINE#" }, /* STATEMENTINPUT */
    { 10, "help       Show basic help text.#NEWLINE#" }, /* STATEMENTHELP */
    { 11, "output     Change numeral output system.#NEWLINE#" }, /* STATEMENTOUTPUT */
    { 12, "list       Show content of a directory.#NEWLINE#" }, /* STATEMENTLIST */
    { 13, "show       Show content of a file.#NEWLINE#" }, /* STATEMENTSHOW */
    { 14, "load       Load variable and functions from file.#NEWLINE#" }, /* STATEMENTLOAD */
    { 15, "save       Save variable and functions to file.#NEWLINE#" }, /* STATEMENTSAVE */
    { 16, "variables  Show list of variables.#NEWLINE#" }, /* STATEMENTVARS */
    { 17, "version    Show version string.#NEWLINE#" }, /* STATEMENTVERSION */
    { 18, "memory     Show internal memory usage.#NEWLINE#" }, /* STATEMENTMEMORY */
    { 19, "exit       Exit program.#NEWLINE#" }, /* STATEMENTEXIT */
    { 20, "The def and eval statements are optional. Functions and#NEWLINE#variables statements can be shorten to funcs and vars.#NEWLINE#" }, /* STATEMENTFOOTER */
    { 21, "Type        Name#NEWLINE#-----------------------------------------------#NEWLINE#" }, /* TXTLISTDIRHEADER */
    { 22, "[file]" }, /* TXTLISTDIRTFILE */
    { 23, "[dir]" }, /* TXTLISTDIRTDIR */
    { 24, "[unknown]" }, /* TXTLISTDIRTUNKNOWN */
    { 25, "Allocated blocks:#SPACE#" }, /* TXTMEMBLOCKS */
    { 26, "Memory usage:    #SPACE#" }, /* TXTMEMSIZE */
    { 27, "Maximum usage:   #SPACE#" }, /* TXTMEMMAXSIZE */
    { 28, "No help is available for this topic.#NEWLINE#" }, /* HELPNOHELP */
    { 29, "Syntax error:#SPACE#" }, /* HELPSYNTAX */
    { 30, "Unexpected error:#SPACE#" }, /* HELPUERROR */
    { 31, "Variable is not defined:#SPACE#" }, /* HELPVARNDEF */
    { 32, "Function is not defined:#SPACE#" }, /* HELPFUNNDEF */
    { 33, "Function cannot be redefined:#SPACE#" }, /* HELPFUNRDEF */
    { 34, "Base value must be between 2 and 32:#SPACE#" }, /* HELPPNUMERA */
    { 35, "Number of digist must be between 0 and 15:#SPACE#" }, /* HELPPDIGITS */
    { 36, "Numeral input system is#SPACE#" }, /* HELPINPUSHOW */
    { 37, "Numeral output system is#SPACE#" }, /* HELPOUTPSHOW */
    { 38, "Input changed to#SPACE#" }, /* HELPINPUSETT */
    { 39, "Output changed to#SPACE#" }, /* HELPOUTPSETT */
    { 40, "Number of digits changed to#SPACE#" }, /* HELPDIGISETT */
    { 41, "Number of digits shown are#SPACE#" }, /* HELPDIGISHOW */
    { 42, "No variables are defined.#NEWLINE#" }, /* HELPVARSNDEF */
    { 43, "No functions are defined.#NEWLINE#" }, /* HELPFUNCNDEF */
    { 44, "Variable and functions loaded from file.#NEWLINE#" }, /* HELPLOADSUCC */
    { 45, "Variable and functions saved to file.#NEWLINE#" }, /* HELPSAVESUCC */
    { 46, "Cannot save to file.#NEWLINE#" }, /* HELPSAVEFAIL */
    { 47, "Nothing to save.#NEWLINE#" }, /* HELPSAVENOTH */
    { 48, "Preferences loaded.#NEWLINE#" }, /* HELPPREFLOAD */
    { 49, "Preferences could not be loaded.#NEWLINE#" }, /* HELPPREFNOLO */
    { 50, "Preferences saved to disk.#NEWLINE#" }, /* HELPPREFSAVE */
    { 51, "Preferences could not be saved.#NEWLINE#" }, /* HELPPREFNOSA */
    { 52, "Could not open directory:#SPACE#" }, /* MSGNODIR */
    { 53, "Cannot open file.#NEWLINE#" }, /* MSGNOFILE */
    { -1, EMPTYSTRING }
};

#endif
