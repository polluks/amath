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

#include "clib.h"
#include "lib/real.h"
#include "lib/fgrid.h"
#include "main/functions.h"
#include "system/graph_amiga.h"

#ifdef AMIGA
#include <exec/types.h>
#include <exec/io.h>
#include <exec/memory.h>
#include <intuition/intuition.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/layers_protos.h>
#include <clib/gadtools_protos.h>
#include <clib/intuition_protos.h>

AmigaGraphWindow::AmigaGraphWindow() :
    GraphWindow()
{
    window = NOMEM;
}

AmigaGraphWindow::~AmigaGraphWindow()
{
    if (window != NOMEM) {
        CloseWindow(window);
    }
}

void AmigaGraphWindow::OpenGraphWindow(UserFunction* function)
{
    grid = new Grid(function);

    window = OpenWindowTags(NULL,
                            WA_Left, 20, WA_Top, 20,
                            WA_Width, width, WA_Height, height,
                            WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_REFRESHWINDOW,
                            WA_Flags, WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET | WFLG_CLOSEGADGET | WFLG_ACTIVATE |
                            WFLG_SMART_REFRESH,
                            WA_Title, (BYTE*)function->GetDefitionName(),
                            TAG_DONE);

    grid->SetScreenBounderues(0, width - 15, 0, height - 15);
    grid->SetFunctionBounderies(min, max);
    DrawAxis();
}

void AmigaGraphWindow::CloseGraphWindow()
{
    //TODO: Implement
}

void AmigaGraphWindow::DrawGraph(UserFunction* function)
{
    RastPort *rp = window->RPort;
    SetAPen(rp, (ULONG)17);
    bool first = true;

    RealNumber *parameter = new RealNumber();
    double x = min;
    double y;
    double step = grid->GetHorizontalResolution();

    int screenX;
    int screenY;

    while (x < max) {
        parameter->SetRealValue(x);
        function->GetVariable()->AssignValue(parameter);
        Number *res = function->GetExpression()->Evaluate();
        y = res->GetRealValue();

        grid->GetScreenCoordinates(x, &screenX, y, &screenY);
        if (screenX != -1 && screenY != -1) {
            if (first) {
                Move(rp, screenX, height - screenY);
                first = false;
            } else {
                Draw(rp, screenX, height - screenY);
            }
        }

        x = x + step;
    }
}

void AmigaGraphWindow::DrawAxis()
{
    const int arrow = 4;
    int xstart, ystart;
    int xend, yend;

    RastPort *rp = window->RPort;
    SetAPen(rp, (ULONG)17);

    grid->GetXAxis(&xstart, &xend, &ystart, &yend);
    Move(rp, xstart, height - ystart);
    Draw(rp, xend, height - yend);

    Draw(rp, xend - arrow,  height - yend + arrow);
    Move(rp, xend, height - yend);
    Draw(rp, xend - arrow,  height - yend - arrow);

    grid->GetYAxis(&xstart, &xend, &ystart, &yend);
    Move(rp, xstart, height - ystart);
    Draw(rp, xend, height - yend);

    Draw(rp, xend - arrow, height - yend + arrow);
    Move(rp, xend, height - yend);
    Draw(rp, xend + arrow, height - yend + arrow);
}

#endif



