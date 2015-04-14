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
#include "system/language_stdc.h"

StandardLanguage::StandardLanguage() :
    Language()
{
    LoadCatalogs();
}

StandardLanguage::~StandardLanguage()
{
    if (textbase != NOMEM) {
        delete textbase;
    }

    if (helpbase != NOMEM) {
        delete helpbase;
    }

    if (identbase != NOMEM) {
        delete identbase;
    }

    if (kwordbase != NOMEM) {
        delete kwordbase;
    }

}

char* StandardLanguage::Translate(textdef* def)
{
    return textcatalog == NOMEM ?
           (char*)def->text :
           (char*)textcatalog[def->id].text;
}

char* StandardLanguage::Translate(helptextdef* def)
{
    return helpcatalog == NOMEM ?
           (char*)def->text :
           (char*)helpcatalog[def->id].text;
}

char* StandardLanguage::Translate(identhelpdef* def)
{
    return identcatalog == NOMEM ?
           (char*)def->text :
           (char*)identcatalog[def->id].text;
}

char StandardLanguage::GetFractionPoint()
{
    return '.';
}

bool StandardLanguage::CharIsAlNum(long unsigned int character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9');
}

bool StandardLanguage::CharIsAlpha(long unsigned int character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z');
}

bool StandardLanguage::CharIsDigit(long unsigned int character)
{
    return (character >= '0' && character <= '9');
}

bool StandardLanguage::CharIsPunct(long unsigned int character)
{
    return (character == '.');
}

bool StandardLanguage::CharIsSpace(long unsigned int character)
{
    return (character == 32);
}

bool StandardLanguage::CharIsCntrl(long unsigned int character)
{
    return (character < 32 || character > 125);
}

bool StandardLanguage::StrIsEqualLoc(const char* s1, const char* s2)
{
    return StrIsEqual(s1, s2);
}


void StandardLanguage::LoadCatalogs()
{
    const char* key;
    const char* value;

    LoadCatalog(&textbase, "utext/dk-text.dict");
    if (textbase != NOMEM) {
        textcatalog = new textdef[textcount];
        for (unsigned int j = 0; j < textcount; j++) {
            GetNextPair(&key, &value);
            textcatalog[j].id = j;
            textcatalog[j].text = value;
        }
    }

    LoadCatalog(&helpbase, "utext/dk-help.dict");
    if (helpbase != NOMEM) {
        helpcatalog = new helptextdef[helpcount];
        for (unsigned int j = 0; j < helpcount; j++) {
            GetNextPair(&key, &value);
            helpcatalog[j].id = j;
            helpcatalog[j].symbol = helptexts[j].symbol;
            helpcatalog[j].text = value;
        }
    }

    LoadCatalog(&identbase, "utext/dk-ident.dict");
    if (identbase != NOMEM) {
        identcatalog = new identhelpdef[identcount];
        for (unsigned int j = 0; j < identcount; j++) {
            GetNextPair(&key, &value);
            identcatalog[j].id = j;
            identcatalog[j].ident = key;
            identcatalog[j].text = value;
        }
    }

    LoadCatalog(&kwordbase, "utext/dk-keyword.dict");
    if (kwordbase != NOMEM) {
        keywordsloc = new keyworddef[keywordcount];
        for (unsigned int j = 0; j < keywordcount; j++) {
            GetNextPair(&key, &value);
            keywordsloc[j].id = j;
            keywordsloc[j].name = value;
            keywordsloc[j].symbol = keywords[j].symbol;
        }
    }
}

void StandardLanguage::LoadCatalog(char **dest, const char *file)
{
    FilesystemBase *filesystem = CreateFilesystem();
    CharBuffer *cbuf = filesystem->LoadTextFile(file);

    if (cbuf != NOMEM) {
        AllocAndCopy(dest, cbuf->GetString());
        ptr = *dest;
        delete cbuf;
    } else {
        *dest = NOMEM;
    }

    delete filesystem;
}

void StandardLanguage::GetNextPair(const char **key, const char **value)
{
    SkipComments();
    *key = ptr;
    GetNextLine();
    SkipComments();
    *value = ptr;
    GetNextLine();
}

void StandardLanguage::GetNextLine()
{
    while ((*ptr) != '\0' && (*ptr) != '\n') {
        ptr++;
    }

    if ((*ptr) == '\n') {
        *ptr++ = '\0';
    }
}

void StandardLanguage::SkipComments()
{
    bool skipping;
    do {
        if ((*ptr) == ';') {
            GetNextLine();
            skipping = true;
        } else if ((*ptr) == '#' && *(ptr + sizeof(char)) == '#') {
            GetNextLine();
            skipping = true;
        } else {
            skipping = false;
        }
    } while (skipping);
}
