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

#include "amath.h"
#include "parser.h"
#include "viewer.h"
#include "optimizer.h"
#include "evaluator.h"

Evaluator::Evaluator(const char* input)
{
    this->input = input;
    output = new CharBuffer();
}

Evaluator::~Evaluator()
{
    if (output != nullptr)
    {
        delete output;
    }
}

void Evaluator::Evaluate() const
{
    output->ClearBuffer();

    Parser* parser = new Parser(input);
    SyntaxNode* node = parser->Parse();
    delete parser;

#if defined(DEBUGTREE)
    Viewer* viewer = new Viewer(node);
    const char* vout = viewer->GetTree();
    output->EnsureGrowth(StrLen(vout));
    output->Append(vout);
    delete viewer;
#endif

    Optimizer* optimizer = new Optimizer(node);
    optimizer->Optimize();
    node = optimizer->GetRoot();
    delete optimizer;

#if defined(DEBUGTREE)
    viewer = new Viewer(node);
    vout = viewer->GetTree();
    output->EnsureGrowth(StrLen(vout));
    output->Append(vout);
    delete viewer;

    const char* out = node->Execute();
    output->EnsureGrowth(StrLen(out));
    output->Append(out);
#endif

#ifndef DEBUGTREE
    const char* out = node->Execute();
    output->ClearAndCopy(out);
#endif

    delete node;
}

char* Evaluator::GetResult() const
{
    return output->GetString();
}
