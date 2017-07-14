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
#include "amathc.h"
#include "viewer.h"
#include "lib/charbuf.h"

#if defined(DEBUGTREE)

Viewer::Viewer(SyntaxNode* root)
{
    this->root = root;
    output = new CharBuffer();
}

Viewer::~Viewer()
{
    delete output;
}

char* Viewer::GetTree() const
{
    output->ClearBuffer();
    Structure(root, 0);
    output->EnsureGrowth(42);
    output->Append('\n');
    output->Append('-', 40);
    output->Append('\n');

    return output->GetString();
}

void Viewer::Structure(SyntaxNode* node, int level) const
{
    if (node == nullptr)
    {
        output->EnsureGrowth(1);
        output->Append('~');
    }
    else
    {
        node->ResetIterator();
        Structure(node->GetNext(), level + 1);
        output->EnsureGrowth(level + StrLen(node->GetTextCode() + 1));
        output->Append('\t', level);
        output->Append(node->GetTextCode());
        output->Append('\n');
        Structure(node->GetNext(), level + 1);
    }
}

#endif
