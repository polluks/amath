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

#ifndef AMATH_PARSER_H
#define AMATH_PARSER_H

/**
 * @file  parser.h
 * @brief Application logic tied to Parser.
 *
 */

#include "nodes.h"
#include "lexer.h"

/**
 * @brief Encapsulates a recursive descent parser.
 * @details
 * More info on recursive descent parsers is available at Wikipedia:
 * https://wikipedia.org/wiki/Recursive_descent_parser
 *
 */
class Parser
{
public:
    explicit Parser(const char* input);
    ~Parser();

    /**
     * @brief Parses the input into a syntax tree.
     *
     * @return SyntaxNode* representing a pointer to the top node of the tree.
     *         Notice: The caller is responsible for releasing memory.
     *
     */
    SyntaxNode* Parse(); // Clang ns_returns_retained

private:
    Lexer* lexer;
    Token* token;

    int syntaxError;
    ErrorNode* errorNode;

    SyntaxNode* ParseDefault();
    SyntaxNode* TryParseStatement();
    SyntaxNode* ParseStatement();
    SyntaxNode* ParseEvaluation();
    ExpressionNode* ParseExpression();
    ExpressionNode* ParseAddSubstract();
    ExpressionNode* ParseFactor();
    ExpressionNode* ParsePower();
    ExpressionNode* ParseUnary();
    ExpressionNode* ParseAtomic();
    ExpressionNode* ParseIdent();
    ExpressionNode* ParseNumber();

    SyntaxNode* ParseFunctionDef();
    SyntaxNode* ParseHelpStatement();
    SyntaxNode* ParseDeleteStatement();
    SyntaxNode* ParseListStatement();
    SyntaxNode* ParseFileStatement();
    SyntaxNode* ParseNumeralStatement();
    SyntaxNode* ParseDigistStatement();
    SyntaxNode* ParseDrawStatement();
    SyntaxNode* ParsePromptStatement();
    SyntaxNode* ParsePrefsStatement();

    void GetToken();
    void PutToken();
    bool Expect(Symbol symbol);
    Token* Peek() const;
};

#endif
