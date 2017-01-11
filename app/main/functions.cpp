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

#include "clib.h"
#include "lib/numb.h"
#include "main/values.h"
#include "main/functions.h"
#include "main/functiondefs.h"
#include "system/program.h"
#include "localize/text.h"

// -----------------------------------------------------
// ------------------ FunctionNode ---------------------
// -----------------------------------------------------

FunctionNode::FunctionNode(ExpressionNode* expression) :
    ExpressionNode(), expression(expression) { }

FunctionNode::~FunctionNode()
{
    if (expression != NOMEM) {
        delete expression;
    }
}

int FunctionNode::GetPrecedence()
{
    return 5;
}

char* FunctionNode::GetText()
{
    const char *functionText = GetNodeText();
    const char *expText = expression->GetText();

    output->EnsureSize(StrLen(functionText) + StrLen(expText) + 2 + 1);
    output->Empty();
    output->Append(functionText);
    output->Append("(");
    output->Append(expText);
    output->Append(")");

    return output->GetString();
}

SyntaxNode* FunctionNode::GetNext()
{
    if (iterator == NOMEM) {
        iterator = expression;
        return expression;
    }

    return NOMEM;
}

void FunctionNode::Attach(SyntaxNode* node)
{
    if (expression == NOMEM) {
        expression = (ExpressionNode*)node;
        node->SetParent(this);
    }
}

void FunctionNode::Detach(SyntaxNode* node)
{
    if (expression == node) {
        expression = NOMEM;
    }
}

void FunctionNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n) {
        delete expression;
        expression = (ExpressionNode*)x;
    }
}

// -----------------------------------------------------
// ------------------ UserFunction ---------------------
// -----------------------------------------------------

UserFunction::UserFunction(const char *name, const char *variable, ExpressionNode *expression)
{
    AllocAndCopy(&this->name, name);
    this->variable = new Variable(variable);
    this->expression = expression;
    this->Next = NOMEM;

    defname = new CharBuffer();
    defition = new CharBuffer();
    InitializeTexts();

    chainDelete = true;
}

UserFunction::UserFunction(const char *name)
{
    AllocAndCopy(&this->name, name);
    this->variable = NOMEM;
    this->expression = NOMEM;
    this->Next = NOMEM;

    defname = new CharBuffer();
    defition = new CharBuffer();

    chainDelete = true;
}

UserFunction::~UserFunction()
{
    delete [] name;
    delete defname;
    delete defition;

    if (variable != NOMEM) {
        delete variable;
    }

    if (expression != NOMEM) {
        delete expression;
    }

    if (chainDelete && Next != NOMEM) {
        delete Next;
    }
}

void UserFunction::InitializeTexts()
{
    defname->Empty();
    defname->Append(name);
    defname->Append('(');
    defname->Append(variable != NOMEM ? variable->GetName() : EMPTYSTRING);
    defname->Append(')');

    defition->Empty();
    defition->Append(defname->GetString());
    defition->Append('=');
    defition->Append(expression != NOMEM ? expression->GetText() : EMPTYSTRING);
}

char* UserFunction::GetName()
{
    return name;
}

char* UserFunction::GetDefitionName()
{
    return defname->GetString();
}

char* UserFunction::GetDefitionText()
{
    return defition->GetString();
}

Variable* UserFunction::GetVariable()
{
    return variable;
}

Variable* UserFunction::CreateVariable(const char *name)
{
    if(variable != NOMEM) {
        delete variable;
    }

    variable = new Variable(name);
    InitializeTexts();

    return variable;
}

ExpressionNode* UserFunction::GetExpression()
{
    return expression;
}

void UserFunction::SetExpression(ExpressionNode* expression)
{
    delete this->expression;
    this->expression = expression;
    InitializeTexts();
}

// -----------------------------------------------------
// ---------------- UserFunctionNode -------------------
// -----------------------------------------------------

UserFunctionNode::UserFunctionNode(UserFunction* function, ExpressionNode* parameter) :
    FunctionNode(parameter), function(function) { }

char* UserFunctionNode::GetNodeText()
{
    return function->GetName();
}

Number* UserFunctionNode::Evaluate()
{
    // Set value of function parameter and then evaluate function.
    function->GetVariable()->AssignValue(expression->Evaluate());
    return function->GetExpression()->Evaluate();
}

SyntaxNode* UserFunctionNode::GetNext()
{
    if (iterator == NOMEM) {
        iterator = function->GetExpression();
        return iterator;
    }

    return NOMEM;
}

void UserFunctionNode::Attach(SyntaxNode* node)
{
    // TODO: Implement
}

void UserFunctionNode::Detach(SyntaxNode* node)
{
    // TODO: Implement
}

void UserFunctionNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    // TODO: Implement
}

// -----------------------------------------------------
// -------------- FunctionDefinitionNode ---------------
// -----------------------------------------------------

FunctionDefinitionNode::FunctionDefinitionNode() :
    StatementNode() {
    output->EnsureMinimumSize();
    output->Empty();
}

char* FunctionDefinitionNode::Execute()
{
    // TODO: Move function definition logic from parser to here.
    return output->GetString();
}

char* FunctionDefinitionNode::GetText()
{
    return output->GetString();
}

// -----------------------------------------------------
// ------------------ FunctionList ---------------------
// -----------------------------------------------------

FunctionList::FunctionList()
{
    first = NOMEM;
    buf = new CharBuffer();
}

FunctionList::~FunctionList()
{
    if (first != NOMEM) {
        delete first;
    }

    delete buf;
}

void FunctionList::Clear()
{
    if (first != NOMEM) {
        delete first;
        first = NOMEM;
    }

    buf->ClearBuffer();
}

bool FunctionList::Delete(const char *name, const char *argument)
{
    if (first == NOMEM)
    {
        return false;
    }

    if (first != NOMEM && StrIsEqual(first->GetName(), name) && StrIsEqual(first->GetVariable()->GetName(), argument)) {
        UserFunction *func = first;
        first = first->Next;
        func->chainDelete = false;
        delete func;
        return true;
    }

    UserFunction *current = first->Next;
    UserFunction *last = first;

    while (current != NOMEM && !StrIsEqual(current->GetName(), name)) {
        current = current->Next;
        last = last->Next;
    }

    if (current == NOMEM) {
        return false;
    } else if (!StrIsEqual(current->GetVariable()->GetName(), argument)) {
        return false;
    }

    last->Next = current->Next;

    // Only delete this variable. Not the whole chain.
    current->chainDelete = false;
    delete current;

    return true;
}

UserFunction* FunctionList::GetFirstFunction()
{
    return first;
}

UserFunction* FunctionList::GetFunctionDef(const char *name)
{
    // Search the list for function definition. If function not found then create a new definition.
    if (first == NOMEM) {
        first = new UserFunction(name);
        return first;
    }

    UserFunction *current = first;
    UserFunction *last = NOMEM;

    while (current != NOMEM) {
        if (StrIsEqual(current->GetName(), name)) {
            return current;
        }

        last = current;
        current = current->Next;
    }

    current = new UserFunction(name);
    last->Next = current;

    return current;
}

UserFunction* FunctionList::GetFunctionDef(const char *name, const char *argument)
{
    UserFunction *current = first;

    while (current != NOMEM) {
        if (StrIsEqual(current->GetName(), name) && StrIsEqual(current->GetVariable()->GetName(), argument)) {
            return current;
        }

        current = current->Next;
    }

    return NOMEM;
}

FunctionNode* FunctionList::GetFunctionCall(const char *function, ExpressionNode *parameter)
{
    const functiondef *systemFunction = GetSystemFunction(function);
    if (systemFunction != NOMEM) {
        return (systemFunction->create)(parameter);
    }

    UserFunction *current = first;
    while (current != NOMEM && !StrIsEqual(current->GetName(), function)) {
        current = current->Next;
    }

    if (current != NOMEM) {
        return new UserFunctionNode(current, parameter);
    }

    return NOMEM;
}

char* FunctionList::List()
{
    return ListContent(false);
}

char* FunctionList::ListDefinitions()
{
    return ListContent(true);
}

char* FunctionList::ListContent(bool cmdFormat)
{
    if (first == NOMEM) {
        return (char*)(cmdFormat ? NOMEM : HELPFUNCNDEF);
    }

    int len = 0;
    UserFunction *current = first;

    while (current != NOMEM) {
        len += StrLen(current->GetName());
        len += 1;
        len += StrLen(current->GetVariable()->GetName());
        len += 2;
        len += StrLen(current->GetExpression()->GetText());
        len += cmdFormat ? 2 : 1;
        current = current->Next;
    }

    buf->Empty();
    buf->EnsureSize(len + StrLen(NEWLINE) + 1);

    current = first;
    while (current != NOMEM) {
        buf->Append(current->GetName());
        buf->Append("(");
        buf->Append(current->GetVariable()->GetName());
        buf->Append(")=");
        buf->Append(current->GetExpression()->GetText());

        if (cmdFormat) {
            buf->Append(';');
        }

        buf->Append(NEWLINE);
        current = current->Next;
    }

    return buf->GetString();
}

bool FunctionList::IsSystemFunction(const char *name)
{
    return (GetSystemFunction(name) != NOMEM);
}

functiondef* FunctionList::GetSystemFunction(const char *ident)
{
    static const unsigned int count = sizeof(functiondefs) / sizeof(functiondef);
    for (unsigned int i = 0; i < count; i++) {
        if (StrIsEqual(functiondefs[i].name, ident)) {
            return (functiondef*)&functiondefs[i];
        }
    }

    return NOMEM;
}

// -----------------------------------------------------
// -------------- ListFunctionsStatement ---------------
// -----------------------------------------------------

ListFunctionsStatement::ListFunctionsStatement() :
    StatementNode() { }

char* ListFunctionsStatement::Execute()
{
    return Program->Functions->List();
}

// -----------------------------------------------------
// --------------- AbsoluteFunctionNode ----------------
// -----------------------------------------------------

AbsoluteFunctionNode::AbsoluteFunctionNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* AbsoluteFunctionNode::Create(ExpressionNode* expression)
{
    return new AbsoluteFunctionNode(expression);
}

Number* AbsoluteFunctionNode::Evaluate()
{
    result = expression->Evaluate()->Absolute();
    return result;
}

char* AbsoluteFunctionNode::GetNodeText()
{
    return (char*)"abs";
}

// -----------------------------------------------------
// --------------------- SignumNode --------------------
// -----------------------------------------------------

SignumNode::SignumNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* SignumNode::Create(ExpressionNode* expression)
{
    return new SignumNode(expression);
}

Number* SignumNode::Evaluate()
{
    result = expression->Evaluate()->Signum();
    return result;
}

char* SignumNode::GetNodeText()
{
    return (char*)"sgn";
}

// -----------------------------------------------------
// --------------------- RoundNode ---------------------
// -----------------------------------------------------

RoundNode::RoundNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* RoundNode::Create(ExpressionNode* expression)
{
    return new RoundNode(expression);
}

Number* RoundNode::Evaluate()
{
    result = expression->Evaluate()->Round();
    return result;
}

char* RoundNode::GetNodeText()
{
    return (char*)"round";
}

// -----------------------------------------------------
// --------------------- TruncNode ---------------------
// -----------------------------------------------------

TruncNode::TruncNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* TruncNode::Create(ExpressionNode* expression)
{
    return new TruncNode(expression);
}

Number* TruncNode::Evaluate()
{
    result = expression->Evaluate()->Trunc();
    return result;
}

char* TruncNode::GetNodeText()
{
    return (char*)"trunc";
}

// -----------------------------------------------------
// --------------------- FloorNode ---------------------
// -----------------------------------------------------

FloorNode::FloorNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* FloorNode::Create(ExpressionNode* expression)
{
    return new FloorNode(expression);
}

Number* FloorNode::Evaluate()
{
    result = expression->Evaluate()->Floor();
    return result;
}

char* FloorNode::GetNodeText()
{
    return (char*)"floor";
}

// -----------------------------------------------------
// -------------------- CeilingNode ---------------------
// -----------------------------------------------------

CeilingNode::CeilingNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* CeilingNode::Create(ExpressionNode* expression)
{
    return new CeilingNode(expression);
}

Number* CeilingNode::Evaluate()
{
    result = expression->Evaluate()->Ceiling();
    return result;
}

char* CeilingNode::GetNodeText()
{
    return (char*)"ceil";
}

// -----------------------------------------------------
// ------------------ SquareRootNode -------------------
// -----------------------------------------------------

SquareRootNode::SquareRootNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* SquareRootNode::Create(ExpressionNode* expression)
{
    return new SquareRootNode(expression);
}

Number* SquareRootNode::Evaluate()
{
    result = expression->Evaluate()->SquareRoot();
    return result;
}

char* SquareRootNode::GetNodeText()
{
    return (char*)"sqrt";
}

// -----------------------------------------------------
// ------------------- CubeRootNode --------------------
// -----------------------------------------------------

CubeRootNode::CubeRootNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* CubeRootNode::Create(ExpressionNode* expression)
{
    return new CubeRootNode(expression);
}

Number* CubeRootNode::Evaluate()
{
    result = expression->Evaluate()->CubeRoot();
    return result;
}

char* CubeRootNode::GetNodeText()
{
    return (char*)"cbrt";
}

// -----------------------------------------------------
// ------------------ BinaryLogFunction ----------------
// -----------------------------------------------------

BinaryLogNode::BinaryLogNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* BinaryLogNode::Create(ExpressionNode* expression)
{
    return new BinaryLogNode(expression);
}

Number* BinaryLogNode::Evaluate()
{
    result = expression->Evaluate()->Log2();
    return result;
}

char* BinaryLogNode::GetNodeText()
{
    return (char*)"lb";
}

// -----------------------------------------------------
// --------------------- LnRootNode --------------------
// -----------------------------------------------------

LnRootNode::LnRootNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* LnRootNode::Create(ExpressionNode* expression)
{
    return new LnRootNode(expression);
}

Number* LnRootNode::Evaluate()
{
    result = expression->Evaluate()->Log();
    return result;
}

char* LnRootNode::GetNodeText()
{
    return (char*)"ln";
}

// -----------------------------------------------------
// -------------------- LogRootNode --------------------
// -----------------------------------------------------

LogNode::LogNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* LogNode::Create(ExpressionNode* expression)
{
    return new LogNode(expression);
}

Number* LogNode::Evaluate()
{
    result = expression->Evaluate()->Log10();
    return result;
}

char* LogNode::GetNodeText()
{
    return (char*)"lg";
}

// -------------------------------------------------------------------------
// ----------------------- Trigonometric Functions -------------------------
// -------------------------------------------------------------------------

SineNode::SineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* SineNode::Create(ExpressionNode* expression)
{
    return new SineNode(expression);
}

Number* SineNode::Evaluate()
{
    result = expression->Evaluate()->Sine();
    return result;
}

char* SineNode::GetNodeText()
{
    return (char*)"sin";
}

CosineNode::CosineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* CosineNode::Create(ExpressionNode* expression)
{
    return new CosineNode(expression);
}

Number* CosineNode::Evaluate()
{
    result = expression->Evaluate()->Cosine();
    return result;
}

char* CosineNode::GetNodeText()
{
    return (char*)"cos";
}

TangentNode::TangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* TangentNode::Create(ExpressionNode* expression)
{
    return new TangentNode(expression);
}

Number* TangentNode::Evaluate()
{
    result = expression->Evaluate()->Tangent();
    return result;
}

char* TangentNode::GetNodeText()
{
    return (char*)"tan";
}

CosecantNode::CosecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* CosecantNode::Create(ExpressionNode* expression)
{
    return new CosecantNode(expression);
}

Number* CosecantNode::Evaluate()
{
    result = expression->Evaluate()->Cosecant();
    return result;
}

char* CosecantNode::GetNodeText()
{
    return (char*)"csc";
}

SecantNode::SecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* SecantNode::Create(ExpressionNode* expression)
{
    return new SecantNode(expression);
}

Number* SecantNode::Evaluate()
{
    result = expression->Evaluate()->Secant();
    return result;
}

char* SecantNode::GetNodeText()
{
    return (char*)"sec";
}

CotangentNode::CotangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* CotangentNode::Create(ExpressionNode* expression)
{
    return new CotangentNode(expression);
}

Number* CotangentNode::Evaluate()
{
    result = expression->Evaluate()->Cotangent();
    return result;
}

char* CotangentNode::GetNodeText()
{
    return (char*)"cot";
}

// -------------------------------------------------------------------------
// -------------------- Inverse Trigonometric Functions --------------------
// -------------------------------------------------------------------------

ArcSineNode::ArcSineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* ArcSineNode::Create(ExpressionNode* expression)
{
    return new ArcSineNode(expression);
}

Number* ArcSineNode::Evaluate()
{
    result = expression->Evaluate()->ArcSine();
    return result;
}

char* ArcSineNode::GetNodeText()
{
    return (char*)"asin";
}

ArcCosineNode::ArcCosineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* ArcCosineNode::Create(ExpressionNode* expression)
{
    return new ArcCosineNode(expression);
}

Number* ArcCosineNode::Evaluate()
{
    result = expression->Evaluate()->ArcCosine();
    return result;
}

char* ArcCosineNode::GetNodeText()
{
    return (char*)"acos";
}

ArcTangentNode::ArcTangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* ArcTangentNode::Create(ExpressionNode* expression)
{
    return new ArcTangentNode(expression);
}

Number* ArcTangentNode::Evaluate()
{
    result = expression->Evaluate()->ArcTangent();
    return result;
}

char* ArcTangentNode::GetNodeText()
{
    return (char*)"atan";
}

ArcCosecantNode::ArcCosecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* ArcCosecantNode::Create(ExpressionNode* expression)
{
    return new ArcCosecantNode(expression);
}

Number* ArcCosecantNode::Evaluate()
{
    result = expression->Evaluate()->ArcCosecant();
    return result;
}

char* ArcCosecantNode::GetNodeText()
{
    return (char*)"acsc";
}

ArcSecantNode::ArcSecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* ArcSecantNode::Create(ExpressionNode* expression)
{
    return new ArcSecantNode(expression);
}

Number* ArcSecantNode::Evaluate()
{
    result = expression->Evaluate()->ArcSecant();
    return result;
}

char* ArcSecantNode::GetNodeText()
{
    return (char*)"asec";
}

ArcCotangentNode::ArcCotangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }


FunctionNode* ArcCotangentNode::Create(ExpressionNode* expression)
{
    return new ArcCotangentNode(expression);
}

Number* ArcCotangentNode::Evaluate()
{
    result = expression->Evaluate()->ArcCotangent();
    return result;
}

char* ArcCotangentNode::GetNodeText()
{
    return (char*)"acot";
}

// ------------------------------------------------------------------------
// ------------------------- Hyperbolic Functions -------------------------
// ------------------------------------------------------------------------

HyperbolicSineNode::HyperbolicSineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicSineNode::Create(ExpressionNode* expression)
{
    return new HyperbolicSineNode(expression);
}

Number* HyperbolicSineNode::Evaluate()
{
    result = expression->Evaluate()->HypSine();
    return result;
}

char* HyperbolicSineNode::GetNodeText()
{
    return (char*)"sinh";
}

HyperbolicCosineNode::HyperbolicCosineNode(ExpressionNode* expression)
    : FunctionNode(expression) { }

FunctionNode* HyperbolicCosineNode::Create(ExpressionNode* expression)
{
    return new HyperbolicCosineNode(expression);
}

Number* HyperbolicCosineNode::Evaluate()
{
    result = expression->Evaluate()->HypCosine();
    return result;
}

char* HyperbolicCosineNode::GetNodeText()
{
    return (char*)"cosh";
}

HyperbolicTangentNode::HyperbolicTangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicTangentNode::Create(ExpressionNode* expression)
{
    return new HyperbolicTangentNode(expression);
}

Number* HyperbolicTangentNode::Evaluate()
{
    result = expression->Evaluate()->HypTangent();
    return result;
}

char* HyperbolicTangentNode::GetNodeText()
{
    return (char*)"tanh";
}

HyperbolicCotangentNode::HyperbolicCotangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicCotangentNode::Create(ExpressionNode* expression)
{
    return new HyperbolicCotangentNode(expression);
}

Number* HyperbolicCotangentNode::Evaluate()
{
    result = expression->Evaluate()->HypCotangent();
    return result;
}

char* HyperbolicCotangentNode::GetNodeText()
{
    return (char*)"coth";
}

HyperbolicSecantNode::HyperbolicSecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicSecantNode::Create(ExpressionNode* expression)
{
    return new HyperbolicSecantNode(expression);
}

Number* HyperbolicSecantNode::Evaluate()
{
    result = expression->Evaluate()->HypSecant();
    return result;
}

char* HyperbolicSecantNode::GetNodeText()
{
    return (char*)"sech";
}

HyperbolicCosecantNode::HyperbolicCosecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicCosecantNode::Create(ExpressionNode* expression)
{
    return new HyperbolicCosecantNode(expression);
}

Number* HyperbolicCosecantNode::Evaluate()
{
    result = expression->Evaluate()->HypCosecant();
    return result;
}

char* HyperbolicCosecantNode::GetNodeText()
{
    return (char*)"csch";
}

// -------------------------------------------------------------------------
// --------------------- Inverse Hyperbolic Functions ----------------------
// -------------------------------------------------------------------------

HyperbolicArcsineNode::HyperbolicArcsineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArcsineNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArcsineNode(expression);
}

Number* HyperbolicArcsineNode::Evaluate()
{
    result = expression->Evaluate()->HypArcSine();
    return result;
}

char* HyperbolicArcsineNode::GetNodeText()
{
    return (char*)"asinh";
}

HyperbolicArccosineNode::HyperbolicArccosineNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArccosineNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArccosineNode(expression);
}

Number* HyperbolicArccosineNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCosine();
    return result;
}

char* HyperbolicArccosineNode::GetNodeText()
{
    return (char*)"acosh";
}

HyperbolicArctangentNode::HyperbolicArctangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArctangentNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArctangentNode(expression);
}

Number* HyperbolicArctangentNode::Evaluate()
{
    result = expression->Evaluate()->HypArcTangent();
    return result;
}

char* HyperbolicArctangentNode::GetNodeText()
{
    return (char*)"atanh";
}

HyperbolicArcCotangentNode::HyperbolicArcCotangentNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArcCotangentNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArcCotangentNode(expression);
}

Number* HyperbolicArcCotangentNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCotangent();
    return result;
}

char* HyperbolicArcCotangentNode::GetNodeText()
{
    return (char*)"acoth";
}

HyperbolicArcSecantNode::HyperbolicArcSecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArcSecantNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArcSecantNode(expression);
}

Number* HyperbolicArcSecantNode::Evaluate()
{
    result = expression->Evaluate()->HypArcSecant();
    return result;
}

char* HyperbolicArcSecantNode::GetNodeText()
{
    return (char*)"asech";
}

HyperbolicArcCosecantNode::HyperbolicArcCosecantNode(ExpressionNode* expression) :
    FunctionNode(expression) { }

FunctionNode* HyperbolicArcCosecantNode::Create(ExpressionNode* expression)
{
    return new HyperbolicArcCosecantNode(expression);
}

Number* HyperbolicArcCosecantNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCosecant();
    return result;
}

char* HyperbolicArcCosecantNode::GetNodeText()
{
    return (char*)"acsch";
}


