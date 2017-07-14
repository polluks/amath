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
#include "console.h"
#include "program.h"
#include "loc/text.h"

static const char *version = TXTVERSMSG;
static const char *compiler = TXTCOMPMSG;
static const char *about = NEWLINE NEWLINE
    "amath features a case sensitive command line interface, internal IEEE 754" NEWLINE
    "calculations with 15 significant digits, calculations with real and complex" NEWLINE
    "numbers, variables and user defined functions, logarithmic and exponential" NEWLINE
    "functions, trigonometric and hyperbolic function and selected mathematical" NEWLINE
    "constants and rounding functions." NEWLINE;
static const char *help =
    "usage: amath [noansi] [shell|expression]" NEWLINE;
static const char *copyright =
    "Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>";
static const char *license =
    "Copyright (c) 2007 The NetBSD Foundation, Inc." NEWLINE
    "Copyright (c) 1990, 1993 The Regents of the University of California." NEWLINE
    "All rights reserved." NEWLINE NEWLINE
    "This code is derived from software written by Stephen L. Moshier." NEWLINE
    "It is redistributed by the NetBSD Foundation by permission of the author." NEWLINE NEWLINE
    "This code is derived from software contributed to Berkeley by" NEWLINE
    "Mike Hibler and Chris Torek." NEWLINE NEWLINE
    "Redistribution and use in source and binary forms, with or without" NEWLINE
    "modification, are permitted provided that the following conditions are met:" NEWLINE NEWLINE
    "* Redistributions of source code must retain the above copyright notice, this" NEWLINE
    "  list of conditions and the following disclaimer." NEWLINE NEWLINE
    "* Redistributions in binary form must reproduce the above copyright notice," NEWLINE
    "  this list of conditions and the following disclaimer in the documentation" NEWLINE
    "  and/or other materials provided with the distribution." NEWLINE NEWLINE
    "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"" NEWLINE
    "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE" NEWLINE
    "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" NEWLINE
    "DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE" NEWLINE
    "FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL" NEWLINE
    "DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR" NEWLINE
    "SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER" NEWLINE
    "CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY," NEWLINE
    "OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE" NEWLINE
    "OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE." NEWLINE NEWLINE;
static const char *footer = "Specific details should be found in the source files.";

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

const char * ConsoleBase::GetVersionText()
{
    return version;
}

const char *ConsoleBase::GetCompilerText()
{
    return compiler;
}

bool ConsoleBase::Open()
{
    return true;
}

void ConsoleBase::Close()
{
}

bool ConsoleBase::SetAnsiMode(bool value)
{
    ansiMode = value;
    return value;
}

void ConsoleBase::ResetConsole()
{
    if (ansiMode)
    {
        static const char *normal = "\x1B[0m";
        WriteString(normal);
    }
}

void ConsoleBase::AnsiBold()
{
    if (ansiMode)
    {
        static const char *bold = "\x1B[1m";
        WriteString(bold);
    }
}

void ConsoleBase::AnsiItalics()
{
    if (ansiMode)
    {
        static const char *italics = "\x1B[3m";
        WriteString(italics);
    }
}

void ConsoleBase::Clear()
{
    if (ansiMode)
    {
        static const char *clear = "\x1B[1;1H\x1B[J";
        WriteString(clear);
        ResetConsole();
    }
    else
    {
        static const char *msg = "Screen can only be cleared in ANSI mode.";
        WriteString(msg);
        WriteString(NEWLINE);
    }
}

void ConsoleBase::ShowHelp()
{
    WriteString(help);
}

void ConsoleBase::ShowVersion()
{
    AnsiBold();
    WriteString(version);
    ResetConsole();
    WriteString(NEWLINE);
    WriteString(compiler);
    WriteString(NEWLINE);
    ResetConsole();
}

void ConsoleBase::ShowAbout()
{
    AnsiBold();
    WriteString(version);
    ResetConsole();
    WriteString(NEWLINE);
    WriteString(compiler);
    ResetConsole();
    WriteString(about);
    ResetConsole();
}

void ConsoleBase::ShowLicense()
{
    WriteString(NEWLINE);
    AnsiBold();
    WriteString(copyright);
    ResetConsole();
    WriteString(NEWLINE);
    WriteString(license);
    AnsiItalics();
    WriteString(footer);
    ResetConsole();
    WriteString(NEWLINE);
    WriteString(NEWLINE);
}

void ConsoleBase::StartMessage()
{
    WriteString(INTROMSG);
    ResetConsole();
}

void ConsoleBase::Prompt()
{
    ResetConsole();
    WriteString(prompt);
    ResetConsole();
}

void ConsoleBase::SetPrompt(const char* string)
{
    delete prompt;
    AllocAndCopy(&prompt, string);
}
