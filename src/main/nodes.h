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

#ifndef AMATH_NODES_H
#define AMATH_NODES_H

/**
 * @file  nodes.h
 * @brief Top nodes in syntax trees.
 *
 */

#include "lib/numb.h"
#include "lib/charbuf.h"

typedef enum
{
    othernodetype,
    statement,
    expression
} NodeType;

typedef enum
{
    nonereduc,
    unaryreduc,
    valuereduc,
    compladdreduc,
    complsubreduc
} ReductionType;

/**
* @brief Base class for all nodes in a syntax tree.
* @details
* More info is available at Wikipedia:
* https://wikipedia.org/wiki/Abstract_syntax_tree
*
*/
class SyntaxNode
{
public:
    SyntaxNode();
    virtual ~SyntaxNode();
    void SetFirstNode();
    bool GetFirstNode() const;
    SyntaxNode* GetParent() const;
    void SetParent(SyntaxNode* node);
    virtual NodeType GetNodeType() = 0;
    virtual ReductionType GetReductionType();
    virtual void ResetIterator();
    virtual SyntaxNode* GetNext() = 0;
    virtual char* GetTextCode() = 0;
    virtual char* Execute() = 0;
    virtual void Attach(SyntaxNode* node) = 0;
    virtual void Detach(SyntaxNode* node) = 0;
    virtual void Replace(SyntaxNode* n, SyntaxNode* x) = 0;

protected:
    CharBuffer* output;
    SyntaxNode* parent;
    SyntaxNode* iterator;
    bool leftBottom;
};

/**
* @brief Base class for all nodes related to mathematical expressions.
* @details
* Nodes of this type is used to build trees representing an mathematical
* expressions. Each node in the tree consist of a number, an operator or
* any other element in an expression.
*
*/
class ExpressionNode : public SyntaxNode
{
public:
    ExpressionNode();
    explicit ExpressionNode(Number* value);
    virtual ~ExpressionNode();

    NodeType GetNodeType();
    virtual bool IsSilent();
    virtual char* GetText() = 0;
    virtual Number* Evaluate() = 0;
    virtual int GetPrecedence() = 0;
    char* GetTextCode();
    char* Execute();

protected:
    virtual char* GetNodeText() = 0;
    Number* result;
};

/**
* @brief Represents an error message encapsulated in a syntax tree.
*
*/
class ErrorNode : public virtual SyntaxNode
{
public:
    ErrorNode(const char* input, int pos);
    ErrorNode(const char* input, const char* message, const char* parameter, int pos);
    virtual ~ErrorNode();

    NodeType GetNodeType();
    SyntaxNode* GetNext();
    char* GetTextCode();
    char* Execute();
    void Attach(SyntaxNode* node);
    void Detach(SyntaxNode* node);
    void Replace(SyntaxNode* n, SyntaxNode* x);

private:
    static void StrCopyVisible(char* destination, const char* source);
    char* message;
    char* input;
    int pos;
};

struct StatementBlockElement;

/**
* @brief A sequence of statements in a syntax tree.
*
*/
class StatementBlockNode : public virtual SyntaxNode
{
public:
    StatementBlockNode();
    ~StatementBlockNode();

    NodeType GetNodeType();
    SyntaxNode* GetNext();
    void Add(SyntaxNode* node);
    char* GetTextCode();
    char* Execute();
    void Attach(SyntaxNode* node);
    void Detach(SyntaxNode* node);
    void Replace(SyntaxNode* n, SyntaxNode* x);

private:
    StatementBlockElement* first;
};

/**
* @brief Used to create a linked list of statements.
*
*/
struct StatementBlockElement
{
    SyntaxNode* statement;
    StatementBlockElement* next;
};

#endif
