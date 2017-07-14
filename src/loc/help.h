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
 * Generated with FlexCat. For more information, see:
 * http://sourceforge.net/projects/flexcat/
 *
 * Project homepage:
 * https://amath.innolan.net
 * 
 */

#ifndef AMATH_LOCALE_HELP_H
#define AMATH_LOCALE_HELP_H

/**
 * @file  loc/help.h
 * @brief Help texts for statement
 */

#include "amath.h"
#include "amathc.h"
#include "amatht.h"
#include "main/symbol.h"

#define symzero Symbol(0)

struct helptextdef
{
    int id;
    Symbol symbol;
    const char* text;
};

static const helptextdef helptexts[] = {
    { 0, symzero, "Enter command or expression to evaluate.#NEWLINE##SYNTAXHIGHLIGHT#Example: 2+3-cos(3)#NORMALTEXT##NEWLINE# #NEWLINE#More help is available for designated topics.#NEWLINE#----------------------------------------------------#NEWLINE#functions    Base functions#NEWLINE#trigon       Trigonometric functions#NEWLINE#hyper        Hyperbolic functions#NEWLINE#early        Early trigonometric functions#NEWLINE#complex      Syntax for complex numbers#NEWLINE#statements   Available statements#NEWLINE#operators    Supported operators#NEWLINE#----------------------------------------------------#NEWLINE##SYNTAXHIGHLIGHT#Example: help trigon#NEWLINE#" },
    { 1, symoperator, "----------------------------------------------------#NEWLINE#    +    Mathematical addition#NEWLINE#    -    Mathematical subtraction#NEWLINE#    *    Mathematical multiplication#NEWLINE#    /    Mathematical division#NEWLINE#    ^    Mathematical exponentiation#NEWLINE#    =    Assignment of variable values#NEWLINE#    |    Absolute value of number#NEWLINE#----------------------------------------------------#NEWLINE#" },
    { 2, symfunction, "----------------------------------------------------#NEWLINE#abs     Absolute value of number#NEWLINE#sgn     Mathematical signum function#NEWLINE#round   Round to nearest integer number#NEWLINE#trunc   Discard fraction part of number#NEWLINE#floor   Mathematical floor function#NEWLINE#ceil    Mathematical ceiling function#NEWLINE#sqrt    Square root function (exp 1/2)#NEWLINE#cbrt    Cube root function (exp 1/3)#NEWLINE#lb      Binary logarithm function (base 2)#NEWLINE#ln      Natural logarithm function (base e)#NEWLINE#lg      Common logarithm function (base 10)#NEWLINE#----------------------------------------------------#NEWLINE##SYNTAXHIGHLIGHT#Example: round(1.55)#NORMALTEXT##NEWLINE#" },
    { 3, symtrigon, "----------------------------------------------------#NEWLINE#sin     Trigonometric sine function#NEWLINE#cos     Trigonometric cosine function#NEWLINE#tan     Trigonometric tangent function#NEWLINE#cot     Trigonometric cotangent function#NEWLINE#sec     Trigonometric secant function#NEWLINE#csc     Trigonometric cosecant function#NEWLINE#crd     Trigonometric chord function#NEWLINE#exsec   Trigonometric exsecant function#NEWLINE#excsc   Trigonometric excosecant function#NEWLINE#asin    Inverse trigonometric sine function#NEWLINE#acos    Inverse trigonometric cosine function#NEWLINE#atan    Inverse trigonometric tangent function#NEWLINE#acot    Inverse trigonometric cotangent function#NEWLINE#asec    Inverse trigonometric secant function#NEWLINE#acsc    Inverse trigonometric cosecant function#NEWLINE#acrd    Inverse trigonometric chord function#NEWLINE#aexsec  Inverse trigonometric exsecant function#NEWLINE#aexcsc  Inverse trigonometric excosecant function#NEWLINE#----------------------------------------------------#NEWLINE#Inverse functions can be prefixed with ar or arc#NEWLINE#instead of a.#NEWLINE#" },
    { 4, symhyper, "----------------------------------------------------#NEWLINE#sinh    Hyperbolic sine function#NEWLINE#cosh    Hyperbolic cosine function#NEWLINE#tanh    Hyperbolic tangent function#NEWLINE#coth    Hyperbolic cotangent function#NEWLINE#sech    Hyperbolic secant function#NEWLINE#csch    Hyperbolic cosecant function     #NEWLINE#asinh   Inverse hyperbolic sine function#NEWLINE#acosh   Inverse hyperbolic cosine function#NEWLINE#atanh   Inverse hyperbolic tangent function#NEWLINE#acoth   Inverse hyperbolic cotangent function#NEWLINE#asech   Inverse hyperbolic secant function#NEWLINE#acsch   Inverse hyperbolic cosecant function#NEWLINE#----------------------------------------------------#NEWLINE#Inverse functions can be prefixed with ar or arc #NEWLINE#instead of a.#NEWLINE#" },
    { 5, symearly, "----------------------------------------------------#NEWLINE#ver     Versed sine function#NEWLINE#vcs     Versed cosine function#NEWLINE#cvs     Coversed sine function#NEWLINE#cvc     Coversed cosine function#NEWLINE#hv      Haversed sine function#NEWLINE#hvc     Haversed cosine function#NEWLINE#hcv     Hacoversed sine function#NEWLINE#hcc     Hacoversed cosine function#NEWLINE#aver    Inverse versed sine function#NEWLINE#avcs    Inverse versed cosine function#NEWLINE#acvs    Inverse coversed sine function#NEWLINE#acvc    Inverse coversed cosine function#NEWLINE#ahv     Inverse haversed sine function#NEWLINE#ahvc    Inverse haversed cosine function#NEWLINE#ahcv    Inverse hacoversed sine function#NEWLINE#ahcc    Inverse hacoversed cosine function#NEWLINE#----------------------------------------------------#NEWLINE#Inverse functions can be prefixed with ar or arc #NEWLINE#instead of a.#NEWLINE#" },
    { 6, symcomplex, "Expressions with complex numbers are written using an i to denote#NEWLINE#the imaginary value. Complex numbers can seamlessly be mixed with#NEWLINE#real numbers.#NEWLINE##SYNTAXHIGHLIGHT#Syntax:  2+3i#NEWLINE#Example: 2+3.2i*cos(-1i)+5/7#NEWLINE#" },
    { 7, symclear, "The clear statement erases all text in the console window.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: clear#NEWLINE#" },
    { 8, symdef, "The def statement is used to define functions. When defining a function#NEWLINE#it is possible to omit the def keyword. Defined functions can be shown#NEWLINE#using the functions statement.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: def f(x)=2*x+3#NEWLINE#Optional syntax: f(x)=2*x+3#NEWLINE#" },
    { 9, symdelete, "The delete statement can delete variable and functions. To delete a#NEWLINE#single variable or functions use the name of the function or variable.#NEWLINE#To delete all functions or variables specify either the variable or#NEWLINE#function keyword.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: delete f(x)#NEWLINE#Syntax: delete variables#NEWLINE#" },
    { 10, symdigits, "The digits statement defines the displayed number of significant digits.#NEWLINE#To show current configuration use the digits statement without specifying#NEWLINE#the number.#NEWLINE# #SYNTAXHIGHLIGHT#Syntax: digits 7#NEWLINE#" },
    { 11, symeval, "The eval statement evaluates an expression. When evaluating an expression#NEWLINE#it is possible to omit the eval keyword.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: eval 2.4*x+3.2#NEWLINE#Optional syntax: 2.4*x+3.2#NEWLINE#" },
    { 12, symexecute, "The execute statement reads the content of a file and execute all statements.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: execute \"savedfile\"#NEWLINE#" },
    { 13, syminput, "The input statement either changes or shows the how numeral input is interpreted.#NEWLINE#Possible input systems are: binary, octal, decimal and hexadecimal. Default is#NEWLINE#decimal. To use positional systems with other bases specify the base number.#NEWLINE#Numeral output system can be modified using the output statement.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: input hexadecimal#NEWLINE#Syntax: input 4#NEWLINE#" },
    { 14, symhelp, "The help statement can be used to display help about topics and statements.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: help variables#NEWLINE#" },
    { 15, symoutput, "The output statement either changes or shows the how numeral output is shown.#NEWLINE#Possible output systems are: binary, octal, decimal and hexadecimal. Default#NEWLINE#is decimal. To use positional systems with other bases specify the base number.#NEWLINE#Numeral input system can be modified using the input statement.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: output octal#NEWLINE#" },
    { 16, symlist, "No description is available for the list statement.#NEWLINE#" },
    { 17, symshow, "The show statement displays the content of a file.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: show \"filetosee\"#NEWLINE#" },
    { 18, symload, "The load statement retrieves a set of defined variables and functions from#NEWLINE#a file. Variables and functions can be saved using the save statement.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: load \"savedwork\"#NEWLINE#" },
    { 19, symsave, "The save statement saves defined variables and functions to a file in a#NEWLINE#plain text format. Saved variables and functions can be retrieved using#NEWLINE#the load statement.#NEWLINE# #SYNTAXHIGHLIGHT#Syntax: save \"worktokeep\"#NEWLINE#" },
    { 20, symversion, "Show which version of amath is running.#NEWLINE#" },
    { 21, symabout, "Show various information about the running version of amath.#NEWLINE#" },
    { 22, symlicense, "Show license details.#NEWLINE#" },
    { 23, symmem, "Show internal memory usage together with maximum usage.#NEWLINE#" },
    { 24, symprefs, "There is no help for prefs statement now.#NEWLINE#" },
    { 25, symvariable, "The variable statement shows a list of variables in memory.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: variables#NEWLINE##NORMALTEXT#optional syntax: vars#NEWLINE#" },
    { 26, symexit, "The exit statement shuts down amath.#NEWLINE##SYNTAXHIGHLIGHT#Syntax: exit#NEWLINE#" },
    { 27, syme, "Euler's number is base of the exponential function which equals its own#NEWLINE#derivative. It is approximately equal to 2.71828.#NEWLINE##SYNTAXHIGHLIGHT#Example: ln(e)#NEWLINE#" },
    { 28, sympi, "Pi is the ratio of the circumference of a circle to its diameter. Being an#NEWLINE#irrational number, pi cannot be expressed exactly as a common fraction.#NEWLINE#The value of pi is commonly approximated as #SYNTAXHIGHLIGHT#3.14159#NORMALTEXT#.#NEWLINE#" },
    { 29, symi, "The imaginary unit is denoted and commonly referred to as i.#NEWLINE#The imaginary unit is a number, which when multiplied#NEWLINE#by itself gives -1.#NEWLINE#" },
    { 30, symins, "No help is available for the ins variable#NEWLINE#" },
    { 31, symbin, "No help is available for the binary keyword#NEWLINE" },
    { 32, symoct, "No help is available for the octal keyword#NEWLINE" },
    { 33, symdec, "No help is available for the decimal keyword#NEWLINE" },
    { 34, symhex, "No help is available for the hexadecimal keyword#NEWLINE" },
    { -1, symzero, EMPTYSTRING }
};

#endif
