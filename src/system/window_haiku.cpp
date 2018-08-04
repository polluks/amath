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
#include "window_haiku.h"
#include "lib/charbuf.h"
#include "lib/aengine.h"
#include "main/evaluator.h"
#include "loc/text.h"

//http://git.netsurf-browser.org/netsurf.git/plain/frontends/beos/about.cpp
//https://notabug.org/Tsyesika/Runyu/src/master/RunyuWindow.cpp

#if defined(HAIKU)

#if __GNUC__ == 2
#pragma GCC diagnostic ignored "-Wno-multichar"
#endif

#include <Application.h>
#include <ScrollView.h>
#include <LayoutBuilder.h>
#include <MenuBar.h>
#include <Window.h>
#include <private/interface/AboutWindow.h>

HaikuWindow::HaikuWindow(const char *prompt, CharValidator *validator) :
    ConsoleBase(prompt),
    BWindow(
        BRect(150, 150, 800, 600),
        TXTTITLE,
        B_TITLED_WINDOW,
        B_ASYNCHRONOUS_CONTROLS
    )
{
    BRect textRect = Bounds();
    textRect.OffsetTo(0, 0);
    textRect.InsetBy(5, 5);

    BFont font(be_fixed_font);
    textView = new HaikuTextView(
        this,
        Bounds(),
        "TextView",
        textRect,
        &font, 0);
    textView->SetStylable(true);
    DetachMemSafe(textView);

    BScrollView *scrollView = new BScrollView(
        TXTTITLE "ScrollView",
        textView,
        B_FOLLOW_ALL,
        0,
        false,
        true);
    DetachMemSafe(scrollView);
    AddChild(scrollView);

    /*
    BMenuBar* menuBar = new BMenuBar("MenuBar");
    BLayoutBuilder::Menu<>(menuBar)
        .AddMenu("File")
            .AddItem("About", B_ABOUT_REQUESTED)
            .AddItem("Quit", B_QUIT_REQUESTED, 'Q')
    .End();
    DetachMemSafe(menuBar);

    BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
            .SetInsets(0)
            .Add(menuBar)
            .Add(scrollView)
    .End();
    */
}

HaikuWindow::~HaikuWindow(void)
{
}

void HaikuWindow::Exit(void)
{
    be_app->PostMessage(B_QUIT_REQUESTED);
}

void HaikuWindow::Start(void)
{
    textView->MakeFocus(true);
    StartMessage();
    Prompt();
    Show();
}

void HaikuWindow::StartMessage(void)
{
    text_run run;
    run.font = be_bold_font;
    run.offset = 0;
    run.color.red = 0;
    run.color.green = 0;
    run.color.blue = 0;
    run.color.alpha = 255;

    text_run_array runArray;
    runArray.count = 1;
    runArray.runs[0] = run;

    textView->Insert(INTROMSG, &runArray);
}

void HaikuWindow::ShowAbout(void)
{
    BAboutWindow* about = new BAboutWindow("About amath", "application/x-vnd.amath");
    DetachMemSafe(about);

    CharBuffer *buf = new CharBuffer();
    static const char* version = TXTTITLE SPACE RELDATESTAMP;
    static const char* compiler = TXTCOMPMSG;
    static const char* footer = "Details specified in license.";
    int len = StrLen(version) + StrLen(compiler) + StrLen(footer) + 10;

    buf->EnsureSize(len);
    buf->Append(version);
    buf->Append(NEWLINE);
    buf->Append(compiler);
    buf->Append(NEWLINE);
    buf->Append(NEWLINE);
    buf->Append(footer);

    about->AddCopyright(2014, "Carsten Sonne Larsen");
    about->AddExtraInfo(buf->GetString());
    about->Show();

    delete buf;
}

void HaikuWindow::ShowLicense(void)
{
    // TODO: Show license in colors
    ConsoleBase::ShowLicense();
}

void HaikuWindow::ShowVersion(void)
{
	text_run run;
	run.font = be_bold_font;
	run.offset = 0;
	run.color.red = 34;
	run.color.green = 139;
	run.color.blue = 34;
	run.color.alpha = 255;
	
	text_run_array runArray;
	runArray.count = 1;
	runArray.runs[0] = run;
	
	textView->Insert(GetVersionText(), &runArray);
    textView->Insert(NEWLINE);

    runArray.runs[0].font = be_plain_font;
    runArray.runs[0].font.SetFace(B_REGULAR_FACE);
	runArray.runs[0].color.red = 0;
	runArray.runs[0].color.green = 0;
	runArray.runs[0].color.blue = 0;

    textView->Insert(GetCompilerText(), &runArray);
    textView->Insert(NEWLINE);
}

void HaikuWindow::Clear(void)
{
    textView->SetText(EMPTYSTRING);
}

void HaikuWindow::WriteString(const char *string)
{
    text_run run;
    run.font = be_fixed_font;
    run.offset = 0;
    run.color.red = 0;
    run.color.green = 0;
    run.color.blue = 0;
    run.color.alpha = 255;

    text_run_array runArray;
    runArray.count = 1;
    runArray.runs[0] = run;

    textView->Insert(string, &runArray);
}

void HaikuWindow::Execute(void)
{
    int lineIndex = textView->CurrentLine();
    int lineStart = textView->OffsetAt(lineIndex);
    int lineCount = textView->CountLines();

    if (lineCount != lineIndex + 1)
    {
        return;
    }

    int len = textView->TextLength() - lineStart;
    char *line = new char[len + 1];
    textView->GetText(lineStart, lineStart + len, line);
    *(line + len) = '\0';

    char *input = line;
    char *p = prompt;
    while (*input == *p && *input != '\0')
    {
        input++;
        p++;
    }

    WriteString(NEWLINE);
    Evaluator *evaluator = new Evaluator(input);
    evaluator->Evaluate();
    const char *out = evaluator->GetResult();
    WriteString(out);

    delete evaluator;
    delete line;

    Prompt();
    textView->ScrollToOffset(textView->TextLength() - 1);
}

void HaikuWindow::MessageReceived(BMessage* msg)
{
    switch (msg->what)
    {
            case B_ABOUT_REQUESTED:
            ShowAbout();
            break;
        default:
            BWindow::MessageReceived(msg);
            break;
    }
}

void HaikuWindow::FrameResized(float w, float h)
{
    UpdateTextRect();
}

void HaikuWindow::UpdateTextRect(void)
{
    BRect rect(textView->Bounds());
    rect.InsetBy(5, 5);
    textView->SetTextRect(rect);
}

bool HaikuWindow::QuitRequested()
{
    Exit();
    return true;
}

HaikuTextView::HaikuTextView(
    HaikuWindow *window,
    BRect frame,
    const char *name,
    BRect textRect,
    const BFont *initialFont,
    const rgb_color *initialColor) :
    BTextView(
        frame,
        name,
        textRect,
        initialFont,
        initialColor,
        B_FOLLOW_ALL, B_WILL_DRAW | B_PULSE_NEEDED
    ), window(window)
{
}

HaikuTextView::~HaikuTextView(void)
{
}

void HaikuTextView::KeyDown(const char *bytes, int32 numBytes)
{
    switch (*bytes)
    {
        case B_ENTER:
            window->Execute();
            break;
        default:
            BTextView::KeyDown(bytes, numBytes);
            break;
    }
}

#endif
