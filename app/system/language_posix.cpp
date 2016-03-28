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

#include "clib.h"
#include "localize/lex.h"
#include "localize/tags.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/ident.h"
#include "localize/kword.h"
#include "system/base/io.h"
#include "system/program.h"
#include "system/language_posix.h"

#ifdef UNIX
#include <stdio.h>
#include <ctype.h>     /*  http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/ctype.h.html   */
#include <locale.h>    /*  http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/locale.h.html  */
#include <nl_types.h>  /*  http://pubs.opengroup.org/onlinepubs/7908799/xsh/nl_types.h.html        */
#include <string.h>

PosixLanguage::PosixLanguage() :
    Language()
{
//    locale = newlocale(LC_ALL, "da_DK.ISO8859-15", (locale_t)0);
//    setlocale(LC_NUMERIC, "da_DK.ISO8859-15");
    locale = newlocale(LC_ALL, "", (locale_t)0);
    setlocale(LC_NUMERIC, "");
    conv = localeconv();
}

PosixLanguage::~PosixLanguage()
{
    freelocale(locale);
}

bool PosixLanguage::CharIsAlNum(long unsigned int character)
{
    return (bool)isalnum_l((int)character, locale);
}

bool PosixLanguage::CharIsAlpha(long unsigned int character)
{
    return (bool)isalpha_l((int)character, locale);
}

bool PosixLanguage::CharIsCntrl(long unsigned int character)
{
    return (bool)iscntrl_l((int)character, locale);
}

bool PosixLanguage::CharIsDigit(long unsigned int character)
{
    return (bool)isdigit_l((int)character, locale);
}

bool PosixLanguage::CharIsPunct(long unsigned int character)
{
    return (bool)ispunct_l((int)character, locale);
}

bool PosixLanguage::CharIsSpace(long unsigned int character)
{
    return (bool)isspace_l((int)character, locale);
}

char PosixLanguage::GetFractionPoint()
{
    return *(conv->decimal_point);
}

bool PosixLanguage::StrIsEqualLoc(const char* s1, const char* s2)
{
    size_t len = StrLen(s2) * 2;
    char *tmp = new char[len];
    strxfrm(tmp, s2, len);
    bool res = StrIsEqual(s1, tmp);
    delete tmp;
    return res;
}

char* PosixLanguage::Translate(identhelpdef* def)
{
    return (char*)def->text;
}

char* PosixLanguage::Translate(helptextdef* def)
{
    return (char*)def->text;
}

char* PosixLanguage::Translate(textdef* def)
{
    return (char*)def->text;
}

#endif
