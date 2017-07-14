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

#include "user.h"
#include "amathc.h"

UserFunctionNode::UserFunctionNode(UserFunction* function, ExpressionNode* parameter) :
    FunctionNode(parameter, nullptr, nullptr), function(function)
{
}

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
    if (iterator == nullptr)
    {
        iterator = function->GetExpression();
        return iterator;
    }

    return nullptr;
}

void UserFunctionNode::Attach(SyntaxNode* node)
{
    // TODO: Implement Attach in UserFunctionNode
}

void UserFunctionNode::Detach(SyntaxNode* node)
{
    // TODO: Implement Detach in UserFunctionNode
}

void UserFunctionNode::Replace(SyntaxNode* n, SyntaxNode* x)
{
    // TODO: Implement Replace in UserFunctionNode
}
