/*-
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

/**
 * @file  doc.h
 * @brief Documentation in doxygen format.
 *
 */

/*!
  \mainpage Simple command line calculator
  \section  intro_sec Introduction

  A mathematical calculator capable of evaluating arithmetic expressions.
  Main features include:
  - Case sensitive command line interface
  - Native IEEE 754 with 15 significant digits
  - Calculations with real and complex numbers
  - Variables and user defined functions
  - Logarithmic and exponential functions
  - Trigonometric and hyperbolic functions
  - Mathematical constants and rounding functions
  - Disk functions to load, save and view content
  - Comprehensive and easy to use built-in help
  - Freely distributable sources (BSD \ref license_page)

  \subsection install Installation
  Install by copying the desired amath binary to C: or any other appropriate location.

  \subsection usage Usage
  amath supply 50 \ref command_page combined with 7 arithmetic operators:
  \verbatim
      +     Mathematical addition.
      -     Mathematical subtraction.
      *     Mathematical multiplication.
      /     Mathematical division.
      ^     Mathematical exponentiation.
      =     Assignment of variable values.
      |     Absolute value of number.
  \endverbatim

  Do a calculation in shell (CLI mode):
  > amath 1.2+1.4

  Get an interactive promt in shell:
  > amath shell

  Show version string:
  > amath version

  Open amath in its own window:
  > amath

  \subsection license License
  amath is open source. The main repository is located at gitlab:<BR>
  https://gitlab.com/rnger/amath

  \subsection download Download
  Prebuild packages are available from:<BR>
  Windows: http://innolan.net/amath-1.6.1-win32.exe<BR>
  (SHA256 58dc5906723b7f66e0bfe1c15d90dc28913ef5b9ea63e227a59a9e42ccdaefb5)<BR>
  <BR>
  FreeBSD: https://www.freshports.org/math/amath/<BR>
  
  \subsection history History
  A full \ref release_page is available for amath.


  \page    command_page Statements and functions
  \section command_sec  Statements and functions

  \subsection command_stat Statements
  \verbatim
  clear       Clear the console window.
  def         Define function.
  delete      Delete variable or function.
  digits      Set number of significant digits.
  eval        Evaluate arithmetic expression.
  execute     Execute statements in a file.
  functions   Show list of user defined functions.
  help        Show basic help text.
  list        Show the content of a directory.
  show        Show the content of a file.
  load        Load variable and functions from file.
  save        Save variable and functions to file.
  variables   Show list of variables.
  version     Show version string.
  exit        Exit program.
  \endverbatim
  \subsection command_func Base functions
  \verbatim
  abs         Absolute value of number.
  sgn         Mathematical signum function.
  round       Round to nearest integer number.
  trunc       Discard fraction part of number.
  floor       Mathematical floor function.
  ceil        Mathematical ceiling function.
  sqrt        Square root function (exp 1/2).
  cbrt        Cube root function (exp 1/3).
  lb          Binary logarithm function (base 2).
  ln          Natural logarithm function (base e).
  lg          Common logarithm function (base 10).
  \endverbatim
  \subsection command_trig Trigonometric functions
  \verbatim
  sin         Trigonometric sine function.
  cos         Trigonometric cosine function.
  tan         Trigonometric tangent function.
  cot         Trigonometric cotangent function.
  sec         Trigonometric secant function.
  csc         Trigonometric cosecant function.
  arcsin      Inverse trigonometric sine function.
  arccos      Inverse trigonometric cosine function.
  arctan      Inverse trigonometric tangent function.
  arccot      Inverse trigonometric cotangent function.
  arcsec      Inverse trigonometric secant function.
  arccsc      Inverse trigonometric cosecant function.
  \endverbatim
  \subsection command_hype Hyperbolic functions
  \verbatim
  sinh        Hyperbolic sine function.
  cosh        Hyperbolic cosine function.
  tanh        Hyperbolic tangent function.
  coth        Hyperbolic cotangent function.
  sech        Hyperbolic secant function.
  csch        Hyperbolic cosecant function.
  arcsinh     Inverse hyperbolic sine function.
  arccosh     Inverse hyperbolic cosine function.
  arctanh     Inverse hyperbolic tangent function.
  arccoth     Inverse hyperbolic cotangent function.
  arcsech     Inverse hyperbolic secant function.
  arccsch     Inverse hyperbolic cosecant function.
  \endverbatim
  \subsection command_exfunc Example script
  \verbatim
  round(1.5461);round(-1.5461);
  ceil(43.5461);ceil(-43.5461);
  floor(39.9531);floor(-39.9531);
  trunc(23.827);trunc(-23.827);
  sqrt(100);sqrt(52.23);
  \endverbatim
  \subsection command_exuserfunc Example script with functions
  \verbatim
  f(x)=x*2+1;
  g(y)=y^2+y*1.5+2;
  a=2;b=3;c=a+b;
  vars;funcs;
  f(2.2);c+1.1;
  \endverbatim
  \subsection command_excomplex Example script with complex numbers
  \verbatim
  cos(1+2i);
  sin(1+2i);
  tan(1+2i);
  coth(1+2i);
  sech(1+2i);
  csch(1+2i);
  \endverbatim


  \page    license_page License
  \section license_sec  License
  amath is using a permissive free software licenses.

  \subsection license_bsd  BSD License  
  <BLOCKQUOTE><PRE>
  Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  </PRE></BLOCKQUOTE>

  Some functions defined in complex.h
  <BLOCKQUOTE><PRE>
  Copyright (c) 2007 The NetBSD Foundation, Inc.
  All rights reserved.

  This code is derived from software written by Stephen L. Moshier.
  It is redistributed by the NetBSD Foundation by permission of the author.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
  </PRE></BLOCKQUOTE>

  Some functions defined in clib.h
  <BLOCKQUOTE><PRE>
  Copyright (c) 1990, 1993
  The Regents of the University of California.  All rights reserved.

  This code is derived from software contributed to Berkeley by
  Mike Hibler and Chris Torek.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  4. Neither the name of the University nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
  </PRE></BLOCKQUOTE>

  \subsection license_tem Template
  A template for The BSD 2-Clause License are available from the
  Open Source Initiative and Wikipidia<BR>
  http://opensource.org/licenses/BSD-2-Clause<BR>
  http://en.wikipedia.org/wiki/BSD_licenses<BR>


  \page    release_page Release history
  \section release_sec  Release history

  \subsection version161 v1.6.1 January 21 2017
  - Fixed language bug in Windows
  - Fixed potential memory bugs
  - Clang compiler support
  - Update copyright texts
  - New doxygen documentation

  \subsection version160 v1.6.0 April 7 2016
  - Complete internal restructure of source code.
  - Fixed several minor bugs in calculation.
  - Support for Windows & Linux.
  - Custom memory handling.
  - Localization support.

  \subsection version154 1.5.4 March 04 2015
  - Fixed several bugs in output of significant digits.
  - Fixed sign bug in addition of negative complex numbers.
  - Fixed sign bug in inverse hyperbolic cosine of complex numbers.
  - Fixed sign bug in inverse hyperbolic secant of complex numbers.
  - Fixed calculation bug in division of real number with complex number.
  - Fixed calculation bug in exponentiation with complex number.
  - Implemented reduction of unary sign in expressions.
  - Implemented reduction of complex numbers in expressions.
  - Implemented internal optimization of expression trees.
  - Miscellaneous internal code optimization.
  - Changed to Amiga hosted GCC compiler (ADE).
  - Verified calculation through 192 test cases.

  \subsection version153 1.5.3 October 26 2014
  - Changed iconed versions to run directly from Workbench.
  - Reconfigured builds to avoid erroneous calculations.
  - Removed broken support for numeral systems.
  - Switched to new floating output library.
  - Reintroduced 68020 FPU and 68030 version.

  \subsection version152 1.5.2 October 11 2014
  - Modified character handling code to comply with licenses.
  - Modified complex math code to comply with licenses.
  - Modified code base to work with Kickstart 2.04.
  - Square root of negative numbers now yield correct result.
  - Implemented scientific notation of numbers.
  - Infinity is now shown in division with 0.
  - Fixed bug in number code sometimes yielding 0.
  - Switched to Amiga memory allocation.
  - Fixed out-of-memory bug.
  - Miscellaneous bug fixes.
  - Removed dead code.
  - Added icons.

  \subsection version151 1.5.1 September 28 2014
  - Improved navigation with arrow keys.
  - Improved text and color compositions.
  - Implemented missing complex functions.
  - Fixed bug in negative complex numbers.
  - Fixed file I/O bug in shell mode.
  - Fixed shell flush bug on AROS.
  - Fixed clear console bug on AROS.
  - Miscellaneous minor bug fixes.

  \subsection version15 1.5 September 21 2014
  - Calculation with complex numbers.
  - Fixed command line version.
  - Miscellaneous bug fixed.
  - Fixed spelling mistakes in help files.
  - Documentation including class diagrams in HTML format.
  - Scripts for porting and building the source.

  \subsection version14 1.4 August 24 2014
  - New math engine based on Sun Microsystems fdlibm (64 bit IEEE 754).
  - Support for positional numeral systems including binary, octal and hexadecimal.
  - Added pure command line version (CLI) as addition to the stand-alone version.
  - Added statement to clear all in-memory variables and functions.
  - Fixed bug causing console to close when entering an empty statement.
  - Fixed bug causing application to hang when loading files with KS 2.0.4.
  - Fixed accuracy bug when using pi and e.
  - Restructured and improved built-in help.
  - Added new 68030 and FPU versions.

  \subsection version132 1.3.2 August 11 2014
  - Fixed two severe bugs causing memory corruption.

  \subsection version131 1.3.1 August 08 2014
  - AROS i386 version released.

  \subsection version13 1.3 August 06 2014
  - All trigonometric and hyperbolic functions are now supported.
  - Runs in console window. amath no longer depends on a shell.
  - Hardened code. amath is no longer a beta version.
  - Added support for disk based activities.
  - Fixed bug in exponentiation operator.
  - Reverted back to clib math.
  - Fixed a few memory leak bugs.
  - Optimized generated binaries.
  - Comments added in source code.
  - Improved error handling.
  - Improved built-in help.
  - Simplified license.

  \subsection version12b 1.2b July 21 2014
  - Root functions added.
  - User defined functions added.
  - Improved error handling.
  - Improved build-in help.
  - Binary support for additional processors.
  - Miscellaneous bug fixes.
  - Source files restructured.

  \subsection version11b 1.1b July 13 2014
  - Minor bug fixes.
  - Source code released.

  \subsection version10b 1.0b July 11 2014
  - First public release.

*/