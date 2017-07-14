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
 * https://amath.innolan.net
 * 
 */

#include "amathc.h"
#include "main/token.h"

#if __GNUC__ > 2
#pragma GCC diagnostic ignored "-Wshadow"
#endif

Token::Token(Token* last, Symbol symbol, int pos)
{
    this->last = last;
    this->symbol = symbol;
    this->pos = pos;
    this->text = nullptr;
    this->next = nullptr;
}

Token::Token(Token* last, Symbol symbol, const char* text, int pos)
{
    this->last = last;
    this->symbol = symbol;
    this->pos = pos;
    this->next = nullptr;
    AllocAndCopy(&this->text, text);
}

Token::~Token()
{
    if (text != nullptr)
    {
        delete [] text;
    }

    if (next != nullptr)
    {
        delete next;
    }
}

Token* Token::GetLastToken() const
{
    return last;
}

Token* Token::GetNextToken()
{
    // Always return a token if requested
    if (next == nullptr)
    {
        next = new Token(this, symend, pos);
    }

    return next;
}

char* Token::GetText() const
{
    return text;
}

int Token::GetPos() const
{
    return pos;
}
