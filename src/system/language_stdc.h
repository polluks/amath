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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#ifndef AMATH_LANGUAGE_STANDARD_H
#define AMATH_LANGUAGE_STANDARD_H

#include "amath.h"
#include "amathc.h"
#include "language.h"
#include "localize/help.h"
#include "localize/text.h"

#if !defined(AMIGA)

class StandardLanguage : public Language
{
public:
    StandardLanguage();
    ~StandardLanguage();
    char GetFractionPoint();
    bool CharIsAlNum(unsigned long character);
    bool CharIsAlpha(unsigned long character);
    bool CharIsDigit(unsigned long character);
    bool CharIsPunct(unsigned long character);
    bool CharIsSpace(unsigned long character);
    bool CharIsCntrl(unsigned long character);
    bool StrIsEqualLoc(const char* s1, const char* s2);
    bool Validate(char c);

protected:
    char* Translate(textdef* def);
    char* Translate(helptextdef* def);
    char* Translate(identhelpdef* def);

private:
    void LoadCatalogs();
    void LoadCatalog(char** dest, const char* file);
    void GetNextPair(const char** key, const char** value);
    void GetNextLine();
    void SkipComments();

    char* textbase;
    char* helpbase;
    char* identbase;
    char* kwordbase;

    char* ptr;
    textdef* textcatalog;
    helptextdef* helpcatalog;
    identhelpdef* identcatalog;
};

#endif

#endif
