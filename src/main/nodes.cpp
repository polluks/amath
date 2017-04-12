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
 * http://amath.innolan.net
 * 
 */

#include "amath.h"
#include "amathc.h"
#include "nodes.h"
#include "lib/numb.h"
#include "lib/charbuf.h"
#include "loc/text.h"
#include "system/program.h"

// -----------------------------------------------------
// ------------------- SyntaxNode ----------------------
// -----------------------------------------------------

SyntaxNode::SyntaxNode()
{
    output = new CharBuffer();
    parent = nullptr;
    iterator = nullptr;
    leftBottom = false;
}

SyntaxNode::~SyntaxNode()
{
    delete output;
}

ReductionType SyntaxNode::GetReductionType()
{
    return nonereduc;
}

bool SyntaxNode::GetFirstNode() const
{
    return leftBottom;
}

void SyntaxNode::SetFirstNode()
{
    leftBottom = true;
}

SyntaxNode* SyntaxNode::GetParent() const
{
    return parent;
}

void SyntaxNode::SetParent(SyntaxNode* node)
{
    parent = node;
}

void SyntaxNode::ResetIterator()
{
    iterator = nullptr;
}

// -----------------------------------------------------
// ------------------ ExpressionNode -------------------
// -----------------------------------------------------

ExpressionNode::ExpressionNode() :
    SyntaxNode()
{
    result = nullptr;
}

ExpressionNode::ExpressionNode(Number* value) :
    SyntaxNode()
{
    result = value;
}

ExpressionNode::~ExpressionNode()
{
    if (result != nullptr)
    {
        delete result;
    }
}

NodeType ExpressionNode::GetNodeType()
{
    return expression;
}

bool ExpressionNode::IsSilent()
{
    return false;
}

char* ExpressionNode::GetTextCode()
{
    return GetNodeText();
}

char* ExpressionNode::Execute()
{
    return nullptr;
}

// -----------------------------------------------------
// -------------------- ErrorNode ----------------------
// -----------------------------------------------------

ErrorNode::ErrorNode(const char* input, const char* message, const char* parameter, int pos) :
    SyntaxNode(), pos(pos)
{
    this->input = new char[StrLen(input) + 1];
    StrCopyVisible(this->input, input);

    CharBuffer* temp = new CharBuffer();
    temp->EnsureSize(StrLen(message) + StrLen(parameter) + 1);
    temp->Append(message);
    temp->Append(parameter);
    AllocAndCopy(&this->message, temp->GetString());
    delete temp;
}

ErrorNode::ErrorNode(const char* input, int pos) :
    SyntaxNode(), pos(pos)
{
    char* temp = HELPSYNTAX;
    this->input = new char[StrLen(input) + 1];
    StrCopyVisible(this->input, input);
    AllocAndCopy(&this->message, temp);
}

ErrorNode::~ErrorNode()
{
    delete [] input;
    delete [] message;
}

NodeType ErrorNode::GetNodeType()
{
    return othernodetype;
}

char* ErrorNode::GetTextCode()
{
    static char* ret = (char*)"ERRND";
    return ret;
}

char* ErrorNode::Execute()
{
    output->ClearAndAlloc(StrLen(message) + StrLen(input) + pos + 1 + StrLen(NEWLINE) * 3 + 1);
    output->Empty();
    output->Append(message);
    output->Append(NEWLINE);
    output->Append(input);
    output->Append(NEWLINE);
    output->Append(' ', pos);
    output->Append('^');
    output->Append(NEWLINE);

    return output->GetString();
}

void ErrorNode::StrCopyVisible(char* destination, const char* source)
{
    while (*source != '\0' && *source >= 32 && *source <= 126)
    {
        *destination++ = *source++;
    }

    *destination = '\0';
}

SyntaxNode* ErrorNode::GetNext()
{
    return nullptr;
}

void ErrorNode::Attach(SyntaxNode* node)
{
}

void ErrorNode::Detach(SyntaxNode* node)
{
}

void ErrorNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
}

// -----------------------------------------------------
// ----------------- StatementBlockNode ----------------
// -----------------------------------------------------

StatementBlockNode::StatementBlockNode() :
    SyntaxNode()
{
    first = nullptr;
    iterator = nullptr;
}

StatementBlockNode::~StatementBlockNode()
{
    StatementBlockElement* e = first;

    while (e != nullptr)
    {
        StatementBlockElement* next = e->next;
        delete e->statement;
        delete e;
        e = next;
    }
}

NodeType StatementBlockNode::GetNodeType()
{
    return statement;
}

void StatementBlockNode::Add(SyntaxNode* node)
{
    if (first == nullptr)
    {
        first = new StatementBlockElement();
        first->statement = node;
        first->next = nullptr;
        return;
    }

    StatementBlockElement* last = first;
    StatementBlockElement* current = first->next;

    while (current != nullptr)
    {
        current = current->next;
        last = last->next;
    }

    current = new StatementBlockElement();
    current->statement = node;
    current->next = nullptr;
    last->next = current;
}

char* StatementBlockNode::GetTextCode()
{
    static char* ret = (char*)"SBLCK";
    return ret;
}

char* StatementBlockNode::Execute()
{
    output->ClearBuffer();
    output->Empty();

    StatementBlockElement* e = first;
    while (e != nullptr)
    {
        const char* out = e->statement->Execute();
        output->EnsureGrowth(StrLen(out) + 1);
        output->Append(out);
        e = e->next;
    }

    return output->GetString();
}

SyntaxNode* StatementBlockNode::GetNext()
{
    // TODO: Implement GetNext in StatementBlockNode
    return nullptr;
}

void StatementBlockNode::Attach(SyntaxNode* node)
{
}

void StatementBlockNode::Detach(SyntaxNode* node)
{
    // TODO: Implement Detach in StatementBlockNode
}

void StatementBlockNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    // TODO: Implement Replace in StatementBlockNode
}
