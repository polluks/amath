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

#include "mathr.h"
#include "amath.h"
#include "amathc.h"
#include "nodes.h"
#include "values.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/cplex.h"
#include "lib/charbuf.h"
#include "loc/text.h"
#include "system/program.h"

// -----------------------------------------------------
// --------------------- Variable ----------------------
// -----------------------------------------------------

Variable::Variable(const char* name)
{
    AllocAndCopy(&this->name, name);
    value = nullptr;
    Next = nullptr;
    chainDelete = true;
}

Variable::~Variable()
{
    delete [] name;

    if (value != nullptr)
    {
        delete value;
    }

    if (chainDelete && Next != nullptr)
    {
        delete Next;
    }
}

char* Variable::GetName() const
{
    return name;
}

Number* Variable::GetValue() const
{
    return value->Clone();;
}

void Variable::AssignValue(Number* value)
{
    if (this->value != nullptr)
    {
        delete this->value;
    }

    this->value = value->Clone();
}

// -----------------------------------------------------
// ------------------- VariableList --------------------
// -----------------------------------------------------

VariableList::VariableList()
{
    first = nullptr;
    buf = new CharBuffer();
}

VariableList::~VariableList()
{
    if (first != nullptr)
    {
        delete first;
    }

    delete buf;
}

void VariableList::Clear()
{
    if (first != nullptr)
    {
        delete first;
        first = nullptr;
    }

    buf->ClearBuffer();
}

bool VariableList::Delete(const char* name)
{
    Variable* var = GetVariable(name);

    if (var == nullptr)
    {
        return false;
    }

    if (var == first)
    {
        first = var->Next;
        var->chainDelete = false;
        delete var;
        return true;
    }

    Variable* current = first->Next;
    Variable* last = first;

    while (current != var)
    {
        current = current->Next;
        last = last->Next;
    }

    last->Next = var->Next;

    // Only delete this variable. Not the whole chain.
    var->chainDelete = false;
    delete var;

    return true;
}

Variable* VariableList::GetFirstVariable() const
{
    return first;
}

Variable* VariableList::GetVariable(const char* name) const
{
    Variable* current = first;

    while (current != nullptr && !StrIsEqual(current->GetName(), name))
    {
        current = current->Next;
    }

    return current;
}

Variable* VariableList::CreateVariable(const char* name)
{
    if (first == nullptr)
    {
        first = new Variable(name);
        return first;
    }

    Variable* current = first;
    Variable* last = nullptr;

    while (current != nullptr)
    {
        if (StrIsEqual(name, current->GetName()))
        {
            return current;
        }

        last = current;
        current = current->Next;
    }

    current = new Variable(name);
    last->Next = current;

    return current;
}

Variable* VariableList::InsertTemporaryVariable(Variable* variable)
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
    Variable* newFirst = first->Next;
    first->Next = nullptr;
    first = newFirst;
}

char* VariableList::List() const
{
    return ListContent(false);
}

char* VariableList::ListDefinitions() const
{
    return ListContent(true);
}

char* VariableList::ListContent(bool cmdFormat) const
{
    buf->Empty();

    if (GetFirstVariable() == nullptr)
    {
        return static_cast<char*>(cmdFormat ? nullptr : HELPVARSNDEF);
    }

    int len = 0;
    Variable* current = GetFirstVariable();

    while (current != nullptr)
    {
        len += StrLen(current->GetName());
        len += 3;
        len += 32; // Max length of value
        len += cmdFormat ? 2 : 1;
        current = current->Next;
    }

    current = GetFirstVariable();

    buf->EnsureSize(len);

    while (current != nullptr)
    {
        buf->Append(current->GetName());
        buf->Append(" = ");

        Number* num = current->GetValue();
        const char* val = Program->Output->GetText(num);
        buf->Append(val);
        delete num;

        if (cmdFormat)
        {
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
    : StatementNode()
{
}

char* ListVariablesStatement::Execute()
{
    return Program->Variables->List();
}

// -----------------------------------------------------
// ------------------- VariableNode --------------------
// -----------------------------------------------------

VariableNode::VariableNode(Variable* variable):
    ExpressionNode(), variable(variable)
{
}

int VariableNode::GetPrecedence()
{
    return 0;
}

Number* VariableNode::Evaluate()
{
    result = variable->GetValue();
    return result;
}

void VariableNode::AssignValue(Number* value) const
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
    return nullptr;
}

void VariableNode::Attach(SyntaxNode* node)
{
}

void VariableNode::Detach(SyntaxNode* node)
{
}

void VariableNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
}

// -----------------------------------------------------
// ----------------- InsVariableNode -------------------
// -----------------------------------------------------

InsVariableNode::InsVariableNode() :
    VariableNode(nullptr)
{
}

Number* InsVariableNode::Evaluate()
{
    return Program->GetLastResult();
}

char* InsVariableNode::GetText()
{
    static char* ret = (char*)"ins";
    return ret;
}

char* InsVariableNode::GetNodeText()
{
    static char* ret = (char*)"ins";
    return ret;
}

// -----------------------------------------------------
// ----------------- NumericValueNode ------------------
// -----------------------------------------------------

NumericValueNode::NumericValueNode() :
    ExpressionNode(new RealNumber())
{
}

NumericValueNode::NumericValueNode(Number* value) :
    ExpressionNode(value)
{
}

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
    const char* val = Program->Input->GetText(result);
    output->ClearAndCopy(val);
    return output->GetString();
}

SyntaxNode* NumericValueNode::GetNext()
{
    return nullptr;
}

void NumericValueNode::Attach(SyntaxNode* node)
{
}

void NumericValueNode::Detach(SyntaxNode* node)
{
}

void NumericValueNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
}

void NumericValueNode::ReplaceWith(Number* value)
{
    delete result;
    result = value;
}

// -----------------------------------------------------
// ----------------- EulersNumberNode ------------------
// -----------------------------------------------------

EulersNumberNode::EulersNumberNode() :
    NumericValueNode(new RealNumber(EULERS))
{
}

ReductionType EulersNumberNode::GetReductionType()
{
    return nonereduc;
}

char* EulersNumberNode::GetNodeText()
{
    static char* ret = (char*)"e";
    return ret;
}

// -----------------------------------------------------
// ---------------------- PiNode -----------------------
// -----------------------------------------------------

PiNode::PiNode() :
    NumericValueNode(new RealNumber(PI))
{
}

ReductionType PiNode::GetReductionType()
{
    return nonereduc;
}

char* PiNode::GetNodeText()
{
    static char* ret = (char*)"pi";
    return ret;
}

// -----------------------------------------------------
// ------------------- ComplexiNode --------------------
// -----------------------------------------------------

ComplexiNode::ComplexiNode() :
    NumericValueNode(new ComplexNumber(0.0, 1.0))
{
}

ReductionType ComplexiNode::GetReductionType()
{
    return nonereduc;
}

char* ComplexiNode::GetNodeText()
{
    static char* ret = (char*)"i";
    return ret;
}
