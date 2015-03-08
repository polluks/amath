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

#include "def/libc.h"
#include "def/text.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/cplex.h"
#include "lib/charbuf.h"
#include "main/nodes.h"
#include "main/values.h"
#include "prog/program.h"

// -----------------------------------------------------
// --------------------- Variable ----------------------
// -----------------------------------------------------

Variable::Variable(const char *name)
{
    AllocAndCopy(&this->name, name);
    value = NOMEM;
    Next = NOMEM;
    chainDelete = true;
}

Variable::~Variable()
{
    delete [] name;

    if (value != NOMEM) {
        delete value;
    }

    if (chainDelete && Next != NOMEM) {
        delete Next;
    }
}

char* Variable::GetName()
{
    return name;
}

Number* Variable::GetValue()
{
    return value->Clone();;
}

void Variable::AssignValue(Number *value)
{
    if (this->value != NOMEM) {
        delete this->value;
    }

    this->value = value->Clone();
}

// -----------------------------------------------------
// ------------------- VariableList --------------------
// -----------------------------------------------------

VariableList::VariableList()
{
    first = NOMEM;
    buf = new CharBuffer();
}

VariableList::~VariableList()
{
    if (first != NOMEM) {
        delete first;
    }

    delete buf;
}

void VariableList::Clear()
{
    if (first != NOMEM) {
        delete first;
        first = NOMEM;
    }

    buf->ClearBuffer();
}

bool VariableList::Delete(const char *name)
{
    Variable* var = GetVariable(name);

    if (var == NOMEM) {
        return false;
    }

    if (var == first) {
        first = var->Next;
        var->chainDelete = false;
        delete var;
        return true;
    }

    Variable *current = first->Next;
    Variable *last = first;

    while (current != var) {
        current = current->Next;
        last = last->Next;
    }

    last->Next = var->Next;

    // Only delete this variable. Not the whole chain.
    var->chainDelete = false;
    delete var;

    return true;
}

Variable* VariableList::GetFirstVariable()
{
    return first;
}

Variable* VariableList::GetVariable(const char *name)
{
    Variable* current = first;

    while (current != NOMEM && !StrIsEqual(current->GetName(), name)) {
        current = current->Next;
    }

    return current;
}

Variable* VariableList::CreateVariable(const char *name)
{
    if (first == NOMEM) {
        first = new Variable(name);
        return first;
    }

    Variable* current = first;
    Variable* last = NOMEM;

    while (current != NOMEM) {
        if (StrIsEqual(name, current->GetName())) {
            return current;
        }

        last = current;
        current = current->Next;
    }

    current = new Variable(name);
    last->Next = current;

    return current;
}

Variable* VariableList::InsertTemporaryVariable(Variable *variable)
{
    // Temporary variables are always inserted at the beginning of the list.
    Variable* oldFirst = first;
    first = variable;
    variable->Next = oldFirst;

    return variable;
}

void VariableList::RemoveTemporaryVariable()
{
    // Temporary variables are not owned by the variable list. Do not free memory.
    Variable *newFirst = first->Next;
    first->Next = NOMEM;
    first = newFirst;
}

char* VariableList::List()
{
    return ListContent(false);
}

char* VariableList::ListDefinitions()
{
    return ListContent(true);
}

char* VariableList::ListContent(bool cmdFormat)
{
    buf->Empty();

    if (GetFirstVariable() == NOMEM) {
        return (char*)(cmdFormat ? NOMEM : HELPVARSNDEF);
    }

    int len = 0;
    Variable* current = GetFirstVariable();

    while (current != NOMEM) {
        len += StrLen(current->GetName());
        len += 3;
        len += 32; // Max length of value
        len += cmdFormat ? 2 : 1;
        current = current->Next;
    }

    current = GetFirstVariable();

    buf->EnsureSize(len);

    while (current != NOMEM) {
        buf->Append(current->GetName());
        buf->Append(" = ");

        Number *num = current->GetValue();
        const char *val = Program->Output->GetText(num);
        buf->Append(val);
        delete num;

        if (cmdFormat) {
            buf->Append(';');
        }

        buf->Append(NEWLINE);
        current = current->Next;
    }

    return buf->GetString();
}

// -----------------------------------------------------
// -------------- ListVariablesStatement ---------------
// -----------------------------------------------------

ListVariablesStatement::ListVariablesStatement()
    : StatementNode() { }

char* ListVariablesStatement::Execute()
{
    return Program->Variables->List();
}

// -----------------------------------------------------
// ------------------- VariableNode --------------------
// -----------------------------------------------------

VariableNode::VariableNode(Variable* variable):
    ExpressionNode(), variable(variable) { }

int VariableNode::GetPrecedence()
{
    return 0;
}

Number* VariableNode::Evaluate()
{
    result = variable->GetValue();
    return result;
}

void VariableNode::AssignValue(Number *value)
{
    variable->AssignValue(value);
}

char* VariableNode::GetText()
{
    return variable->GetName();
}

char* VariableNode::GetNodeText()
{
    return variable->GetName();
}

SyntaxNode* VariableNode::GetNext()
{
    return NOMEM;
}

void VariableNode::Attach(SyntaxNode* node)
{ }

void VariableNode::Detach(SyntaxNode* node)
{ }

void VariableNode::Replace(SyntaxNode* n, SyntaxNode* x)
{ }

// -----------------------------------------------------
// ----------------- NumericValueNode ------------------
// -----------------------------------------------------

NumericValueNode::NumericValueNode() :
    ExpressionNode(new RealNumber()) { }

NumericValueNode::NumericValueNode(Number *value) :
    ExpressionNode(value) { }

ReductionType NumericValueNode::GetReductionType()
{
    return valuereduc;
}

int NumericValueNode::GetPrecedence()
{
    return !leftBottom ?
           result->GetPrecedence() :
           result->GetDefaultPrecedence();
}

Number* NumericValueNode::Evaluate()
{
    return result;
}

char* NumericValueNode::GetText()
{
    return GetNodeText();
}

char* NumericValueNode::GetNodeText()
{
    const char *val = Program->Input->GetText(result);
    output->ClearAndCopy(val);
    return output->GetString();
}

SyntaxNode* NumericValueNode::GetNext()
{
    return NOMEM;
}

void NumericValueNode::Attach(SyntaxNode* node)
{ }

void NumericValueNode::Detach(SyntaxNode* node)
{ }

void NumericValueNode::Replace(SyntaxNode* n, SyntaxNode* x)
{ }

void NumericValueNode::ReplaceWith(Number* value)
{
    delete result;
    result = value;
}

// -----------------------------------------------------
// ----------------- EulersNumberNode ------------------
// -----------------------------------------------------

EulersNumberNode::EulersNumberNode() :
    NumericValueNode(new RealNumber(EULERS)) { }

ReductionType EulersNumberNode::GetReductionType()
{
    return nonereduc;
}

char* EulersNumberNode::GetNodeText()
{
    return (char*)"e";
}

// -----------------------------------------------------
// ---------------------- PiNode -----------------------
// -----------------------------------------------------

PiNode::PiNode() :
    NumericValueNode(new RealNumber(PI)) { }

ReductionType PiNode::GetReductionType()
{
    return nonereduc;
}

char* PiNode::GetNodeText()
{
    return (char*)"pi";
}

// -----------------------------------------------------
// ------------------- ComplexiNode --------------------
// -----------------------------------------------------

ComplexiNode::ComplexiNode() :
    NumericValueNode(new ComplexNumber(0.0, 1.0)) { }

ReductionType ComplexiNode::GetReductionType()
{
    return nonereduc;
}

char* ComplexiNode::GetNodeText()
{
    return (char*)"i";
}
