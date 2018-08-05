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
      +     Mathematical addition
      -     Mathematical subtraction
      *     Mathematical multiplication
      /     Mathematical division
      ^     Mathematical exponentiation
      =     Assignment of variable values
      |     Absolute value of number
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
  https://gitlab.com/rnger/amath <BR>
  <BR>
  Github has a mirror:<BR>
  https://github.com/rainlance/amath

  \subsection download Download
  FreeBSD: <a href="https://www.freshports.org/math/amath/">freshports.org</a><BR>
  Haiku OS: <a href="https://depot.haiku-os.org/#!/pkg/amath/haikuports/1/8/3/-/1/x86_gcc2">depot.haiku-os.org</a><BR>
  Mac OS X and Linux: <a href="https://pkgsrc.joyent.com">pkgsrc.joyent.com</a><<BR>
  NetBSD:  <a href="http://ftp.netbsd.org/pub/pkgsrc/current/pkgsrc/math/amath/README.html">netbsd.org</a> and
           <a href="http://pkgsrc.se/math/amath">pkgsrc.se</a><BR>
  Windows: <a href="http://amath.innolan.net/amath-1.8.3-win.zip">amath.innolan.net</a><BR>
  Other packages: <a href="http://ftp.innolan.net/pub/amath/">ftp.innolan.net</a>
  \subsection history History
  A full \ref release_page is available for amath.

  \page    command_page Statements and functions
  \section command_sec  Statements and functions

  \subsection command_stat Statements
  \verbatim

  about       Show about text
  clear       Clear console window
  def         Define function
  delete      Delete variable or function
  digits      Set number of significant digits
  eval        Evaluate arithmetic expression
  execute     Execute statements in a file
  functions   Show list of user defined functions
  input       Change numeral input system
  help        Show basic help text
  output      Change numeral output system
  list        Show content of a directory
  show        Show content of a file
  load        Load variable and functions from file
  save        Save variable and functions to file
  variables   Show list of variables
  version     Show version string
  license     Show copyright and license texts
  memory      Show internal memory usage
  exit        Exit program
  \endverbatim
  \subsection command_func Miscellaneous functions
  \verbatim
  abs         Absolute value of number
  sgn         Mathematical signum function
  round       Round to nearest integer number
  trunc       Discard fraction part of number
  floor       Mathematical floor function
  ceil        Mathematical ceiling function
  sqrt        Square root function (exp 1/2)
  cbrt        Cube root function (exp 1/3)
  lb          Binary logarithm function (base 2)
  ln          Natural logarithm function (base e)
  lg          Common logarithm function (base 10)
  \endverbatim
  \subsection command_trig Trigonometric functions
  \verbatim
  sin         Trigonometric sine function
  cos         Trigonometric cosine function
  tan         Trigonometric tangent function
  cot         Trigonometric cotangent function
  sec         Trigonometric secant function
  csc         Trigonometric cosecant function
  crd         Trigonometric chord function
  exsec       Trigonometric exsecant function
  excsc       Trigonometric excosecant function
  arcsin      Inverse trigonometric sine function
  arccos      Inverse trigonometric cosine function
  arctan      Inverse trigonometric tangent function
  arccot      Inverse trigonometric cotangent function
  arcsec      Inverse trigonometric secant function
  arccsc      Inverse trigonometric cosecant function
  arccrd      Inverse trigonometric chord function
  arcexsec    Inverse trigonometric exsecant function
  arcexcsc    Inverse trigonometric excosecant function
  \endverbatim
  \subsection command_hype Hyperbolic functions
  \verbatim
  sinh        Hyperbolic sine function
  cosh        Hyperbolic cosine function
  tanh        Hyperbolic tangent function
  coth        Hyperbolic cotangent function
  sech        Hyperbolic secant function
  csch        Hyperbolic cosecant function
  arcsinh     Inverse hyperbolic sine function
  arccosh     Inverse hyperbolic cosine function
  arctanh     Inverse hyperbolic tangent function
  arccoth     Inverse hyperbolic cotangent function
  arcsech     Inverse hyperbolic secant function
  arccsch     Inverse hyperbolic cosecant function
  \endverbatim
  \subsection command_earl Early trigonometric functions
  \verbatim
  ver         Versed sine function
  vcs         Versed cosine function
  cvs         Coversed sine function
  cvc         Coversed cosine function
  hv          Haversed sine function
  hvc         Haversed cosine function
  hcv         Hacoversed sine function
  hcc         Hacoversed cosine function
  arcver      Inverse versed sine function
  arcvcs      Inverse versed cosine function
  arccvs      Inverse coversed sine function
  arccvc      Inverse coversed cosine function
  archv       Inverse haversed sine function
  archvc      Inverse haversed cosine function
  archcv      Inverse hacoversed sine function
  archcc      Inverse hacoversed cosine function
  \endverbatim
  \subsection command_vars Variables and constant
  \verbatim
  pi          Trigonometric constant
  e           Euler's number
  i           Imaginary unit
  ins         Result of last calculation
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
  Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
  Copyright (c) 2007 The NetBSD Foundation, Inc.
  Copyright (c) 1990, 1993 The Regents of the University of California.
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

  \subsection license_tem Template
  A template for The BSD 2-Clause License are available from the
  Open Source Initiative and Wikipidia<BR>
  http://opensource.org/licenses/BSD-2-Clause<BR>
  https://wikipedia.org/wiki/BSD_licenses<BR>

  \page    release_page Release history
  \section release_sec  Release history

  \subsection version184 1.8.4 August 05 2017
  - Ignore casing in hexadecimal numbers.

  \subsection version183 1.8.3 July 21 2017
  - Updated help texts and man page.
  - Fixed bug in ANSI switch.

  \subsection version182 1.8.2 July 14 2017
  - MIPS support.
  - Improved endianness detection.
  - Fixed configuration errors.

  \subsection version181 1.8.1 April 22 2017
  - OpenBSD support.
  - Fixed Haiku bug.

  \subsection version180 1.8.0 April 13 2017
  - Fixed bugs in numeral systems.
  - Fixed bugs related to infinity (Inf).
  - Fixed bugs related to Not a Number (NaN).
  - Updated and cleanup documentation.
  - Cleaned up code structure.
  - OpenLibm support.

  \subsection version171 1.7.1 March 26 2017
  - Haiku support.
  - Unified ANSI console.
  - Code cleanup.

  \subsection version170 1.7.0 March 12 2017
  - Introduced scientific notation.
  - Introduced Not a Number (NaN).
  - Fixed bugs related to infinity (Inf).
  - Fixed bugs in log of complex numbers.
  - Fixed bugs in numeral systems.
  - Miscellaneous minor bug fixes.
  - Early trigonometric functions.
  - Static and dynamic libraries.

  \subsection version164 1.6.4 February 04 2017
  - Fixed Windows memory bugs.
  - Fixed 64 bit memory bugs.

  \subsection version163 1.6.3 January 30 2017
  - Improved error handling.
  - Fixed error in fraction point parsing.
  - Fixed typo in help text.
  - 64 bit PowerPC support.
  - Fixed AROS build errors.
  - Fixed ARMv6 build errors.
  - Fixed 64 bit ARM build errors.
  - Debian support.
  - NetBSD support.

  \subsection version162 1.6.2 January 24 2017
  - Fixed bug in memory allocation.
  - Fixed bug in native keyboard input.
  - Included build options in executables.
  - ARM support.

  \subsection version161 1.6.1 January 21 2017
  - Fixed language bug in Windows.
  - Fixed potential memory bugs.
  - Clang compiler support.
  - Update copyright texts.
  - New doxygen documentation.

  \subsection version160 1.6.0 April 7 2016
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

  \subsection version150 1.5.0 September 21 2014
  - Calculation with complex numbers.
  - Fixed command line version.
  - Miscellaneous bug fixed.
  - Fixed spelling mistakes in help files.
  - Documentation including class diagrams in HTML format.
  - Scripts for porting and building the source.

  \subsection version140 1.4.0 August 24 2014
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

  \subsection version130 1.3.0 August 06 2014
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

extern class Program* Program;
