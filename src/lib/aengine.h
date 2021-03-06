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

#ifndef AMATH_ANSI_CONSOLE_ENGINE
#define AMATH_ANSI_CONSOLE_ENGINE

/**
 * @file  aengine.h
 * @brief ANSI Console Engine
 */

class CharBuffer;
class CharValidator;

/**
 * @brief   ANSI console controller
 * @details
 * More info on the ANSI console is available at Wikipedia:
 * https://wikipedia.org/wiki/ANSI_escape_code
 */
class AnsiConoleEngine
{
public:
    AnsiConoleEngine(const char* prompt, CharValidator* validator);
    ~AnsiConoleEngine();

    void StartInput();
    bool InputDone() const;
    const char* GetLine() const;
    void SetPrompt(const char* string);
    const char* ProcessChar(const unsigned char character);
    void Enable();
    void Disable();

private:
    void CopyLine();
    void ShowLast();
    void ShowNext();

    char* prompt;
    bool enabled;

    static const int maxLines = 100;
    static const int lineSize = 1024;
    char** lines;
    CharBuffer* linebuf;
    CharValidator* validator;
    unsigned int len;
    char* cursor;
    char* endpos;

    int curline; // Index of last (current) line in buffer array
    int showline; // Index of line being shown in buffer array
    bool lineswap; // True if array swapped in progress
    char* editline; // Line being edited (will be next to copy to array)

    bool escmode;
    bool csimode;
    bool delmode;
    bool linedone;
    CharBuffer* out;
};

#endif
