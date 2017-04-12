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

#include "amathc.h"
#include "lexer.h"
#include "token.h"
#include "symbol.h"
#include "loc/kword.h"
#include "operatordefs.h"
#include "system/program.h"

Lexer::Lexer(const char* input)
{
    AllocAndCopy(&this->input, input);
    pos = 0;
    str = this->input;
    first = nullptr;
    current = nullptr;
}

Lexer::~Lexer()
{
    delete [] input;

    if (first != nullptr)
    {
        delete first;
    }
}

char* Lexer::GetInput() const
{
    return input;
}

Token* Lexer::GetFirstToken() const
{
    return first;
}

void Lexer::Tokenize()
{
    pos = 0;
    str = input;
    first = nullptr;
    current = nullptr;

    GetNextToken();
    first = current;

    do
    {
        Token* last = current;
        GetNextToken();
        last->next = current;
    }
    while (current->symbol != symend);
}

void Lexer::GetNextToken()
{
    // Skip spaces and non visible characters
    while (*str != 0 && ShouldSkip(*str))
    {
        str++;
        if (Program->Language->CharIsSpace(*str))
        {
            pos++;
        }
    }

    if (*str == 0)
    {
        current = new Token(current, symend, pos);
        return;
    }

    if (GetOperator() || GetQuotedIdent() || GetDigitValue() || GetLitteral())
        return;

    str++;
    pos++;
    current = new Token(current, symunknown, pos - 1);
}

bool Lexer::GetOperator()
{
    static const unsigned int count = sizeof(operators) / sizeof(operatordef);
    for (unsigned int i = 0; i < count; i++)
    {
        if (operators[i].chr == *str)
        {
            current = new Token(current, operators[i].symbol, pos);
            str++;
            pos++;
            return true;
        }
    }

    return false;
}

bool Lexer::GetQuotedIdent()
{
    if (*str != '"')
    {
        return false;
    }

    char* start = str;
    const unsigned int startPos = pos;
    int unsigned len = 0;
    str++;

    while (*str != 0 && *str != '"' && !Program->Language->CharIsCntrl(*str))
    {
        str++;
        len++;
    }

    if (len == 0 || *str != '"')
    {
        str = start;
        return false;
    }

    char* ident = new char[len + 1];
    MemCopy(ident, start + 1, len);
    ident[len] = 0;

    current = new Token(current, symqident, ident, startPos);

    str++;
    pos += len + 1;

    delete [] ident;
    return true;
}

bool Lexer::GetLitteral()
{
    const char* start = str;
    const unsigned int startPos = pos;
    int unsigned len = 0;
    bool found = true;
    Symbol ksymbol;

    while (found)
    {
        if (Program->Language->CharIsAlpha(*str))
        {
            str++;
            len++;
        }
        else if (len != 0 && Program->Language->CharIsDigit(*str))
        {
            str++;
            len++;
        }
        else
        {
            found = false;
        }
    }

    if (len == 0)
    {
        return false;
    }

    char* ident = new char[len + 1];
    MemCopy(ident, start, len);
    ident[len] = 0;

    if ((ksymbol = FindKeyword(ident)))
    {
        current = new Token(current, ksymbol, startPos);
    }
    else
    {
        current = new Token(current, symident, ident, startPos);
    }

    pos += len;

    delete [] ident;
    return true;
}

bool Lexer::GetDigitValue()
{
    unsigned int len;
    char* end;

    // Only the numeral parser can determine if next token is a value
    Number* number = Program->Input->Parse(str, &len, &end);

    if (str == end)
    {
        delete number;
        return false;
    }

    char* text = new char[len + 1];
    MemCopy(text, str, len);
    *(text + len) = '\0';

    current = new Token(current, symnumber, text, pos);
    delete [] text;
    delete number;

    pos += len;
    str = end;
    return true;
}

Symbol Lexer::FindKeyword(const char* ident)
{
    return Program->Language->FindKeyword(ident);
}

char* Lexer::FindKeyword(Symbol symbol)
{
    static const unsigned int kwcount = sizeof(keywords) / sizeof(keyworddef);
    for (unsigned int i = 0; i < kwcount; i++)
    {
        if (keywords[i].symbol == symbol)
        {
            return const_cast<char*>(keywords[i].name);
        }
    }

    static const unsigned int ocount = sizeof(operators) / sizeof(operatordef);
    for (unsigned int i = 0; i < ocount; i++)
    {
        if (operators[i].symbol == symbol)
        {
            return const_cast<char*>(&(operators[i].chr));
        }
    }

    return nullptr;
}

bool Lexer::ShouldSkip(char character)
{
    if (character == '\n')
    {
        return false;
    }

    if (Program->Language->CharIsCntrl(character))
    {
        return true;
    }

    if (Program->Language->CharIsSpace(character))
    {
        return true;
    }

    return false;
}
