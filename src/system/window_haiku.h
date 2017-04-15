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

#ifndef AMATH_HAIKU_CONSOLE_WINDOW_H
#define AMATH_HAIKU_CONSOLE_WINDOW_H

#include "amath.h"
#include "amathc.h"
#include "console.h"
#include "lib/aengine.h"

#if defined(HAIKU)

#if __GNUC__ == 2
#pragma GCC diagnostic ignored "-Wno-multichar"
#endif

#include <Window.h>
#include <Entry.h>
#include <FilePanel.h>
#include <MenuBar.h>
#include <String.h>
#include <TextView.h>

class HaikuTextView;

class HaikuWindow : public ConsoleBase, public BWindow
{
public:
    HaikuWindow(const char *prompt, CharValidator *validator);
    virtual ~HaikuWindow(void);
    virtual void MessageReceived(BMessage* msg);
    virtual void FrameResized(float w, float h);
    virtual void UpdateTextRect(void);
    virtual bool QuitRequested(void);
    virtual void Start(void);
    virtual void Exit(void);
    virtual void Clear(void);
    virtual void ShowAbout(void);
    virtual void ShowLicense(void);
    virtual void ShowVersion(void);
    virtual void WriteString(const char *string);
    void Execute(void);

protected:
    virtual void StartMessage(void);

private:
    HaikuTextView *textView;
};

class HaikuTextView : public BTextView
{
public:
    HaikuTextView(
        HaikuWindow *window,
        BRect frame,
        const char *name,
        BRect textRect,
        const BFont *initialFont,
        const rgb_color *initialColor);
    virtual ~HaikuTextView(void);
    virtual void KeyDown(const char *bytes, int32 numBytes);

private:
    HaikuWindow *window;
};

#endif
#endif
