/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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
 * https://amath.innolan.net
 * 
 */

#ifndef AMATH_LOCALE_TEXT_H
#define AMATH_LOCALE_TEXT_H

/**
 * @file  loc/text.h
 * @brief Static texts in amath
 */

#include "main.h"
#include "amath.h"
#include "amathc.h"
#include "amatht.h"
#include "system/program.h"

#define INTROMSG (Program->Language->GetText(0))
#define STATEMENTLINE (Program->Language->GetText(1))
#define STATEMENTABOUT (Program->Language->GetText(2))
#define STATEMENTCLEAR (Program->Language->GetText(3))
#define STATEMENTDEF (Program->Language->GetText(4))
#define STATEMENTDELETE (Program->Language->GetText(5))
#define STATEMENTDIGITS (Program->Language->GetText(6))
#define STATEMENTEVAL (Program->Language->GetText(7))
#define STATEMENTEXECUTE (Program->Language->GetText(8))
#define STATEMENTFUNCS (Program->Language->GetText(9))
#define STATEMENTINPUT (Program->Language->GetText(10))
#define STATEMENTHELP (Program->Language->GetText(11))
#define STATEMENTOUTPUT (Program->Language->GetText(12))
#define STATEMENTLIST (Program->Language->GetText(13))
#define STATEMENTSHOW (Program->Language->GetText(14))
#define STATEMENTLOAD (Program->Language->GetText(15))
#define STATEMENTSAVE (Program->Language->GetText(16))
#define STATEMENTVARS (Program->Language->GetText(17))
#define STATEMENTVERSION (Program->Language->GetText(18))
#define STATEMENTLICENSE (Program->Language->GetText(19))
#define STATEMENTMEMORY (Program->Language->GetText(20))
#define STATEMENTEXIT (Program->Language->GetText(21))
#define STATEMENTFOOTER (Program->Language->GetText(22))
#define TXTLISTDIRHEADER (Program->Language->GetText(23))
#define TXTLISTDIRTFILE (Program->Language->GetText(24))
#define TXTLISTDIRTDIR (Program->Language->GetText(25))
#define TXTLISTDIRTUNKNOWN (Program->Language->GetText(26))
#define TXTMEMBLOCKS (Program->Language->GetText(27))
#define TXTMEMSIZE (Program->Language->GetText(28))
#define TXTMEMMAXSIZE (Program->Language->GetText(29))
#define HELPNOHELP (Program->Language->GetText(30))
#define HELPSYNTAX (Program->Language->GetText(31))
#define HELPUERROR (Program->Language->GetText(32))
#define HELPVARNDEF (Program->Language->GetText(33))
#define HELPFUNNDEF (Program->Language->GetText(34))
#define HELPFUNRDEF (Program->Language->GetText(35))
#define HELPPNUMERA (Program->Language->GetText(36))
#define HELPPDIGITS (Program->Language->GetText(37))
#define HELPINPUSHOW (Program->Language->GetText(38))
#define HELPOUTPSHOW (Program->Language->GetText(39))
#define HELPINPUSETT (Program->Language->GetText(40))
#define HELPOUTPSETT (Program->Language->GetText(41))
#define HELPDIGISETT (Program->Language->GetText(42))
#define HELPDIGISHOW (Program->Language->GetText(43))
#define HELPVARSNDEF (Program->Language->GetText(44))
#define HELPFUNCNDEF (Program->Language->GetText(45))
#define HELPLOADSUCC (Program->Language->GetText(46))
#define HELPSAVESUCC (Program->Language->GetText(47))
#define HELPSAVEFAIL (Program->Language->GetText(48))
#define HELPSAVENOTH (Program->Language->GetText(49))
#define HELPPREFLOAD (Program->Language->GetText(50))
#define HELPPREFNOLO (Program->Language->GetText(51))
#define HELPPREFSAVE (Program->Language->GetText(52))
#define HELPPREFNOSA (Program->Language->GetText(53))
#define MSGNODIR (Program->Language->GetText(54))
#define MSGNOFILE (Program->Language->GetText(55))

static const textdef textdefs[] = {
    { 0, "#NORMALTEXT##BOLD##STARTMSG##NEWLINE##NORMALTEXT##COLOR02#Type help to show info.#NEWLINE#" }, /* INTROMSG */
    { 1, "------------------------------------------------------------#NEWLINE#" }, /* STATEMENTLINE */
    { 2, "about      Show about text#NEWLINE#" }, /* STATEMENTABOUT */
    { 3, "clear      Clear console window#NEWLINE#" }, /* STATEMENTCLEAR */
    { 4, "def        Define function#NEWLINE#" }, /* STATEMENTDEF */
    { 5, "delete     Delete variable or function#NEWLINE#" }, /* STATEMENTDELETE */
    { 6, "digits     Set number of significant digits#NEWLINE#" }, /* STATEMENTDIGITS */
    { 7, "eval       Evaluate arithmetic expression#NEWLINE#" }, /* STATEMENTEVAL */
    { 8, "execute    Execute statements in a file#NEWLINE#" }, /* STATEMENTEXECUTE */
    { 9, "functions  Show list of user defined functions#NEWLINE#" }, /* STATEMENTFUNCS */
    { 10, "input      Change numeral input system#NEWLINE#" }, /* STATEMENTINPUT */
    { 11, "help       Show basic help text#NEWLINE#" }, /* STATEMENTHELP */
    { 12, "output     Change numeral output system#NEWLINE#" }, /* STATEMENTOUTPUT */
    { 13, "list       Show content of a directory#NEWLINE#" }, /* STATEMENTLIST */
    { 14, "show       Show content of a file#NEWLINE#" }, /* STATEMENTSHOW */
    { 15, "load       Load variable and functions from file#NEWLINE#" }, /* STATEMENTLOAD */
    { 16, "save       Save variable and functions to file#NEWLINE#" }, /* STATEMENTSAVE */
    { 17, "variables  Show list of variables#NEWLINE#" }, /* STATEMENTVARS */
    { 18, "version    Show version string#NEWLINE#" }, /* STATEMENTVERSION */
    { 19, "license    Show copyright and license texts#NEWLINE#" }, /* STATEMENTLICENSE */
    { 20, "memory     Show internal memory usage#NEWLINE#" }, /* STATEMENTMEMORY */
    { 21, "exit       Exit program#NEWLINE#" }, /* STATEMENTEXIT */
    { 22, "The def and eval statements are optional. Functions and#NEWLINE#variables statements can be shorten to funcs and vars.#NEWLINE#" }, /* STATEMENTFOOTER */
    { 23, "Type        Name#NEWLINE#--------------------------------------------------#NEWLINE#" }, /* TXTLISTDIRHEADER */
    { 24, "[file]" }, /* TXTLISTDIRTFILE */
    { 25, "[dir]" }, /* TXTLISTDIRTDIR */
    { 26, "[unknown]" }, /* TXTLISTDIRTUNKNOWN */
    { 27, "Allocated blocks:#SPACE#" }, /* TXTMEMBLOCKS */
    { 28, "Memory usage:    #SPACE#" }, /* TXTMEMSIZE */
    { 29, "Maximum usage:   #SPACE#" }, /* TXTMEMMAXSIZE */
    { 30, "No help is available for this topic.#NEWLINE#" }, /* HELPNOHELP */
    { 31, "Syntax error:#SPACE#" }, /* HELPSYNTAX */
    { 32, "Unexpected error:#SPACE#" }, /* HELPUERROR */
    { 33, "Variable is not defined:#SPACE#" }, /* HELPVARNDEF */
    { 34, "Function is not defined:#SPACE#" }, /* HELPFUNNDEF */
    { 35, "Function cannot be redefined:#SPACE#" }, /* HELPFUNRDEF */
    { 36, "Base value must be between 2 and 32:#SPACE#" }, /* HELPPNUMERA */
    { 37, "Number of digist must be between 0 and 15:#SPACE#" }, /* HELPPDIGITS */
    { 38, "Numeral input system is#SPACE#" }, /* HELPINPUSHOW */
    { 39, "Numeral output system is#SPACE#" }, /* HELPOUTPSHOW */
    { 40, "Input changed to#SPACE#" }, /* HELPINPUSETT */
    { 41, "Output changed to#SPACE#" }, /* HELPOUTPSETT */
    { 42, "Number of digits changed to#SPACE#" }, /* HELPDIGISETT */
    { 43, "Number of digits shown are#SPACE#" }, /* HELPDIGISHOW */
    { 44, "No variables are defined.#NEWLINE#" }, /* HELPVARSNDEF */
    { 45, "No functions are defined.#NEWLINE#" }, /* HELPFUNCNDEF */
    { 46, "Variable and functions loaded from file.#NEWLINE#" }, /* HELPLOADSUCC */
    { 47, "Variable and functions saved to file.#NEWLINE#" }, /* HELPSAVESUCC */
    { 48, "Cannot save to file.#NEWLINE#" }, /* HELPSAVEFAIL */
    { 49, "Nothing to save.#NEWLINE#" }, /* HELPSAVENOTH */
    { 50, "Preferences loaded.#NEWLINE#" }, /* HELPPREFLOAD */
    { 51, "Preferences could not be loaded.#NEWLINE#" }, /* HELPPREFNOLO */
    { 52, "Preferences saved to disk.#NEWLINE#" }, /* HELPPREFSAVE */
    { 53, "Preferences could not be saved.#NEWLINE#" }, /* HELPPREFNOSA */
    { 54, "Could not open directory:#SPACE#" }, /* MSGNODIR */
    { 55, "Cannot open file.#NEWLINE#" }, /* MSGNOFILE */
    { -1, EMPTYSTRING }
};

#endif
