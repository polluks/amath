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

#ifndef AMATH_LOCALIZE_TEXT_H
#define AMATH_LOCALIZE_TEXT_H

/**
 * @file  text.h
 * @brief Localized text definitions.
 *
 */

#include "clib.h"

#define INTROMSG Program->Language->GetText(0)
#define TXTLISTDIRHEADER Program->Language->GetText(1)
#define TXTLISTDIRTFILE Program->Language->GetText(2)
#define TXTLISTDIRTDIR Program->Language->GetText(3)
#define TXTLISTDIRTUNKNOWN Program->Language->GetText(4)
#define TXTMEMBLOCKS Program->Language->GetText(5)
#define TXTMEMSIZE Program->Language->GetText(6)
#define TXTMEMMAXSIZE Program->Language->GetText(7)
#define HELPNOHELP Program->Language->GetText(8)
#define HELPSYNTAX Program->Language->GetText(9)
#define HELPUERROR Program->Language->GetText(10)
#define HELPVARNDEF Program->Language->GetText(11)
#define HELPFUNNDEF Program->Language->GetText(12)
#define HELPFUNRDEF Program->Language->GetText(13)
#define HELPPNUMERA Program->Language->GetText(14)
#define HELPPDIGITS Program->Language->GetText(15)
#define HELPINPUSHOW Program->Language->GetText(16)
#define HELPOUTPSHOW Program->Language->GetText(17)
#define HELPINPUSETT Program->Language->GetText(18)
#define HELPOUTPSETT Program->Language->GetText(19)
#define HELPDIGISETT Program->Language->GetText(20)
#define HELPDIGISHOW Program->Language->GetText(21)
#define HELPVARSNDEF Program->Language->GetText(22)
#define HELPFUNCNDEF Program->Language->GetText(23)
#define HELPLOADSUCC Program->Language->GetText(24)
#define HELPSAVESUCC Program->Language->GetText(25)
#define HELPSAVEFAIL Program->Language->GetText(26)
#define HELPSAVENOTH Program->Language->GetText(27)
#define HELPPREFLOAD Program->Language->GetText(28)
#define HELPPREFNOLO Program->Language->GetText(29)
#define HELPPREFSAVE Program->Language->GetText(30)
#define HELPPREFNOSA Program->Language->GetText(31)
#define MSGNODIR Program->Language->GetText(32)
#define MSGNOFILE Program->Language->GetText(33)

struct textdef {
    int id;
    const char *key;
    const char *text;
};

static const textdef textdefs[] = {
    { 0, "INTROMSG", "#NORMALTEXT##BOLD##STARTMSG##NEWLINE##NORMALTEXT##COLOR02##ITALICS#Type help to show info.#NEWLINE#" },
    { 1, "TXTLISTDIRHEADER", "Type        Name#NEWLINE#-----------------------------------------------#NEWLINE#" },
    { 2, "TXTLISTDIRTFILE", "[file]" },
    { 3, "TXTLISTDIRTDIR", "[dir]" },
    { 4, "TXTLISTDIRTUNKNOWN", "[unknown]" },
    { 5, "TXTMEMBLOCKS", "Allocated blocks:#SPACE#" },
    { 6, "TXTMEMSIZE", "Memory usage:    #SPACE#" },
    { 7, "TXTMEMMAXSIZE", "Maximum usage:   #SPACE#" },
    { 8, "HELPNOHELP", "No help is available for this topic.#NEWLINE#" },
    { 9, "HELPSYNTAX", "Syntax error:#SPACE#" },
    { 10, "HELPUERROR", "Unexpected error:#SPACE#" },
    { 11, "HELPVARNDEF", "Variable is not defined:#SPACE#" },
    { 12, "HELPFUNNDEF", "Function is not defined:#SPACE#" },
    { 13, "HELPFUNRDEF", "Function cannot be redefined:#SPACE#" },
    { 14, "HELPPNUMERA", "Base value must be between 2 and 32:#SPACE#" },
    { 15, "HELPPDIGITS", "Number of digist must be between 0 and 15:#SPACE#" },
    { 16, "HELPINPUSHOW", "Numeral input system is#SPACE#" },
    { 17, "HELPOUTPSHOW", "Numeral output system is#SPACE#" },
    { 18, "HELPINPUSETT", "Input changed to#SPACE#" },
    { 19, "HELPOUTPSETT", "Output changed to#SPACE#" },
    { 20, "HELPDIGISETT", "Number of digits changed to#SPACE#" },
    { 21, "HELPDIGISHOW", "Number of digits shown are#SPACE#" },
    { 22, "HELPVARSNDEF", "No variables are defined.#NEWLINE#" },
    { 23, "HELPFUNCNDEF", "No functions are defined.#NEWLINE#" },
    { 24, "HELPLOADSUCC", "Variable and functions loaded from file.#NEWLINE#" },
    { 25, "HELPSAVESUCC", "Variable and functions saved to file.#NEWLINE#" },
    { 26, "HELPSAVEFAIL", "Cannot save to file.#NEWLINE#" },
    { 27, "HELPSAVENOTH", "Nothing to save.#NEWLINE#" },
    { 28, "HELPPREFLOAD", "Preferences loaded.#NEWLINE#" },
    { 29, "HELPPREFNOLO", "Preferences could not be loaded.#NEWLINE#" },
    { 30, "HELPPREFSAVE", "Preferences saved to disk.#NEWLINE#" },
    { 31, "HELPPREFNOSA", "Preferences could not be saved.#NEWLINE#" },
    { 32, "MSGNODIR", "Could not open directory:#SPACE#" },
    { 33, "MSGNOFILE", "Cannot open file.#NEWLINE#" },
    { -1, EMPTYSTRING, EMPTYSTRING }
};

#endif
