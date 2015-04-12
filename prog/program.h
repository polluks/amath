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

#ifndef _PROGRAM_H
#define _PROGRAM_H

/**
 * @file  program.h
 * @brief Program flow and global states.
 *
 */

#include "io/console.h"
#include "io/filesystem.h"
#include "lib/ntext.h"
#include "main/values.h"
#include "main/graphlist.h"
#include "main/functions.h"

class Program;
extern class Program *Program;

/**
* @brief Master control class.
*
* This control class handles all processes and data
* in the entire program. It usually only exist as a
* single instance.
*/
class Program {
public:
    Program();
    ~Program();

    void Run();
    void RunInShell();
    void Exit();
    void NewPositionalInput(short unsigned int base, short unsigned int digits);
    void NewPositionalOutput(short unsigned int base, short unsigned int digits);

    ConsoleBase *Console;
    FilesystemBase *Filesystem;
    NumeralSystem *Input;
    NumeralSystem *Output;
    VariableList *Variables;
    FunctionList *Functions;
    GraphList *Graphs;
};

#endif
