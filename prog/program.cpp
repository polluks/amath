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

#include "def/io.h"
#include "def/libc.h"
#include "io/console.h"
#include "io/filesystem.h"
#include "main/parser.h"
#include "main/values.h"
#include "main/functions.h"
#include "main/graphlist.h"
#include "prog/program.h"

class Program *Program;

Program::Program()
{
    Input = new DecimalSystem(9);
    Output = new DecimalSystem(9);
    Variables = new VariableList();
    Functions = new FunctionList();
    Graphs = new GraphList();
    Filesystem = CreateFilesystem();
    Console = CreateWindow();
}

Program::~Program()
{
    delete Variables;
    delete Functions;
    delete Graphs;
    delete Input;
    delete Output;
    delete Filesystem;
    delete Console;
}

void Program::NewPositionalInput(short unsigned int base, short unsigned int digits)
{
    delete Input;

    if (digits == 10) {
        Input = new DecimalSystem(digits);
    } else {
        Input = new PositionalNumeralSystem(base, digits);
    }
}

void Program::NewPositionalOutput(short unsigned int base, short unsigned int digits)
{
    delete Output;

    if (digits == 10) {
        Output = new DecimalSystem(digits);
    } else {
        Output = new PositionalNumeralSystem(base, digits);
    }
}

void Program::RunInShell()
{
    delete Console;
    Console = CreateShell();
    Console->Run();
}

void Program::Run()
{
    Console->Run();
}

void Program::Exit()
{
    Console->Exit();
}
