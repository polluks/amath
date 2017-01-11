/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
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

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

/**
 * @file  functions.h
 * @brief Application logic tied to functions.
 *
 */

#include "main/nodes.h"
#include "main/values.h"
#include "main/statements.h"

/**
 * @brief Represents a mathematical function in a syntax tree.
 *
 * Function nodes in syntax trees can both be well known functions like
 * cosine (cos) and also user defined functions. The function node represents
 * a function call and not a function definition.
 *
 * A formal description of mathematical functions can be found at Wikipedia:
 * http://en.wikipedia.org/wiki/Function_(mathematics)
 *
 * When instantiating a function node an argument must be supplied. The argument
 * is a pointer to an expression node representing the value which should be used
 * when computing the function value.
 *
 */
class FunctionNode : public ExpressionNode {
public:
    FunctionNode(ExpressionNode* expression);
    ~FunctionNode();

    int GetPrecedence();
    char* GetText();
    virtual SyntaxNode* GetNext();
    virtual void Attach(SyntaxNode *node);
    virtual void Detach(SyntaxNode *node);
    virtual void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    ExpressionNode* expression;
};

struct functiondef;
class UserFunction;

/**
 * @brief A list of user defined functions.
 *
 */
class FunctionList {
public:
    FunctionList();
    ~FunctionList();

    void Clear();
    bool Delete(const char *name, const char *argument);
    bool IsSystemFunction(const char *name);
    UserFunction* GetFirstFunction();
    UserFunction* GetFunctionDef(const char *name);
    UserFunction* GetFunctionDef(const char *name, const char *argument);
    FunctionNode* GetFunctionCall(const char *function, ExpressionNode* value);

    char* List();
    char* ListDefinitions();

private:
    char* ListContent(bool cmdFormat);
    CharBuffer *buf;
    UserFunction *first;
    functiondef *GetSystemFunction(const char *ident);
};

/**
 * @brief A user defined function.
 *
 */
class UserFunction {
public:
    UserFunction(const char *name, const char *variable, ExpressionNode *expression);
    UserFunction(const char *name);
    ~UserFunction();

    UserFunction *Next;

    char *GetName();
    char *GetDefitionName();
    char *GetDefitionText();
    Variable* GetVariable();
    Variable* CreateVariable(const char *name);
    ExpressionNode* GetExpression();
    void SetExpression(ExpressionNode *expression);

private:
    char *name;
    Variable *variable;
    ExpressionNode *expression;
    bool chainDelete;
    friend bool FunctionList::Delete(const char *name, const char *argument);

    void InitializeTexts();
    CharBuffer *defname;
    CharBuffer *defition;
};

/**
 * @brief A syntax node able to list all user defined functions.
 *
 */
class ListFunctionsStatement : public StatementNode {
public:
    ListFunctionsStatement();
    char* Execute();
};

/**
 * @brief A syntax node able to define a user defined function.
 *
 */
class FunctionDefinitionNode : public StatementNode {
public:
    FunctionDefinitionNode();
    char* GetText();
    char* Execute();
};

/**
 * @brief An expression node able to compute a function value.
 *
 */
class UserFunctionNode : public FunctionNode {
public:
    UserFunctionNode(UserFunction* function, ExpressionNode* parameter);
    Number* Evaluate();
    SyntaxNode* GetNext();
    void Attach(SyntaxNode *node);
    void Detach(SyntaxNode *node);
    void Replace(SyntaxNode *n, SyntaxNode *x);

protected:
    char* GetNodeText();

private:
    UserFunction *function;
};

// -----------------------------------------------------
// ------------------ Odd Functions --------------------
// -----------------------------------------------------

class AbsoluteFunctionNode : public FunctionNode {
public:
    AbsoluteFunctionNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

/**
 * @brief A signum function in a syntax tree.
 *
 * Extracts the sign of a real number. See Number for implementation.
 *
 * More info on the signum function is available at Wikipedia:
 * http://en.wikipedia.org/wiki/Sign_function
 *
 */
class SignumNode : public FunctionNode {
public:
    SignumNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// ---------------- Rounding Functions -----------------
// -----------------------------------------------------

/**
 * @brief A rounding function in a syntax tree.
 *
 * Round to nearest integer. See Number for implementation.
 *
 * More info on the rounding function is available at Wikipedia:
 * http://en.wikipedia.org/wiki/Rounding
 *
 */
class RoundNode : public FunctionNode {
public:
    RoundNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

/**
 * @brief A truncation function in a syntax tree.
 *
 * Discard the number of digits right of the decimal point.
 * See Number for implementation.
 *
 * More info on the truncation function is available at Wikipedia:
 * http://en.wikipedia.org/wiki/Truncation
 *
 */
class TruncNode : public FunctionNode {
public:
    TruncNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class FloorNode : public FunctionNode {
public:
    FloorNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class CeilingNode : public FunctionNode {
public:
    CeilingNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// ------------------ Root Functions -------------------
// -----------------------------------------------------

class SquareRootNode : public FunctionNode {
public:
    SquareRootNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class CubeRootNode : public FunctionNode {
public:
    CubeRootNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// --------------- Logarithmic Functions ---------------
// -----------------------------------------------------

class LogNode : public FunctionNode {
public:
    LogNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class LnRootNode : public FunctionNode {
public:
    LnRootNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class BinaryLogNode : public FunctionNode {
public:
    BinaryLogNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// ------------- Trigonometric Functions ---------------
// -----------------------------------------------------

class SineNode : public FunctionNode {
public:
    SineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class CosineNode : public FunctionNode {
public:
    CosineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class TangentNode : public FunctionNode {
public:
    TangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class CotangentNode : public FunctionNode {
public:
    CotangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class CosecantNode : public FunctionNode {
public:
    CosecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class SecantNode : public FunctionNode {
public:
    SecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// ---------- Inverse Trigonometric Functions ----------
// -----------------------------------------------------

class ArcSineNode : public FunctionNode {
public:
    ArcSineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class ArcCosineNode : public FunctionNode {
public:
    ArcCosineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class ArcTangentNode : public FunctionNode {
public:
    ArcTangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class ArcCotangentNode : public FunctionNode {
public:
    ArcCotangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class ArcCosecantNode : public FunctionNode {
public:
    ArcCosecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class ArcSecantNode : public FunctionNode {
public:
    ArcSecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// --------------- Hyperbolic Functions ----------------
// -----------------------------------------------------

class HyperbolicSineNode : public FunctionNode {
public:
    HyperbolicSineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicCosineNode : public FunctionNode {
public:
    HyperbolicCosineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicTangentNode : public FunctionNode {
public:
    HyperbolicTangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicCotangentNode : public FunctionNode {
public:
    HyperbolicCotangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicSecantNode : public FunctionNode {
public:
    HyperbolicSecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicCosecantNode : public FunctionNode {
public:
    HyperbolicCosecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

// -----------------------------------------------------
// ----------- Inverse Hyperbolic Functions ------------
// -----------------------------------------------------

class HyperbolicArccosineNode : public FunctionNode {
public:
    HyperbolicArccosineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicArcsineNode : public FunctionNode {
public:
    HyperbolicArcsineNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicArctangentNode : public FunctionNode {
public:
    HyperbolicArctangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicArcCotangentNode : public FunctionNode {
public:
    HyperbolicArcCotangentNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicArcCosecantNode : public FunctionNode {
public:
    HyperbolicArcCosecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

class HyperbolicArcSecantNode : public FunctionNode {
public:
    HyperbolicArcSecantNode(ExpressionNode* expression);
    static FunctionNode* Create(ExpressionNode* expression);
    Number* Evaluate();

protected:
    char* GetNodeText();
};

#endif
