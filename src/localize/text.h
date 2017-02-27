/*
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
 */

#ifndef AMATH_LOCALIZE_TEXT_H
#define AMATH_LOCALIZE_TEXT_H

/**
 * @file  text.h
 * @brief Static texts in amath.
 *
 */

#include "main.h"
#include "amath.h"
#include "amathc.h"
#include "amatht.h"
#include "system/program.h"

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

static const textdef textdefs[] = {
    {0, "#NORMALTEXT##BOLD##STARTMSG##NEWLINE##NORMALTEXT##COLOR02#Type help to show info.#NEWLINE#"}, /* INTROMSG */
    {1, "Type        Name#NEWLINE#-----------------------------------------------#NEWLINE#"}, /* TXTLISTDIRHEADER */
    {2, "[file]"}, /* TXTLISTDIRTFILE */
    {3, "[dir]"}, /* TXTLISTDIRTDIR */
    {4, "[unknown]"}, /* TXTLISTDIRTUNKNOWN */
    {5, "Allocated blocks:#SPACE#"}, /* TXTMEMBLOCKS */
    {6, "Memory usage:    #SPACE#"}, /* TXTMEMSIZE */
    {7, "Maximum usage:   #SPACE#"}, /* TXTMEMMAXSIZE */
    {8, "No help is available for this topic.#NEWLINE#"}, /* HELPNOHELP */
    {9, "Syntax error:#SPACE#"}, /* HELPSYNTAX */
    {10, "Unexpected error:#SPACE#"}, /* HELPUERROR */
    {11, "Variable is not defined:#SPACE#"}, /* HELPVARNDEF */
    {12, "Function is not defined:#SPACE#"}, /* HELPFUNNDEF */
    {13, "Function cannot be redefined:#SPACE#"}, /* HELPFUNRDEF */
    {14, "Base value must be between 2 and 32:#SPACE#"}, /* HELPPNUMERA */
    {15, "Number of digist must be between 0 and 15:#SPACE#"}, /* HELPPDIGITS */
    {16, "Numeral input system is#SPACE#"}, /* HELPINPUSHOW */
    {17, "Numeral output system is#SPACE#"}, /* HELPOUTPSHOW */
    {18, "Input changed to#SPACE#"}, /* HELPINPUSETT */
    {19, "Output changed to#SPACE#"}, /* HELPOUTPSETT */
    {20, "Number of digits changed to#SPACE#"}, /* HELPDIGISETT */
    {21, "Number of digits shown are#SPACE#"}, /* HELPDIGISHOW */
    {22, "No variables are defined.#NEWLINE#"}, /* HELPVARSNDEF */
    {23, "No functions are defined.#NEWLINE#"}, /* HELPFUNCNDEF */
    {24, "Variable and functions loaded from file.#NEWLINE#"}, /* HELPLOADSUCC */
    {25, "Variable and functions saved to file.#NEWLINE#"}, /* HELPSAVESUCC */
    {26, "Cannot save to file.#NEWLINE#"}, /* HELPSAVEFAIL */
    {27, "Nothing to save.#NEWLINE#"}, /* HELPSAVENOTH */
    {28, "Preferences loaded.#NEWLINE#"}, /* HELPPREFLOAD */
    {29, "Preferences could not be loaded.#NEWLINE#"}, /* HELPPREFNOLO */
    {30, "Preferences saved to disk.#NEWLINE#"}, /* HELPPREFSAVE */
    {31, "Preferences could not be saved.#NEWLINE#"}, /* HELPPREFNOSA */
    {32, "Could not open directory:#SPACE#"}, /* MSGNODIR */
    {33, "Cannot open file.#NEWLINE#"}, /* MSGNOFILE */
    {-1, EMPTYSTRING}
};

#endif
