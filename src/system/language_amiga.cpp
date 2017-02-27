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
 */

#include "amath.h"
#include "amathc.h"
#include "localize/lex.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/ident.h"
#include "localize/kword.h"
#include "localize/tags.h"
#include "system/program.h"
#include "system/language_amiga.h"

#ifdef AMIGA
#include <clib/locale_protos.h>

AmigaLanguage::AmigaLanguage() :
    Language::Language()
{
    locale = OpenLocale(NULL);
    helpcatalog    = OpenCatalog(locale, CATALOG_HELP, CATALOG_DEF, TAG_DONE);
    identcatalog   = OpenCatalog(locale, CATALOG_IDEN, CATALOG_DEF, TAG_DONE);
    textcatalog    = OpenCatalog(locale, CATALOG_TEXT, CATALOG_DEF, TAG_DONE);
    keywordcatalog = OpenCatalog(locale, CATALOG_KEYW, CATALOG_DEF, TAG_DONE);

    if (keywordcatalog != NULL) {
        keywordsloc = new keyworddef[keywordcount];
        for (unsigned int j = 0; j < keywordcount; j++) {
            keywordsloc[j].id = j;
            keywordsloc[j].name = GetCatalogStr(keywordcatalog, j, NULL);
            keywordsloc[j].symbol = keywords[j].symbol;
        }
    }
}

AmigaLanguage::~AmigaLanguage()
{
    if (helpcatalog != NULL) {
        CloseCatalog(helpcatalog);
    }

    if (identcatalog != NULL) {
        CloseCatalog(identcatalog);
    }

    if (textcatalog != NULL) {
        CloseCatalog(textcatalog);
    }

    if (keywordcatalog != NULL) {
        CloseCatalog(keywordcatalog);
    }

    if (locale != NULL) {
        CloseLocale(locale);
    }
}

char* AmigaLanguage::Translate(textdef *def)
{
    return (char*)GetCatalogStr(textcatalog, def->id, (char*)def->text);
}

char* AmigaLanguage::Translate(helptextdef *def)
{
    return (char*)GetCatalogStr(helpcatalog, def->id, (char*)def->text);
}

char* AmigaLanguage::Translate(identhelpdef *def)
{
    return (char*)GetCatalogStr(identcatalog, def->id, (char*)def->text);
}

char AmigaLanguage::GetFractionPoint()
{
    return locale->loc_DecimalPoint[0];
}

bool AmigaLanguage::CharIsAlNum(long unsigned int character)
{
    return IsAlNum(locale, character);
}

bool AmigaLanguage::CharIsAlpha(long unsigned int character)
{
    return IsAlpha(locale, character);
}

bool AmigaLanguage::CharIsDigit(long unsigned int character)
{
    return IsDigit(locale, character);
}

bool AmigaLanguage::CharIsPunct(long unsigned int character)
{
    return IsPunct(locale, character);
}

bool AmigaLanguage::CharIsSpace(long unsigned int character)
{
    return IsSpace(locale, character);
}

bool AmigaLanguage::CharIsCntrl(long unsigned int character)
{
    return IsCntrl(locale, character);
}

bool AmigaLanguage::StrIsEqualLoc(const char* s1, const char* s2)
{
    return (StrnCmp(locale, (char*)s1, (char*)s2, -1, SC_COLLATE1) == 0);
}

bool AmigaLanguage::Validate(char c)
{
    return CharIsAlNum(c) ||
           CharIsPunct(c) ||
           CharIsSpace(c) ||
           CharIsQuote(c) ||
           CharIsOperator(c);
}

/* for numeric values */
//STRPTR  loc_DecimalPoint;        /* character before the decimals */
//STRPTR  loc_GroupSeparator;      /* separates groups of digits    */
//STRPTR  loc_FracGroupSeparator;  /* separates groups of digits    */
//UBYTE  *loc_Grouping;            /* size of each group            */
//UBYTE  *loc_FracGrouping;        /* size of each group            */

/* elements of the byte arrays pointed to by:
 *   Locale.loc_Grouping
 *   Locale.loc_FracGrouping
 * are interpreted as follows:
 *
 *    255     indicates that no further grouping is to be performed
 *    0       indicates that the previous element is to be repeatedly used
 *	      for the remainder of the digits
 *    <other> the number of digits that comprises the current group
 */


//LIBRARIES_LOCALE_H
/* constants for GetLocaleStr() */
//#define SOFTHYPHEN	43	/* soft hyphenation */
//#define HARDHYPHEN	44	/* hard hyphenation */
//#define OPENQUOTE	45	/* start of quoted block */
//#define CLOSEQUOTE	46	/* end of quoted block	 */

#endif

