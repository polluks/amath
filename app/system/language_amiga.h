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
 */

#ifndef _LANGUAGE_AMIGA_H
#define _LANGUAGE_AMIGA_H

#include "localize/lex.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/kword.h"
#include "system/language.h"

class AmigaLanguage : public Language {
public:
    AmigaLanguage();
    ~AmigaLanguage();
    char GetFractionPoint();
    bool CharIsAlNum(unsigned long character);
    bool CharIsAlpha(unsigned long character);
    bool CharIsDigit(unsigned long character);
    bool CharIsPunct(unsigned long character);
    bool CharIsSpace(unsigned long character);
    bool CharIsCntrl(unsigned long character);
    bool StrIsEqualLoc(const char *s1, const char *s2);

protected:
    char* Translate(textdef *def);
    char* Translate(helptextdef *def);
    char* Translate(identhelpdef *def);

private:
    struct Locale* locale;
    struct Catalog *helpcatalog;
    struct Catalog *identcatalog;
    struct Catalog *textcatalog;
    struct Catalog *keywordcatalog;
};

#endif
