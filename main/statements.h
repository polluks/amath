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

#ifndef _STATEMENTS_H
#define _STATEMENTS_H

/**
 * @file  statements.h
 * @brief General statement nodes
 *
 * This file contains classes implementing statements in a
 * syntax tree. All statements inherit from the StatementNode
 * base class.
 *
 */

#include "main/nodes.h"
#include "main/token.h"

/**
 * @brief Clear the console window.
 *
 * Statement node which encapsulate the clear statment.
 *
 */
class ClearStatement : public virtual StatementNode {
public:
    ClearStatement() { }
    ~ClearStatement() { }
    char* Execute();
};

/**
 * @brief Exit program.
 *
 * Statement node which encapsulate the exit statment.
 *
 */
class ExitStatement : public virtual StatementNode {
public:
    ExitStatement() { }
    ~ExitStatement() { }
    char* Execute();
};

/**
 * @brief An empty statement.
 *
 * Statement node which encapsulate an empty statment. This happens
 * fx. if the user only enters a line feed.
 *
 */
class EmptyStatement : public virtual StatementNode {
public:
    EmptyStatement() { }
    ~EmptyStatement() { }
    char* Execute();
};

/**
 * @brief Show version string.
 *
 * Statement node which encapsulate the version statment.
 *
 */
class VersionStatement : public virtual StatementNode {
public:
    VersionStatement() { }
    ~VersionStatement() { }
    char* Execute();
};

/**
 * @brief Mutes the output of another statement.
 *
 * Statement node which encapsulate another statement and
 * mutes the output when executing the inner statement.
 *
 */
class SilentStatement : public virtual StatementNode {
public:
    SilentStatement(StatementNode *statement);
    ~SilentStatement();

    char* Execute();
    SyntaxNode* GetNext();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

private:
    StatementNode *statement;
};

/**
 * @brief Evaluate arithmetic expression.
 *
 * Statement node which encapsulate the eval statment.
 *
 */
class EvalStatement : public virtual StatementNode {
public:
    EvalStatement(ExpressionNode *expression);
    ~EvalStatement();

    char* Execute();
    SyntaxNode* GetNext();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

private:
    ExpressionNode *expression;
};

/**
 * @brief Logic related to the help statement.
 *
 */
class HelpStatement : public virtual StatementNode {
public:
    HelpStatement();
    HelpStatement(Symbol argument);
    HelpStatement(const char *ident);
    ~HelpStatement();
    char* Execute();

private:
    Symbol argument;
    char *ident;
};

/**
 * @brief Delete variable or function.
 *
 * Statement node which encapsulate the delete statment.
 *
 */
class DeleteStatement : public virtual StatementNode {
public:
    DeleteStatement(Symbol symbol);
    DeleteStatement(const char* name);
    DeleteStatement(const char* name, const char *argument);
    ~DeleteStatement();
    char* Execute();

private:
    Symbol type;
    char *name;
    char *argument;
};

/**
 * @brief Change numeral input system.
 *
 * Statement node which encapsulate the input statment.
 *
 */
class InputStatement : public virtual StatementNode {
public:
    InputStatement();
    InputStatement(unsigned int base);
    ~InputStatement() { }
    char* Execute();

private:
    unsigned int base;
};

/**
 * @brief Change numeral output system.
 *
 * Statement node which encapsulate the output statment.
 *
 */
class OutputStatement : public virtual StatementNode {
public:
    OutputStatement();
    OutputStatement(unsigned int base);
    ~OutputStatement() { }
    char* Execute();

private:
    unsigned int base;
};

/**
 * @brief Set number of significant digits to show.
 *
 * Statement node which encapsulate the digits statment.
 *
 */
class DigitsStatement : public virtual StatementNode {
public:
    DigitsStatement();
    DigitsStatement(unsigned int digits);
    ~DigitsStatement() { }
    char* Execute();

private:
    bool show;
    unsigned int digits;
};

class ShowStatement : public virtual StatementNode {
public:
    ShowStatement(const char *file);
    ~ShowStatement();
    char* Execute();

private:
    char *file;
};

class ListStatement : public virtual StatementNode {
public:
    ListStatement();
    ListStatement(const char *directory);
    ~ListStatement();
    char* Execute();

private:
    char *directory;
};

class LoadStatement : public virtual StatementNode {
public:
    LoadStatement(const char *file);
    ~LoadStatement();
    char* Execute();

private:
    char *file;
};

class SaveStatement : public virtual StatementNode {
public:
    SaveStatement(const char *file);
    ~SaveStatement();
    char* Execute();

private:
    char *file;
};

class ExecuteStatement : public virtual StatementNode {
public:
    ExecuteStatement(const char *file);
    ~ExecuteStatement();
    char* Execute();

private:
    char *file;
};

class PlotStatement : public virtual StatementNode {
public:
    PlotStatement(const char *name, const char *parameter, const char *file);
    PlotStatement(const char *name, const char *parameter);
    ~PlotStatement();
    char* Execute();

private:
    char *name;
    char *parameter;
    char *file;
};

class DrawStatement : public virtual StatementNode {
public:
    DrawStatement(const char *name, const char *parameter);
    ~DrawStatement();
    char* Execute();

private:
    char *name;
    char *parameter;
};

#endif
