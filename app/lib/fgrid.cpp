/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
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

#include "lib/fgrid.h"
#include "lib/real.h"
#include "main/functions.h"

Grid::Grid(UserFunction* function) :
    function(function)
{
    parameter = new RealNumber();
    zoom = 1.0;
    pad = 8;
}

Grid::~Grid()
{
    delete parameter;
}

double Grid::GetHorizontalResolution()
{
    return (maxX - minX) / (screenMaxX - screenMinX);
}

void Grid::SetFunctionBounderies(double minX, double maxX)
{
    this->minX = minX;
    this->maxX = maxX;
    minY = FunctionValue(minX);
    maxY = FunctionValue(maxX);

    scaleX =  (screenMaxX - screenMinX) / (maxX - minX);
    scaleY =  (screenMaxY - screenMinY) / (maxY - minY);

    // Keep ascpect ratio
    if (scaleX < scaleY) {
        scaleX = scaleY;
    } else {
        scaleY = scaleX;
    }
}

void Grid::SetScreenBounderues(int minX, int maxX, int minY, int maxY)
{
    screenMinX = minX + pad;
    screenMaxX = maxX - pad;
    screenMinY = minY + pad;
    screenMaxY = maxY - pad;

    originX = (screenMaxX - screenMinX) / 2;
    originY = (screenMaxY - screenMinY) / 2;
}

double Grid::FunctionValue(double parameter)
{
    this->parameter->SetRealValue(parameter);
    function->GetVariable()->AssignValue(this->parameter);
    Number *res = function->GetExpression()->Evaluate();
    double value = res->GetRealValue();
    return value;
}

void Grid::GetScreenCoordinates(double value, int *x, int *y)
{
    double valueX = value * scaleX * zoom + originX;
    double valueY = FunctionValue(value) * scaleY * zoom + originY;

    *x = valueX < screenMinX || valueX > screenMaxX ? -1 : (int)valueX;
    *y = valueY < screenMinY || valueY > screenMaxY ? -1 : (int)valueY;
}

void Grid::GetScreenCoordinates(double xval, int* x, double yval, int* y)
{
    double valueX = xval * scaleX * zoom + originX;
    double valueY = yval * scaleY * zoom + originY;

    *x = valueX < screenMinX || valueX > screenMaxX ? -1 : (int)valueX;
    *y = valueY < screenMinY || valueY > screenMaxY ? -1 : (int)valueY;
}

void Grid::GetXAxis(int* xstart, int* xend, int* ystart, int* yend)
{
    *xstart = screenMinX;
    *xend = screenMaxX;
    *ystart = originY;
    *yend = originY;
}

void Grid::GetYAxis(int* xstart, int* xend, int* ystart, int* yend)
{
    *xstart = originX;
    *xend = originX;
    *ystart = screenMinY;
    *yend = screenMaxY;
}
