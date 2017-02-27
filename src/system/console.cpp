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
#include "amath.h"
#include "amathc.h"
#include "localize/text.h"
#include "system/console.h"
#include "system/program.h"

ConsoleBase::ConsoleBase(const char* prompt)
{
    AllocAndCopy(&this->prompt, prompt);
}

ConsoleBase::~ConsoleBase()
{
    delete prompt;
}

const char* ConsoleBase::GetName()
{
    return CPROCNAME;
}

void ConsoleBase::Clear()
{
    WriteString(CLEARWINDOW);
    WriteString(NORMALTEXT);
}

void ConsoleBase::StartMessage()
{
    WriteString(INTROMSG);
    WriteString(NORMALTEXT);
}

void ConsoleBase::Prompt()
{
    WriteString(NORMALTEXT);
    WriteString(prompt);
    WriteString(NORMALTEXT);
}

void ConsoleBase::SetPrompt(const char* string)
{
    delete prompt;
    AllocAndCopy(&prompt, string);
}