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

#ifndef AMATH_CHAR_BUFFER_H
#define AMATH_CHAR_BUFFER_H

/**
 * @file  charbuf.h
 * @brief String and character array logic
 */

#include "aengine.h"

/**
 * @brief   Encapsulate an character array which can be used as a string
 * @details The CharBuffer class eases the task of allocating a releasing memory.
 */
class CharBuffer
{
public:
    CharBuffer();
    explicit CharBuffer(unsigned int size);
    ~CharBuffer();
    void ClearBuffer();
    void ClearAndCopy(const char* source);
    void ClearAndAlloc(unsigned int size);
    void EnsureSize(unsigned int size);
    void EnsureSize(unsigned int blocksize, unsigned int blocks);
    void EnsureMinimumSize();
    void EnsureGrowth(unsigned int size);

    void Empty();

    bool IsEmpty() const;

    /**
    * @brief Compare content of CharBuffer with string)
    */
    bool Is(const char* string) const;
    bool Contains(const char c) const;

    void Copy(CharBuffer* buf);
    void Append(const char* source);
    void Append(const char c);
    void Append(const char c, unsigned int count);

    void DeleteLastChar();
    bool RemoveTrailing(const char c);
    bool RemoveTrailing(const char* string);
    char* GetString() const;

private:
    friend class AnsiConoleEngine;

    char* buf;
    char* ptr;
    unsigned int cursize;
    static const unsigned int minimumSize = 64;
};

#endif
