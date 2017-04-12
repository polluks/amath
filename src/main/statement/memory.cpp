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
#include "memory.h"
#include "lib/real.h"
#include "lib/ntextd.h"
#include "loc/text.h"

MemoryStatement::MemoryStatement()
    : StatementNode()
{
}

MemoryStatement::~MemoryStatement()
{
}

char* MemoryStatement::Execute()
{
    long blocks, size, peak;
    MemUsage(&blocks, &size, &peak);
    Number* a = new RealNumber(static_cast<int>(blocks));
    Number* b = new RealNumber(static_cast<int>(size));
    Number* c = new RealNumber(static_cast<int>(peak));

    NumeralSystem* ns = new DecimalSystem(8);
    output->Empty();
    output->EnsureSize(
        StrLen(TXTMEMBLOCKS) + 8 +
        StrLen(TXTMEMSIZE) + 12 +
        StrLen(TXTMEMMAXSIZE) + 12);
    output->Append(TXTMEMBLOCKS);
    output->Append(ns->GetText(a));
    output->Append(NEWLINE);
    output->Append(TXTMEMSIZE);
    output->Append(ns->GetText(b));
    output->Append(NEWLINE);
    output->Append(TXTMEMMAXSIZE);
    output->Append(ns->GetText(c));
    output->Append(NEWLINE);

    delete a;
    delete b;
    delete c;
    delete ns;
    return output->GetString();
}
