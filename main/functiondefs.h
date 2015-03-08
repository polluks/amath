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

#ifndef _FUNCTIONDEFS_H
#define _FUNCTIONDEFS_H

/**
 * @file  functiondefs.h
 * @brief Function defitions for math logic.
 *
 */

#include "main/nodes.h"
#include "main/functions.h"

class FunctionNode;
typedef FunctionNode* (*CreateFunctionNode)(ExpressionNode*);

/**
 * @brief Function defitions of known mathematical functions.
 *
 */
struct functiondef {
    const char *name;
    CreateFunctionNode create;
};

static const functiondef functiondefs[] = {
    { "abs", AbsoluteFunctionNode::Create},
    { "sgn", SignumNode::Create},
    { "round", RoundNode::Create},
    { "trunc", TruncNode::Create},
    { "floor", FloorNode::Create},
    { "ceil", CeilingNode::Create},
    // Supply all variants log and root functions
    { "sqr", SquareRootNode::Create},
    { "sqrt", SquareRootNode::Create},
    { "cbr", CubeRootNode::Create},
    { "cbrt", CubeRootNode::Create},
    { "lb", BinaryLogNode::Create},
    { "log2", BinaryLogNode::Create},
    { "ln", LnRootNode::Create},
    { "lg", LogNode::Create},
    { "log", LogNode::Create},
    { "log10", LogNode::Create},
    { "sin", SineNode::Create},
    { "cos", CosineNode::Create},
    { "tan", TangentNode::Create},
    { "cot", CotangentNode::Create},
    { "sec", SecantNode::Create},
    { "csc", CosecantNode::Create},
    // Supply all variants of inverse functions
    { "asin", ArcSineNode::Create},
    { "acos", ArcCosineNode::Create},
    { "atan", ArcTangentNode::Create},
    { "acot", ArcCotangentNode::Create},
    { "asec", ArcSecantNode::Create},
    { "acsc", ArcCosecantNode::Create},
    { "arsin", ArcSineNode::Create},
    { "arcos", ArcCosineNode::Create},
    { "artan", ArcTangentNode::Create},
    { "arcot", ArcCotangentNode::Create},
    { "arsec", ArcSecantNode::Create},
    { "arcsc", ArcCosecantNode::Create},
    { "arcsin", ArcSineNode::Create},
    { "arccos", ArcCosineNode::Create},
    { "arctan", ArcTangentNode::Create},
    { "arccot", ArcCotangentNode::Create},
    { "arcsec", ArcSecantNode::Create},
    { "arccsc", ArcCosecantNode::Create},
    { "sinh", HyperbolicSineNode::Create},
    { "cosh", HyperbolicCosineNode::Create},
    { "tanh", HyperbolicTangentNode::Create},
    { "coth", HyperbolicCotangentNode::Create},
    { "sech", HyperbolicSecantNode::Create},
    { "csch", HyperbolicCosecantNode::Create},
    // Supply all variants of inverse functions
    { "asinh", HyperbolicArcsineNode::Create},
    { "acosh", HyperbolicArccosineNode::Create},
    { "atanh", HyperbolicArctangentNode::Create},
    { "acoth", HyperbolicArcCotangentNode::Create},
    { "asech", HyperbolicArcSecantNode::Create},
    { "acsch", HyperbolicArcCosecantNode::Create},
    { "arsinh", HyperbolicArcsineNode::Create},
    { "arcosh", HyperbolicArccosineNode::Create},
    { "artanh", HyperbolicArctangentNode::Create},
    { "arcoth", HyperbolicArcCotangentNode::Create},
    { "arsech", HyperbolicArcSecantNode::Create},
    { "arcsch", HyperbolicArcCosecantNode::Create},
    { "arcsinh", HyperbolicArcsineNode::Create},
    { "arccosh", HyperbolicArccosineNode::Create},
    { "arctanh", HyperbolicArctangentNode::Create},
    { "arccoth", HyperbolicArcCotangentNode::Create},
    { "arcsech", HyperbolicArcSecantNode::Create},
    { "arccsch", HyperbolicArcCosecantNode::Create}
};

#endif
