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

#ifndef AMATH_FUNCTIONS_H
#define AMATH_FUNCTIONS_H

/**
 * @file  functions.h
 * @brief Application logic tied to functions.
 *
 */

#include "main/nodes.h"
#include "function/node.h"

class HyperbolicSineNode : public FunctionNode
{
public:
    explicit HyperbolicSineNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicCosineNode : public FunctionNode
{
public:
    explicit HyperbolicCosineNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicTangentNode : public FunctionNode
{
public:
    explicit HyperbolicTangentNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicCotangentNode : public FunctionNode
{
public:
    explicit HyperbolicCotangentNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicSecantNode : public FunctionNode
{
public:
    explicit HyperbolicSecantNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicCosecantNode : public FunctionNode
{
public:
    explicit HyperbolicCosecantNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArccosineNode : public FunctionNode
{
public:
    explicit HyperbolicArccosineNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArcsineNode : public FunctionNode
{
public:
    explicit HyperbolicArcsineNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArctangentNode : public FunctionNode
{
public:
    explicit HyperbolicArctangentNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArcCotangentNode : public FunctionNode
{
public:
    explicit HyperbolicArcCotangentNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArcCosecantNode : public FunctionNode
{
public:
    explicit HyperbolicArcCosecantNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

class HyperbolicArcSecantNode : public FunctionNode
{
public:
    explicit HyperbolicArcSecantNode(ExpressionNode* expression, char* text, char* sys);
    static FunctionNode* Create(ExpressionNode* expression, char* text, char* sys);
    Number* Evaluate();
};

#endif
