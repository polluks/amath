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

#ifndef _VALUES_H
#define _VALUES_H

/**
 * @file  values.h
 * @brief Application logic tied to numbers and values.
 *
 */

#include "clib.h"
#include "lib/numb.h"
#include "main/nodes.h"

class Variable;

/**
 * @brief A list of user defined variables.
 *
 */
class VariableList {
public:
    VariableList();
    ~VariableList();

    void Clear();
    bool Delete(const char *name);
    Variable* GetFirstVariable();
    Variable* GetVariable(const char *name);
    Variable* CreateVariable(const char *name);
    Variable* InsertTemporaryVariable(Variable *variable);
    void RemoveTemporaryVariable();

    char* List();
    char* ListDefinitions();

private:
    char* ListContent(bool cmdFormat);
    CharBuffer *buf;
    Variable *first;
};

/**
 * @brief A user defined variable.
 *
 */
class Variable {
public:
    Variable(const char *name);
    ~Variable();

    char* GetName();
    Number* GetValue();
    void AssignValue(Number *value);

    Variable* Next;

private:
    char *name;
    Number *value;
    bool chainDelete;
    friend bool VariableList::Delete(const char *name);
};

/**
 * @brief Statement to list all user defined variables.
 *
 */
class ListVariablesStatement : public virtual StatementNode {
public:
    ListVariablesStatement();
    char* Execute();
};

/**
 * @brief Use of a variable in a syntax tree.
 *
 */
class VariableNode : public ExpressionNode {
public:
    VariableNode(Variable* variable);
    char* GetText();
    Number* Evaluate();
    void AssignValue(Number *value);
    int GetPrecedence();
    SyntaxNode* GetNext();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    char* GetNodeText();

private:
    Variable* variable;
};


/**
 * @brief Use of last result in a syntax tree.
 *
 */
class InsVariableNode : public VariableNode {
public:
    InsVariableNode();
    char* GetText();
    Number* Evaluate();

protected:
    char* GetNodeText();
};

/**
 * @brief Use of a numeric value in a syntax tree.
 *
 */
class NumericValueNode : public ExpressionNode {
public:
    NumericValueNode();
    NumericValueNode(Number *value);

    virtual ReductionType GetReductionType();
    int GetPrecedence() ;
    char* GetText();
    SyntaxNode* GetNext();
    Number* Evaluate();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);
    void ReplaceWith(Number *value);

protected:
    char* GetNodeText();
};

/**
 * @brief Use of Eulers number in a syntax tree.
 *
 */
class EulersNumberNode : public NumericValueNode {
public:
    EulersNumberNode();
    ReductionType GetReductionType();

protected:
    char* GetNodeText();
};

/**
 * @brief Use of PI in a syntax tree.
 *
 */
class PiNode : public NumericValueNode {
public:
    PiNode();
    ReductionType GetReductionType();

protected:
    char* GetNodeText();
};

/**
 * @brief Use of the square root of -2 in a syntax tree.
 *
 */
class ComplexiNode : public NumericValueNode {
public:
    ComplexiNode();
    ReductionType GetReductionType();

protected:
    char* GetNodeText();
};

#endif

