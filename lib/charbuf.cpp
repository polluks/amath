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

#include "def/libc.h"
#include "lib/charbuf.h"

// -----------------------------------------------------
// -------------------- CharBuffer ---------------------
// -----------------------------------------------------

/**
 * @brief Initialize without allocating memory.
 *
 */
CharBuffer::CharBuffer()
{
    buf = NOMEM;
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
    if (buf != NOMEM) {
        delete [] buf;
    }

    buf = NOMEM;
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
    ptr = buf + cursize - 1;
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
    if (buf == NOMEM) {
        unsigned int size = minimumSize;
        buf = new char[size];
        ptr = buf;
    }
}

/**
 * @brief Ensure a memory block of speficied size is allocated.
 *
 */
void CharBuffer::EnsureSize(unsigned int size)
{
    if (cursize < size) {

        unsigned int tempsize = cursize;
        cursize = (size < minimumSize ? minimumSize : size);

        if (buf == NOMEM) { // Nothing allocated yet. Just allocate requested size.
            buf = new char[cursize];
            ptr = buf;
        } else if (buf == ptr) { // Already allocated but buffer is empty.
            delete [] buf;
            buf = new char[cursize];
            ptr = buf;
        } else { // Buffer already in use.
            // Make at least double size
            cursize = cursize < tempsize * 2 ? tempsize * 2 : cursize;
            unsigned int offset = ptr - buf;
            char *temp = new char[cursize];
            MemCopy(temp, buf, tempsize);
            delete [] buf;
            buf = temp;
            ptr = buf + offset;
        }
    }
}

void CharBuffer::EnsureSize(unsigned int blocksize, unsigned int blocks)
{
    if (cursize < blocksize * blocks) {
        if (buf == NOMEM) {
            cursize = blocksize * blocks;
            buf = new char[cursize];
            ptr = buf;
        } else {
            unsigned int tptr = ptr - buf;
            char *temp = new char[blocksize * blocks];
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
    EnsureSize((ptr - buf) + size);
}

bool CharBuffer::Is(const char* string)
{
    return StrIsEqual(GetString(), string);
}

void CharBuffer::Empty()
{
    if (buf == NOMEM) {
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
    const char *s = source->GetString();

    ptr = buf;
    while ((*ptr++ = *s++))
        ;

    ptr--;
}

void CharBuffer::Append(const char c)
{
    *ptr++ = c;
}

void CharBuffer::Append(const char c, unsigned int count)
{
    if (count == 0) {
        return;
    }

    unsigned int n = count;
    while (n--)
        *ptr++ = c;
}

void CharBuffer::Append(const char* source)
{
    while ((*ptr++ = *source++));

    ptr--;
}

bool CharBuffer::RemoveTrailing(const char c)
{
    if (*(ptr - 1) == c) {
        ptr--;
        return true;
    }

    return false;
}

char* CharBuffer::GetString()
{
    *ptr = '\0';
    return buf;
}

