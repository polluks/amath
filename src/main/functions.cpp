/*
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
 */

#include "amath.h"
#include "amathc.h"
#include "lib/numb.h"
#include "values.h"
#include "functions.h"
#include "function/defs.h"
#include "function/user.h"
#include "system/program.h"
#include "localize/text.h"


HyperbolicSineNode::HyperbolicSineNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicSineNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicSineNode(expression, text, sys);
}

Number* HyperbolicSineNode::Evaluate()
{
    result = expression->Evaluate()->HypSine();
    return result;
}

HyperbolicCosineNode::HyperbolicCosineNode(ExpressionNode* expression, char* text, char* sys)
: FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicCosineNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicCosineNode(expression, text, sys);
}

Number* HyperbolicCosineNode::Evaluate()
{
    result = expression->Evaluate()->HypCosine();
    return result;
}

HyperbolicTangentNode::HyperbolicTangentNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicTangentNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicTangentNode(expression, text, sys);
}

Number* HyperbolicTangentNode::Evaluate()
{
    result = expression->Evaluate()->HypTangent();
    return result;
}

HyperbolicCotangentNode::HyperbolicCotangentNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicCotangentNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicCotangentNode(expression, text, sys);
}

Number* HyperbolicCotangentNode::Evaluate()
{
    result = expression->Evaluate()->HypCotangent();
    return result;
}

HyperbolicSecantNode::HyperbolicSecantNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicSecantNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicSecantNode(expression, text, sys);
}

Number* HyperbolicSecantNode::Evaluate()
{
    result = expression->Evaluate()->HypSecant();
    return result;
}

HyperbolicCosecantNode::HyperbolicCosecantNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicCosecantNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicCosecantNode(expression, text, sys);
}

Number* HyperbolicCosecantNode::Evaluate()
{
    result = expression->Evaluate()->HypCosecant();
    return result;
}

// -------------------------------------------------------------------------
// --------------------- Inverse Hyperbolic Functions ----------------------
// -------------------------------------------------------------------------

HyperbolicArcsineNode::HyperbolicArcsineNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArcsineNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArcsineNode(expression, text, sys);
}

Number* HyperbolicArcsineNode::Evaluate()
{
    result = expression->Evaluate()->HypArcSine();
    return result;
}

HyperbolicArccosineNode::HyperbolicArccosineNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArccosineNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArccosineNode(expression, text, sys);
}

Number* HyperbolicArccosineNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCosine();
    return result;
}

HyperbolicArctangentNode::HyperbolicArctangentNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArctangentNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArctangentNode(expression, text, sys);
}

Number* HyperbolicArctangentNode::Evaluate()
{
    result = expression->Evaluate()->HypArcTangent();
    return result;
}

HyperbolicArcCotangentNode::HyperbolicArcCotangentNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArcCotangentNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArcCotangentNode(expression, text, sys);
}

Number* HyperbolicArcCotangentNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCotangent();
    return result;
}

HyperbolicArcSecantNode::HyperbolicArcSecantNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArcSecantNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArcSecantNode(expression, text, sys);
}

Number* HyperbolicArcSecantNode::Evaluate()
{
    result = expression->Evaluate()->HypArcSecant();
    return result;
}

HyperbolicArcCosecantNode::HyperbolicArcCosecantNode(ExpressionNode* expression, char* text, char* sys) :
    FunctionNode(expression, text, sys)
{
}

FunctionNode* HyperbolicArcCosecantNode::Create(ExpressionNode* expression, char* text, char* sys)
{
    return new HyperbolicArcCosecantNode(expression, text, sys);
}

Number* HyperbolicArcCosecantNode::Evaluate()
{
    result = expression->Evaluate()->HypArcCosecant();
    return result;
}
