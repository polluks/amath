/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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

#ifndef AMATH_PROGRAM_H
#define AMATH_PROGRAM_H

/**
 * @file  program.h
 * @brief Program flow and global states.
 *
 */

#include "console.h"
#include "language.h"
#include "filesystem.h"
#include "preferences.h"
#include "lib/numb.h"
#include "lib/ntext.h"
#include "main/values.h"
#include "main/functionlist.h"

/**
* @brief Master control class.
* @details
* This control class handles all processes and data
* in the entire program. It usually only exist as a
* single instance.
*/
class Program
{
public:
    Program();
    virtual ~Program();
    virtual void Initialize(int argc, char** argv) = 0;
    virtual void Start() = 0;
    virtual void Exit();
    void NewPositionalInput(short unsigned int base, short unsigned int digits);
    void NewPositionalOutput(short unsigned int base, short unsigned int digits);
    void SetLastResult(Number* number);
    void SetPrompt(const char* text) const;
    int GetExitStatus() const;
    bool GetAnsiMode() const;
    void SetAnsiMode(bool value);
    struct Number* GetLastResult() const;
    class Language* Language;
    class ConsoleBase* Console;
    class PreferencesBase* Preferences;
    class FilesystemBase* Filesystem;
    class NumeralSystem* Input;
    class NumeralSystem* Output;
    class VariableList* Variables;
    class FunctionList* Functions;
    class GraphList* Graphs;

protected:
    void InitAnsiMode();
    bool shellMode;
    bool ansiMode;
    int status;

private:
    struct Number* ins;
};

#endif
