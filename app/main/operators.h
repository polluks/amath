/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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

#ifndef _OPERATORS_H
#define _OPERATORS_H

/**
 * @file  operators.h
 * @brief Application logic tied to arithmetic operators.
 *
 */

#include "main/nodes.h"
#include "main/values.h"

class UnaryNode : virtual public ExpressionNode {
public:
    UnaryNode(ExpressionNode* expression);
    ~UnaryNode();

    ReductionType GetReductionType();
    int GetPrecedence();
    SyntaxNode* GetNext();
    char* GetText();
    Number* Evaluate();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    char* GetNodeText();

private:
    ExpressionNode* expression;
};

class AbsoluteNode : virtual public ExpressionNode {
public:
    AbsoluteNode(ExpressionNode* expression);
    ~AbsoluteNode();

    char* GetText();
    Number* Evaluate();
    int GetPrecedence();
    SyntaxNode* GetNext();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    char* GetNodeText();

private:
    ExpressionNode* expression;
};

class NumericOperator : virtual public ExpressionNode {
public:
    NumericOperator(ExpressionNode* left, ExpressionNode* right);
    ~NumericOperator();

    SyntaxNode* GetNext();
    char* GetText();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    ExpressionNode* left;
    ExpressionNode* right;
};

class AdditionNode : public NumericOperator {
public:
    AdditionNode(ExpressionNode* left, ExpressionNode* right);
    ReductionType GetReductionType();
    int GetPrecedence();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class SubtractionNode : public NumericOperator {
public:
    SubtractionNode(ExpressionNode* left, ExpressionNode* right);
    ReductionType GetReductionType();
    int GetPrecedence();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class MultiplicationNode : public NumericOperator {
public:
    MultiplicationNode(ExpressionNode* left, ExpressionNode* right);
    int GetPrecedence();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class DivisionNode : public NumericOperator {
public:
    DivisionNode(ExpressionNode* left, ExpressionNode* right);
    int GetPrecedence();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class PowerNode : public NumericOperator {
public:
    PowerNode(ExpressionNode* left, ExpressionNode* right);
    int GetPrecedence();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class AssignmentNode : public NumericOperator {
public:
    AssignmentNode(VariableNode* variable, ExpressionNode* expression);
    int GetPrecedence();
    bool IsSilent();
    Number* Evaluate();

protected:
    char* GetNodeText();

private:
    VariableNode* variable;
    ExpressionNode* expression;
};

#endif
