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

#ifndef AMATH_FUNCTION_DEFS_H
#define AMATH_FUNCTION_DEFS_H

/**
 * @file  defs.h
 * @brief Function definitions for math logic.
 *
 */

#include "absolute.h"
#include "aexcosecant.h"
#include "aexsecant.h"
#include "arccos.h"
#include "arcchord.h"
#include "arcsin.h"
#include "arctan.h"
#include "arccosecant.h"
#include "arccotangent.h"
#include "arcsecant.h"
#include "arccovercosine.h"
#include "arccoversine.h"
#include "archacovercosine.h"
#include "archacoversine.h"
#include "archavercosine.h"
#include "archaversine.h"
#include "arcvercosine.h"
#include "arcversine.h"
#include "ceil.h"
#include "chord.h"
#include "cosecant.h"
#include "cosine.h"
#include "cotangent.h"
#include "covercos.h"
#include "coversin.h"
#include "cube.h"
#include "excosecant.h"
#include "exsecant.h"
#include "floor.h"
#include "hacovercos.h"
#include "hacoversin.h"
#include "havercos.h"
#include "haversin.h"
#include "hyparccosecant.h"
#include "hyparccosine.h"
#include "hyparccotangent.h"
#include "hyparcsecant.h"
#include "hyparcsine.h"
#include "hyparctangent.h"
#include "hypcosecant.h"
#include "hypcosine.h"
#include "hypcotangent.h"
#include "hypsecant.h"
#include "hypsine.h"
#include "hyptangent.h"
#include "ln.h"
#include "log2.h"
#include "log10.h"
#include "round.h"
#include "secant.h"
#include "signum.h"
#include "sine.h"
#include "trunc.h"
#include "square.h"
#include "tangent.h"
#include "vercos.h"
#include "versin.h"

#include "main/nodes.h"

class FunctionNode;
typedef FunctionNode* (*CreateFunctionNode)(ExpressionNode*, char*, char*);

/**
 * @brief Function definitions of known mathematical functions.
 *
 */
struct functiondef
{
    const char* name;
    CreateFunctionNode create;
};

static const functiondef functiondefs[] = {
    {"abs", AbsoluteFunctionNode::Create},
    {"sgn", SignumNode::Create},
    {"round", RoundNode::Create},
    {"trunc", TruncNode::Create},
    {"floor", FloorNode::Create},
    {"ceil", CeilingNode::Create},
    {"sqrt", SquareRootNode::Create},
    {"cbrt", CubeRootNode::Create},
    {"lb", BinaryLogNode::Create},
    {"ln", LnRootNode::Create},
    {"lg", LogNode::Create},
    {"sin", SineNode::Create},
    {"cos", CosineNode::Create},
    {"tan", TangentNode::Create},
    {"tg", TangentNode::Create},
    {"cot", CotangentNode::Create},
    {"cotan", CotangentNode::Create},
    {"cotg", CotangentNode::Create},
    {"ctg", CotangentNode::Create},
    {"ctn", CotangentNode::Create},
    {"sec", SecantNode::Create},
    {"csc", CosecantNode::Create},
    {"cosec", CosecantNode::Create},
    {"crd", ChordNode::Create},
    {"exsec", ExsecantNode::Create},
    {"excsc", ExcosecantNode::Create},
    {"asin", ArcSineNode::Create},
    {"acos", ArcCosineNode::Create},
    {"atan", ArcTangentNode::Create},
    {"acot", ArcCotangentNode::Create},
    {"asec", ArcSecantNode::Create},
    {"acsc", ArcCosecantNode::Create},
    {"acrd", ArcChordNode::Create},
    {"aexsec", ArcExsecantNode::Create},
    {"aexcsc", ArcExcosecantNode::Create},
    {"sinh", HyperbolicSineNode::Create},
    {"cosh", HyperbolicCosineNode::Create},
    {"tanh", HyperbolicTangentNode::Create},
    {"coth", HyperbolicCotangentNode::Create},
    {"sech", HyperbolicSecantNode::Create},
    {"csch", HyperbolicCosecantNode::Create},
    {"asinh", HyperbolicArcsineNode::Create},
    {"acosh", HyperbolicArccosineNode::Create},
    {"atanh", HyperbolicArctangentNode::Create},
    {"acoth", HyperbolicArcCotangentNode::Create},
    {"asech", HyperbolicArcSecantNode::Create},
    {"acsch", HyperbolicArcCosecantNode::Create},
    {"ver", VersedSineNode::Create},
    {"vcs", VersedCosineNode::Create},
    {"cvs", CoversedSineNode::Create},
    {"cvc", CoversedCosineNode::Create},
    {"hv", HaVersedSineNode::Create},
    {"hvc", HaVersedCosineNode::Create},
    {"hcv", HaCoversedSineNode::Create},
    {"hcc", HaCoversedCosineNode::Create},
    {"aver", ArcVersedSineNode::Create},
    {"avcs", ArcVersedCosineNode::Create},
    {"acvs", ArcCoversedSineNode::Create},
    {"acvc", ArcCoversedCosineNode::Create},
    {"ahv", ArcHaVersedSineNode::Create},
    {"ahvc", ArcHaVersedCosineNode::Create},
    {"ahcv", ArcHaCoversedSineNode::Create},
    {"ahcc", ArcHaCoversedCosineNode::Create}
};

#endif
