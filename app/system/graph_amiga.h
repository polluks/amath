/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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

#ifndef _AMIGA_GRAPH_WINDOW_H
#define _AMIGA_GRAPH_WINDOW_H

/**
 * @file  agraph.h
 * @brief Amiga OS specific graph window.
 *
 */

#include "clib.h"
#include "lib/real.h"
#include "lib/fgrid.h"
#include "main/functions.h"
#include "system/graph.h"

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

class AmigaGraphWindow : public GraphWindow {
public:
    AmigaGraphWindow();
    ~AmigaGraphWindow();

    void OpenGraphWindow(UserFunction* function);
    void CloseGraphWindow();
    void DrawGraph(UserFunction* function);

private:
    void DrawAxis();

    static const int width = 400;
    static const int height = 300;

    static const double min = -5.0;
    static const double max = +5.0;

    Window *window;
};

#endif
#endif

