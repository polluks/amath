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

/**
 * @file  program_test.h
 * @brief Tests for arithmetic logic.
 *
 */

#include "program.h"

/**
* @brief Test control class.
*
* This control class handle the execution of tests.
*
*/
class TestProgram : public Program
{
public:
    explicit TestProgram(bool silent);
    virtual ~TestProgram();
    virtual void Initialize(int argc, char** argv);
    virtual void Start();
    virtual void Exit();

private:
    bool silent;
    int pass;
    int fail;

    void RunTests();
    void RunTestset01();
    void RunTestset02();
    void RunTestset03();
    void RunTestset04();
    void RunTestset05();
    void RunTestset06();
    void RunTestset07();
    void RunTestset08();
    void RunTestset09();
    void RunTestset10();
    void RunTestset11();

    void TestExpression(const char* expression, const char* result);
    void TestStatement(const char* statement, const char* result);
    void PerformTest(const char* input, const char* result, bool show, bool check);
    void TestExecution(const char* statement);
};
