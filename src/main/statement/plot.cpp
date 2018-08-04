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

#include "plot.h"
#include "amath.h"
#include "amathc.h"
#include "lib/ntextd.h"
#include "system/program.h"
#include "../fgrid.h"
#include "../userfunction.h"

PlotStatement::PlotStatement(const char* name, const char* parameter, const char* file) :
    StatementNode()
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
    AllocAndCopy(&this->file, file);
}

PlotStatement::PlotStatement(const char* name, const char* parameter) :
    StatementNode()
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
    file = nullptr;
}

PlotStatement::~PlotStatement()
{
    delete [] name;
    delete [] parameter;

    if (file != nullptr)
    {
        delete [] file;
    }
}

char* PlotStatement::Execute()
{
    UserFunction* function = Program->Functions->GetFunctionDef(name, parameter);

    if (function == nullptr)
    {
        return (char*)("Function does not exists." NEWLINE);
    }

    output->Empty();

    Grid* grid = new Grid(function);
    static const int width = 400;
    static const int height = 300;

    grid->SetScreenBounderues(0, width, 20, height);
    bool first = true;

    static const double min = -5.0;
    static const double max = +5.0;
    grid->SetFunctionBounderies(min, max);

    double x = min;
    double step = grid->GetHorizontalResolution();

    int screenX;
    int screenY;

    RealNumber* n = new RealNumber();
    NumeralSystem* ns = new DecimalSystem(5);

    while (x < max)
    {
        grid->GetScreenCoordinates(x, &screenX, &screenY);

        output->EnsureGrowth(32);

        if (screenX != -1 && screenY != -1)
        {
            if (first)
            {
                output->Append('(');
                n->SetRealValue(screenX);
                output->Append(ns->GetText(n));
                output->Append(',');
                n->SetRealValue(height - screenY);
                output->Append(ns->GetText(n));
                output->Append(')');
                output->Append(NEWLINE);
                first = false;
            }
            else
            {
                output->Append('(');
                n->SetRealValue(screenX);
                output->Append(ns->GetText(n));
                output->Append(',');
                n->SetRealValue(height - screenY);
                output->Append(ns->GetText(n));
                output->Append(')');
                output->Append(NEWLINE);
            }
        }

        x = x + step;
    }

    delete n;
    delete ns;
    delete grid;

    return output->GetString();
}
