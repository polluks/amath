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

#include "amath.h"
#include "amathc.h"
#include "charbuf.h"

/**
 * @brief Initialize without allocating memory.
 *
 */
CharBuffer::CharBuffer()
{
    buf = nullptr;
    ptr = buf;
    cursize = 0;
}

/**
 * @brief Initialize while allocating specified amount of memory.
 *
 */
CharBuffer::CharBuffer(unsigned int size)
{
    cursize = (size < minimumSize ? minimumSize : size);
    buf = new char[cursize];
    ptr = buf;
}

CharBuffer::~CharBuffer()
{
    ClearBuffer();
}

/**
 * @brief Release memory in buffer.
 *
 */
void CharBuffer::ClearBuffer()
{
    if (buf != nullptr)
    {
        delete [] buf;
    }

    buf = nullptr;
    ptr = buf;
    cursize = 0;
}

/**
 * @brief Release memory, allocate and copy source.
 *
 */
void CharBuffer::ClearAndCopy(const char* source)
{
    ClearBuffer();
    cursize = AllocAndCopy(&buf, source);
    ptr = buf + cursize - sizeof(char);
}

/**
 * @brief Release memory and allocate new size.
 *
 */
void CharBuffer::ClearAndAlloc(unsigned int size)
{
    ClearBuffer();
    cursize = (size < minimumSize ? minimumSize : size);
    buf = new char[cursize];
    ptr = buf;
}

void CharBuffer::EnsureMinimumSize()
{
    if (buf == nullptr)
    {
        unsigned int size = minimumSize;
        buf = new char[size];
        ptr = buf;
    }
}

/**
 * @brief Ensure a memory block of specified size is allocated.
 *
 */
void CharBuffer::EnsureSize(unsigned int size)
{
    if (cursize < size)
    {
        unsigned int tempsize = cursize;
        cursize = (size < minimumSize ? minimumSize : size);

        if (buf == nullptr)
        { // Nothing allocated yet. Just allocate requested size.
            buf = new char[cursize];
            ptr = buf;
        }
        else if (buf == ptr)
        { // Already allocated but buffer is empty.
            delete [] buf;
            buf = new char[cursize];
            ptr = buf;
        }
        else
        { // Buffer already in use.
            // Make at least double size
            cursize = cursize < tempsize * 2 ? tempsize * 2 : cursize;
            unsigned int offset = (unsigned int)(ptr - buf);
            char* temp = new char[cursize];
            MemCopy(temp, buf, tempsize);
            delete [] buf;
            buf = temp;
            ptr = buf + offset;
        }
    }
}

void CharBuffer::EnsureSize(unsigned int blocksize, unsigned int blocks)
{
    if (cursize < blocksize * blocks)
    {
        if (buf == nullptr)
        {
            cursize = blocksize * blocks;
            buf = new char[cursize];
            ptr = buf;
        }
        else
        {
            unsigned int tptr = (unsigned int)(ptr - buf);
            char* temp = new char[blocksize * blocks];
            MemCopy(temp, buf, cursize);
            delete [] buf;
            cursize = blocksize * blocks;
            buf = temp;
            ptr = buf + tptr;
        }
    }
}

void CharBuffer::EnsureGrowth(unsigned int size)
{
    EnsureSize((unsigned int)((ptr - buf) + size));
}

bool CharBuffer::IsEmpty() const
{
    char* i = buf;

    if (i == nullptr || buf == ptr)
        return true;

    do
    {
        // Blank space characters
        if (*i != ' ' && *i != '\t' && *i != '\r' && *i != '\n')
            return false;

        i++;
    }
    while (i != ptr);

    return true;
}

bool CharBuffer::Is(const char* string) const
{
    return StrIsEqual(GetString(), string);
}

bool CharBuffer::Contains(const char c) const
{
    char* i = buf;

    if (i == nullptr || buf == ptr)
        return false;

    do
    {
        if (*i == c)
            return true;

        i++;
    }
    while (i != ptr);

    return false;
}

void CharBuffer::Empty()
{
    if (buf == nullptr)
    {
        EnsureMinimumSize();
    }

    ptr = buf;
}

void CharBuffer::DeleteLastChar()
{
    ptr--;
}

void CharBuffer::Copy(CharBuffer* source)
{
    EnsureSize(source->cursize);
    const char* s = source->GetString();

    ptr = buf;
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while ((*ptr++ = *s++));

    ptr--;
}

void CharBuffer::Append(const char c)
{
    *ptr++ = c;
}

void CharBuffer::Append(const char c, unsigned int count)
{
    if (count == 0)
    {
        return;
    }

    unsigned int n = count;
    while (n--)
        *ptr++ = c;
}

void CharBuffer::Append(const char* source)
{
    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    while ((*ptr++ = *source++));

    ptr--;
}

bool CharBuffer::RemoveTrailing(const char c)
{
    if (ptr == buf)
    {
        return false;
    }

    if (*(--ptr) == c)
    {
        return true;
    }

    ptr++;
    return false;
}

bool CharBuffer::RemoveTrailing(const char* string)
{
    int len = StrLen(string) * sizeof(char);
    char* s = ptr - len;
    if (s < buf)
    {
        return false;
    }

    *ptr = '\0';

    if (StrIsEqual(s, string))
    {
        ptr = s;
        return true;
    }

    return false;
}

char* CharBuffer::GetString() const
{
    *ptr = '\0';
    return buf;
}
