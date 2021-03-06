/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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

#ifndef AMATH_LEXER_H
#define AMATH_LEXER_H

/**
 * @file  lexer.h
 * @brief Application logic tied to Lexer.
 *
 */

#include "token.h"

/**
 * @brief Encapsulates an lexical analyzer. Provides token for the parser.
 * @details
 * More info on lexical analysis is available at Wikipedia:
 * https://wikipedia.org/wiki/Lexical_analysis
 *
 */
class Lexer
{
public:
    explicit Lexer(const char* input);
    ~Lexer();

    void Tokenize();
    Token* GetFirstToken() const;
    char* GetInput() const;
    static char* FindKeyword(Symbol symbol);

private:
    char* input; // Input to process by lexer
    char* str; // Pointer to char being processed
    unsigned int pos;
    Token* first;
    Token* current;

    void GetNextToken();
    bool GetOperator();
    bool GetQuotedIdent();
    bool GetLiteral();
    bool GetDigitValue();
    static bool ShouldSkip(char character);
    static Symbol FindKeyword(const char* ident);
};

#endif
