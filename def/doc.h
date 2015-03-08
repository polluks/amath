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
  First install ixemul.library if needed. Then copy the amath binary file and
  icon to C: or any other appropriate location.

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

  \subsection remarks Remarks
  Download and install the ADE package from Aminet to compile a customized
  version of amath. Instructions are provided within the source archive.

  \subsection license License
  amath is Freeware and the sources are open. The source is always included in
  distributions from aminet. Latest well documented version is distributed
  independently:<BR>
  http://aminet.net/package/misc/math/amath.src

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
  Copyright (c) 2015 Carsten Larsen
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
  </PRE></BLOCKQUOTE>
  \subsection license_tem Template
  A template for The BSD 2-Clause License are available from the
  Open Source Initiative and Wikipidia<BR>
  http://opensource.org/licenses/BSD-2-Clause<BR>
  http://en.wikipedia.org/wiki/BSD_licenses<BR>


  \page    release_page Release history
  \section release_sec  Release history

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


  \page    make000_page Amiga 500+ build
  \section make000_sec  Amiga 500+ build with GCC

  Example of included bash script for building an Amiga 500+ version with GCC.

  <BLOCKQUOTE><PRE>
  #!/bin/bash
  # ------------------------------------------------------------------------------------ #
  # Amiga 500+ build with GCC 2.95.3                                                     #
  # Download GCC toolchain from github:                                                  #
  # https://github.com/cahirwpz/m68k-amigaos-toolchain                                   #
  #                                                                                      #
  # Flags:                                                                               #
  # Os                Optimize space usage (code and data) of resulting program.         #
  # m68000            Generate code for the 68000 CPU.                                   #
  # fstrength-reduce  Might make some loops run faster.                                  #
  # ffreestanding     Do not depend on any standard library.                             #
  # noixemul          Use static linking with LibNIX library.                            #
  # fno-rtti          Disable generation of runtime type information.                    #
  # ffloat-store      Do not store floating point variables in registers.                #
  # s                 Remove all symbol table and relocation information.                #
  # DAOS              Compile for an amiga compliant operating system.                   #
  # DAOSSMALL         Generate code for an amiga with low maximum screen resolution.     #
  # DAMIGAALLOC       Use Amiga AllocVec and FreeVec to handle memory (de)allocation.    #
  # o                 Output executable 'amath'                                          #
  # Wall              Enables all compiler's warning messages.                           #
  # --------------------------------------------------------------------------------------
  m68k-amigaos-gcc -Os -m68000                                                           \
    -fstrength-reduce -ffreestanding -noixemul -fno-rtti -ffloat-store -s                \
    prog/main.cpp        prog/program.cpp     prog/cli.cpp         main/values.cpp       \
    main/functions.cpp   main/graphlist.cpp   main/statements.cpp  main/lexer.cpp        \
    main/nodes.cpp       main/operators.cpp   main/parser.cpp      main/token.cpp        \
    lib/aengine.cpp      lib/charbuf.cpp      lib/real.cpp         lib/cplex.cpp         \
    lib/ntext.cpp        lib/fgrid.cpp        lib/graph.cpp        libc/calloc.cpp       \
    libc/memcpy.cpp      libc/memset.cpp      libc/strcmp.cpp      libc/strlen.cpp       \
    libm/cplex/exp.cpp   libm/cplex/pow.cpp   libm/cplex/logb.cpp  libm/cplex/log.cpp    \
    libm/cplex/log10.cpp libm/cplex/cos.cpp   libm/cplex/sin.cpp   libm/cplex/tan.cpp    \
    libm/cplex/sec.cpp   libm/cplex/csc.cpp   libm/cplex/cot.cpp   libm/cplex/acos.cpp   \
    libm/cplex/asin.cpp  libm/cplex/atan.cpp  libm/cplex/asec.cpp  libm/cplex/acsc.cpp   \
    libm/cplex/acot.cpp  libm/cplex/cosh.cpp  libm/cplex/sinh.cpp  libm/cplex/tanh.cpp   \
    libm/cplex/sech.cpp  libm/cplex/csch.cpp  libm/cplex/coth.cpp  libm/cplex/acosh.cpp  \
    libm/cplex/asinh.cpp libm/cplex/atanh.cpp libm/cplex/asech.cpp libm/cplex/acsch.cpp  \
    libm/cplex/acoth.cpp libm/cplex/csgn.cpp  libm/cplex/sqrt.cpp  libm/cplex/cbrt.cpp   \
    libm/real/pow.cpp    libm/real/exp.cpp    libm/real/log.cpp    libm/real/log10.cpp   \
    libm/real/cos.cpp    libm/real/sin.cpp    libm/real/tan.cpp    libm/real/acos.cpp    \
    libm/real/asin.cpp   libm/real/atan.cpp   libm/real/cosh.cpp   libm/real/sinh.cpp    \
    libm/real/tanh.cpp   libm/real/acosh.cpp  libm/real/asinh.cpp  libm/real/atanh.cpp   \
    libm/real/floor.cpp  libm/real/ceil.cpp   libm/real/sqrt.cpp   libm/real/cbrt.cpp    \
    libm/real/atan2.cpp  libm/real/hypot.cpp  libm/real/kcos.cpp   libm/real/ksin.cpp    \
    libm/real/ktan.cpp   libm/real/remp2.cpp  libm/real/kremp2.cpp libm/real/scalbn.cpp  \
    libm/real/log1p.cpp  libm/real/expm1.cpp  libm/real/fmod.cpp   io/console.cpp        \
    lib/dconv/math.cpp   lib/dconv/print.cpp  lib/dconv/dragon4.cpp                      \
    arc/aos/gui/agraph.cpp       arc/aos/gui/awindow.cpp     arc/aos/sys/aconsole.cpp    \
    arc/aos/sys/afilesystem.cpp  arc/aos/sys/aproc.cpp       arc/aos/sys/atask.cpp       \
    -I. -Iarc -Ilib -Ilibm -Imain -Iprog                                                 \
    -DAOS -DAOSSMALL -DAMIGAALLOC                                                        \
    -o amath -lgcc -Wall                                                                 \
  # --------------------------------------------------------------------------------------
  </PRE></BLOCKQUOTE>

  \page    make030_page Amiga 1200 build
  \section make030_sec  Amiga 1200 build with GCC

  Example of included bash script for building an expanded Amiga 1200 version with GCC.

  <BLOCKQUOTE><PRE>
  #!/bin/bash
  # --------------------------------------------------------------------------------------
  # Expanded Amiga 1200 build with GCC 2.95.3                                            #
  # Download GCC toolchain from github:                                                  #
  # https://github.com/cahirwpz/m68k-amigaos-toolchain                                   #
  #                                                                                      #
  # Flags:                                                                               #
  # O1                Moderate optimization; optimizes reasonably well.                  #
  # m68030            Generate code for the 68030 CPU.                                   #
  # m68881            Generate code for the 68881 FPU.                                   #
  # fstrength-reduce  Might make some loops run faster.                                  #
  # ffreestanding     Do not depend on any standard library.                             #
  # noixemul          Use static linking with LibNIX library.                            #
  # fno-rtti          Disable generation of runtime type information.                    #
  # ffloat-store      Do not store floating point variables in registers.                #
  # s                 Remove all symbol table and relocation information.                #
  # DAOS              Compile for an amiga compliant operating system.                   #
  # DAMIGAALLOC       Use Amiga AllocVec and FreeVec to handle memory (de)allocation.    #
  # o                 Output executable amath.030f                                       #
  # Wall              Enables all compiler's warning messages.                           #
  # ------------------------------------------------------------------------------------ #
  m68k-amigaos-gcc -O1 -m68030 -m68881                                                   \
    -fstrength-reduce -ffreestanding -noixemul -fno-rtti -ffloat-store -s                \
    prog/main.cpp        prog/program.cpp     prog/cli.cpp         main/values.cpp       \
    main/functions.cpp   main/graphlist.cpp   main/statements.cpp  main/lexer.cpp        \
    main/nodes.cpp       main/operators.cpp   main/parser.cpp      main/token.cpp        \
    lib/aengine.cpp      lib/charbuf.cpp      lib/real.cpp         lib/cplex.cpp         \
    lib/ntext.cpp        lib/fgrid.cpp        lib/graph.cpp        libc/calloc.cpp       \
    libc/memcpy.cpp      libc/memset.cpp      libc/strcmp.cpp      libc/strlen.cpp       \
    libm/cplex/exp.cpp   libm/cplex/pow.cpp   libm/cplex/logb.cpp  libm/cplex/log.cpp    \
    libm/cplex/log10.cpp libm/cplex/cos.cpp   libm/cplex/sin.cpp   libm/cplex/tan.cpp    \
    libm/cplex/sec.cpp   libm/cplex/csc.cpp   libm/cplex/cot.cpp   libm/cplex/acos.cpp   \
    libm/cplex/asin.cpp  libm/cplex/atan.cpp  libm/cplex/asec.cpp  libm/cplex/acsc.cpp   \
    libm/cplex/acot.cpp  libm/cplex/cosh.cpp  libm/cplex/sinh.cpp  libm/cplex/tanh.cpp   \
    libm/cplex/sech.cpp  libm/cplex/csch.cpp  libm/cplex/coth.cpp  libm/cplex/acosh.cpp  \
    libm/cplex/asinh.cpp libm/cplex/atanh.cpp libm/cplex/asech.cpp libm/cplex/acsch.cpp  \
    libm/cplex/acoth.cpp libm/cplex/csgn.cpp  libm/cplex/sqrt.cpp  libm/cplex/cbrt.cpp   \
    libm/real/pow.cpp    libm/real/exp.cpp    libm/real/log.cpp    libm/real/log10.cpp   \
    libm/real/cos.cpp    libm/real/sin.cpp    libm/real/tan.cpp    libm/real/acos.cpp    \
    libm/real/asin.cpp   libm/real/atan.cpp   libm/real/cosh.cpp   libm/real/sinh.cpp    \
    libm/real/tanh.cpp   libm/real/acosh.cpp  libm/real/asinh.cpp  libm/real/atanh.cpp   \
    libm/real/floor.cpp  libm/real/ceil.cpp   libm/real/sqrt.cpp   libm/real/cbrt.cpp    \
    libm/real/atan2.cpp  libm/real/hypot.cpp  libm/real/kcos.cpp   libm/real/ksin.cpp    \
    libm/real/ktan.cpp   libm/real/remp2.cpp  libm/real/kremp2.cpp libm/real/scalbn.cpp  \
    libm/real/log1p.cpp  libm/real/expm1.cpp  libm/real/fmod.cpp   io/console.cpp        \
    lib/dconv/math.cpp   lib/dconv/print.cpp  lib/dconv/dragon4.cpp                      \
    arc/aos/gui/agraph.cpp       arc/aos/gui/awindow.cpp     arc/aos/sys/aconsole.cpp    \
    arc/aos/sys/afilesystem.cpp  arc/aos/sys/aproc.cpp       arc/aos/sys/atask.cpp       \
    -I. -Iarc -Ilib -Ilibm -Imain -Iprog                                                 \
    -DAOS -DAMIGAALLOC                                                                   \
    -o amath.030f -lgcc -Wall                                                            \
  # --------------------------------------------------------------------------------------
  </PRE></BLOCKQUOTE>

  \page    makearos_page AROS i386 build
  \section makearos_sec  AROS i386 build with GCC

  Example of included bash script for building an i386 AROS version with GCC.

  <BLOCKQUOTE><PRE>
  #!/bin/bash
  # --------------------------------------------------------------------------------------
  # AROS i386 build with GCC 4.6.4                                                       #
  #                                                                                      #
  # Flags:                                                                               #
  # O2                Full optimization; generates highly optimized code.                #
  # fstrength-reduce  Might make some loops run faster.                                  #
  # ffreestanding     Do not depend on any standard library.                             #
  # fno-rtti          Disable generation of runtime type information.                    #
  # s                 Remove all symbol table and relocation information.                #
  # DAOS              Compile for an amiga compliant operating system.                   #
  # DAMIGAALLOC       Use Amiga AllocVec and FreeVec to handle memory (de)allocation.    #
  # o                 Output executable amath.i386                                       #
  # Wall              Enables all compiler's warning messages.                           #
  # --------------------------------------------------------------------------------------
  i386-aros-gcc -O2 -fstrength-reduce -ffreestanding -fno-rtti                           \
    prog/main.cpp        prog/program.cpp     prog/cli.cpp         main/values.cpp       \
    main/functions.cpp   main/graphlist.cpp   main/statements.cpp  main/lexer.cpp        \
    main/nodes.cpp       main/operators.cpp   main/parser.cpp      main/token.cpp        \
    lib/aengine.cpp      lib/charbuf.cpp      lib/real.cpp         lib/cplex.cpp         \
    lib/ntext.cpp        lib/fgrid.cpp        lib/graph.cpp        libc/calloc.cpp       \
    libc/memcpy.cpp      libc/memset.cpp      libc/strcmp.cpp      libc/strlen.cpp       \
    libm/cplex/exp.cpp   libm/cplex/pow.cpp   libm/cplex/logb.cpp  libm/cplex/log.cpp    \
    libm/cplex/log10.cpp libm/cplex/cos.cpp   libm/cplex/sin.cpp   libm/cplex/tan.cpp    \
    libm/cplex/sec.cpp   libm/cplex/csc.cpp   libm/cplex/cot.cpp   libm/cplex/acos.cpp   \
    libm/cplex/asin.cpp  libm/cplex/atan.cpp  libm/cplex/asec.cpp  libm/cplex/acsc.cpp   \
    libm/cplex/acot.cpp  libm/cplex/cosh.cpp  libm/cplex/sinh.cpp  libm/cplex/tanh.cpp   \
    libm/cplex/sech.cpp  libm/cplex/csch.cpp  libm/cplex/coth.cpp  libm/cplex/acosh.cpp  \
    libm/cplex/asinh.cpp libm/cplex/atanh.cpp libm/cplex/asech.cpp libm/cplex/acsch.cpp  \
    libm/cplex/acoth.cpp libm/cplex/csgn.cpp  libm/cplex/sqrt.cpp  libm/cplex/cbrt.cpp   \
    libm/real/pow.cpp    libm/real/exp.cpp    libm/real/log.cpp    libm/real/log10.cpp   \
    libm/real/cos.cpp    libm/real/sin.cpp    libm/real/tan.cpp    libm/real/acos.cpp    \
    libm/real/asin.cpp   libm/real/atan.cpp   libm/real/cosh.cpp   libm/real/sinh.cpp    \
    libm/real/tanh.cpp   libm/real/acosh.cpp  libm/real/asinh.cpp  libm/real/atanh.cpp   \
    libm/real/floor.cpp  libm/real/ceil.cpp   libm/real/sqrt.cpp   libm/real/cbrt.cpp    \
    libm/real/atan2.cpp  libm/real/hypot.cpp  libm/real/kcos.cpp   libm/real/ksin.cpp    \
    libm/real/ktan.cpp   libm/real/remp2.cpp  libm/real/kremp2.cpp libm/real/scalbn.cpp  \
    libm/real/log1p.cpp  libm/real/expm1.cpp  libm/real/fmod.cpp   io/console.cpp        \
    lib/dconv/math.cpp   lib/dconv/print.cpp  lib/dconv/dragon4.cpp                      \
    arc/aos/gui/agraph.cpp       arc/aos/gui/awindow.cpp     arc/aos/sys/aconsole.cpp    \
    arc/aos/sys/afilesystem.cpp  arc/aos/sys/aproc.cpp       arc/aos/sys/atask.cpp       \
    -I. -Iarc -Ilib -Ilibm -Imain -Iprog                                                 \
    -DAOS -DINTEL -DAMIGAALLOC                                                           \
    -o amath.i386 -lstdc++ -Wall                                                         \
  # --------------------------------------------------------------------------------------
  i386-aros-strip --strip-unneeded -R .comment amath.i386
  # --------------------------------------------------------------------------------------
  </PRE></BLOCKQUOTE>

*/
