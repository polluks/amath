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

#ifndef AMATH_FUNCTIONLIST_H
#define AMATH_FUNCTIONLIST_H

#include "function/node.h"

struct functiondef;
class UserFunction;

/**
 * @brief A list of user defined functions.
 *
 */
class FunctionList
{
public:
    FunctionList();
    ~FunctionList();
    
    void Clear();
    bool Delete(const char* name, const char* argument);
    static bool IsSystemFunction(const char* name);
    UserFunction* GetFirstFunction() const;
    UserFunction* GetFunctionDef(const char* name);
    UserFunction* GetFunctionDef(const char* name, const char* argument) const;
    FunctionNode* GetFunctionCall(const char* function, ExpressionNode* value) const;
    
    char* List() const;
    char* ListDefinitions() const;
    
private:
    char* ListContent(bool cmdFormat) const;
    CharBuffer* buf;
    UserFunction* first;
    static functiondef* GetSystemFunction(const char* ident);
    static char* FindAlias(const char* ident);
};

#endif
