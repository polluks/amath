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

#ifndef _LANGUAGE_BASE_H
#define _LANGUAGE_BASE_H

#include "localize/lex.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/ident.h"
#include "localize/kword.h"

class Language {
public:
    Language();
    virtual ~Language();
    char* GetText(int id);
    char* GetHelpText(char *ident);
    char* GetHelpText(Symbol symbol);
    Symbol FindKeyword(const char *ident);
    virtual char GetFractionPoint() = 0;
    virtual bool CharIsAlNum(unsigned long character) = 0;
    virtual bool CharIsAlpha(unsigned long character) = 0;
    virtual bool CharIsDigit(unsigned long character) = 0;
    virtual bool CharIsPunct(unsigned long character) = 0;
    virtual bool CharIsSpace(unsigned long character) = 0;
    virtual bool CharIsCntrl(unsigned long character) = 0;
    virtual bool StrIsEqualLoc(const char *s1, const char *s2) = 0;

protected:
    virtual char* Translate(textdef *def) = 0;
    virtual char* Translate(helptextdef *def) = 0;
    virtual char* Translate(identhelpdef *def) = 0;

    keyworddef *keywordsloc;
    unsigned int keywordcount;
    unsigned int textcount;
    unsigned int identcount;
    unsigned int helpcount;
    unsigned int aliascount;

private:
    char* FindAlias(const char *ident);
    char* UntagText(const char *text);
    char* lastText;
};

#endif
