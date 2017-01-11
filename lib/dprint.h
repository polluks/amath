/******************************************************************************
  Copyright (c) 2014 Ryan Juckett
  http://www.ryanjuckett.com/

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
     distribution.
*******************************************************************************
  Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  The origin source code can be obtained from:
  http://www.ryanjuckett.com/

******************************************************************************/

#ifndef RJX_DPRINT_H
#define RJX_DPRINT_H

/**
 * @file  dprint.h
 * @brief Format defitions used in the Dragon4 library
 *
 */

#include "dstandard.h"

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
//******************************************************************************
enum tPrintFloatFormat
{
    PrintFloatFormat_Positional,    // [-]ddddd.dddd
    PrintFloatFormat_Scientific,    // [-]d.dddde[sign]ddd
};

//******************************************************************************
// Print a 32-bit floating-point number as a decimal string.
// The output string is always NUL terminated and the string length (not
// including the NUL) is returned.
//******************************************************************************
tU32 PrintFloat32
(
    tC8 *               pOutBuffer,     // buffer to output into
    tU32                bufferSize,     // size of pOutBuffer
    tF32                value,          // value to print
    tPrintFloatFormat   format,         // format to print with
    tS32                precision,      // If negative, the minimum number of digits to represent a
    tC8                 decimalPoint    // Character before the decimals
    // unique 32-bit floating point value is output. Otherwise,
    // this is the number of digits to print past the decimal point.
);

//******************************************************************************
// Print a 64-bit floating-point number as a decimal string.
// The output string is always NUL terminated and the string length (not
// including the NUL) is returned.
//******************************************************************************
tU32 PrintFloat64
(
    tC8 *               pOutBuffer,     // buffer to output into
    tU32                bufferSize,     // size of pOutBuffer
    tF64                value,          // value to print
    tPrintFloatFormat   format,         // format to print with
    tS32                precision,      // If negative, the minimum number of digits to represent a
    tC8                 decimalPoint    // Character before the decimals
    // unique 64-bit floating point value is output. Otherwise,
    // this is the number of digits to print past the decimal point.
);

#ifdef __cplusplus
}
#endif

#endif

