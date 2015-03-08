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

#ifndef _DEF_HELP_H
#define _DEF_HELP_H

/**
 * @file  help.h
 * @brief Help texts definitions.
 *
 */

#include "def/lex.h"
#include "def/libc.h"
#include "def/text.h"

struct helptextdef {
    Symbol symbol;
    const char *text;
};

static const helptextdef helptexts[] = {
    {   Symbol(0),
        "Type expression to evaluate or enter command."     NEWLINE
        SYNTAXHIGHLIGHT
        "Example: 2+3-cos(3)" NORMALTEXT NEWLINE NEWLINE
        "More help is available for designated topics."     NEWLINE
        "-------------------------------------------------" NEWLINE
        "functions    Base functions.                     " NEWLINE
        "trigon       Trigonometric functions.            " NEWLINE
        "hyper        Hyperbolic functions.               " NEWLINE
        "complex      Syntax for complex numbers.         " NEWLINE
        "statements   Available statements.               " NEWLINE
        "operators    Supported operators.                " NEWLINE
        "-------------------------------------------------" NEWLINE
        SYNTAXHIGHLIGHT "Example: help trigon" NORMALTEXT   NEWLINE
    },
    {   symoperator,
        "-------------------------------------------------" NEWLINE
        "    +   Mathematical addition.                   " NEWLINE
        "    -   Mathematical subtraction.                " NEWLINE
        "    *   Mathematical multiplication.             " NEWLINE
        "    /   Mathematical division.                   " NEWLINE
        "    ^   Mathematical exponentiation.             " NEWLINE
        "    =   Assignment of variable values.           " NEWLINE
        "    |   Absolute value of number.                " NEWLINE
        "-------------------------------------------------" NEWLINE
    },
    {   symfunction,
        "-------------------------------------------------" NEWLINE
        "abs     Absolute value of number.                " NEWLINE
        "sgn     Mathematical signum function.            " NEWLINE
        "round   Round to nearest integer number.         " NEWLINE
        "trunc   Discard fraction part of number.         " NEWLINE
        "floor   Mathematical floor function.             " NEWLINE
        "ceil    Mathematical ceiling function.           " NEWLINE
        "sqrt    Square root function (exp 1/2).          " NEWLINE
        "cbrt    Cube root function (exp 1/3).            " NEWLINE
        "lb      Binary logarithm function (base 2).      " NEWLINE
        "ln      Natural logarithm function (base e).     " NEWLINE
        "lg      Common logarithm function (base 10).     " NEWLINE
        "-------------------------------------------------" NEWLINE
        SYNTAXHIGHLIGHT "Example: round(1.55)" NORMALTEXT   NEWLINE
    },
    {   symtrigon,
        "-------------------------------------------------" NEWLINE
        "sin     Trigonometric sine function.             " NEWLINE
        "cos     Trigonometric cosine function.           " NEWLINE
        "tan     Trigonometric tangent function.          " NEWLINE
        "cot     Trigonometric cotangent function.        " NEWLINE
        "sec     Trigonometric secant function.           " NEWLINE
        "csc     Trigonometric cosecant function.         " NEWLINE
        "asin    Inverse trigonometric sine function.     " NEWLINE
        "acos    Inverse trigonometric cosine function.   " NEWLINE
        "atan    Inverse trigonometric tangent function.  " NEWLINE
        "acot    Inverse trigonometric cotangent function." NEWLINE
        "asec    Inverse trigonometric secant function.   " NEWLINE
        "acsc    Inverse trigonometric cosecant function. " NEWLINE
        "-------------------------------------------------" NEWLINE
        "Inverse functions can be prefixed with ar or arc " NEWLINE
        "instead of a."                                     NEWLINE
    },
    {   symhyper,
        "-------------------------------------------------" NEWLINE
        "sinh    Hyperbolic sine function.                " NEWLINE
        "cosh    Hyperbolic cosine function.              " NEWLINE
        "tanh    Hyperbolic tangent function.             " NEWLINE
        "coth    Hyperbolic cotangent function.           " NEWLINE
        "sech    Hyperbolic secant function.              " NEWLINE
        "csch    Hyperbolic cosecant function.            " NEWLINE
        "asinh   Inverse hyperbolic sine function.        " NEWLINE
        "acosh   Inverse hyperbolic cosine function.      " NEWLINE
        "atanh   Inverse hyperbolic tangent function.     " NEWLINE
        "acoth   Inverse hyperbolic cotangent function.   " NEWLINE
        "asech   Inverse hyperbolic secant function.      " NEWLINE
        "acsch   Inverse hyperbolic cosecant function.    " NEWLINE
        "-------------------------------------------------" NEWLINE
        "Inverse functions can be prefixed with ar or arc " NEWLINE
        "instead of a."                                     NEWLINE
    },
    {   symstatement,
        "---------------------------------------------------" NEWLINE
        "clear      Clear console window.                   " NEWLINE
        "def        Define function.                        " NEWLINE
        "delete     Delete variable or function.            " NEWLINE
        "digits     Set number of significant digits.       " NEWLINE
        "eval       Evaluate arithmetic expression.         " NEWLINE
        "execute    Execute statements in a file.           " NEWLINE
        "functions  Show list of user defined functions.    " NEWLINE
//        "input      Change numeral input system.            " NEWLINE
        "help       Show basic help text.                   " NEWLINE
//        "output     Change numeral output system.           " NEWLINE
        "list       Show content of a directory.            " NEWLINE
        "show       Show content of a file.                 " NEWLINE
        "load       Load variable and functions from file.  " NEWLINE
        "save       Save variable and functions to file.    " NEWLINE
        "variables  Show list of variables.                 " NEWLINE
        "version    Show version string.                    " NEWLINE
        "exit       Exit program.                           " NEWLINE
        "---------------------------------------------------" NEWLINE
        "The def and eval statements are optional. Functions" NEWLINE
        "and variables statements can be shorten to funcs   " NEWLINE
        "and vars."                                           NEWLINE
    },
    {   symcomplex,
        "Expressions with complex numbers are written using an i to denote" NEWLINE
        "the imaginary value. Complex numbers can seamlessly be mixed with" NEWLINE
        "real numbers." NEWLINE SYNTAXHIGHLIGHT
        "Syntax:  2+3i" NEWLINE
        "Example: 2+3.2i*cos(-1i)+5/7" NEWLINE
    },
    {   symclear,
        "The clear statement erases all text in the console window." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: clear" NEWLINE
    },
    {   symdef,
        "The def statement is used to define functions. When defining a function" NEWLINE
        "it is possible to omit the def keyword. Defined functions can be shown"  NEWLINE
        "using the functions statement." NEWLINE SYNTAXHIGHLIGHT
        "Syntax: def f(x)=2*x+3" NEWLINE
        "Optional syntax: f(x)=2*x+3" NEWLINE
    },
    {   symdelete,
        "The delete statement can delete variable and functions. To delete a"    NEWLINE
        "single variable or functions use the name of the function or variable." NEWLINE
        "To delete all functions or variables specify either the variable or"    NEWLINE
        "function keyword." NEWLINE SYNTAXHIGHLIGHT
        "Syntax: delete f(x)" NEWLINE
        "Syntax: delete variables" NEWLINE
    },
    {   symdigits,
        "The digits statement defines the displayed number of significant digits."  NEWLINE
        "To show current configuration use the digits statement without specifying" NEWLINE
        "the number." NEWLINE SYNTAXHIGHLIGHT
        "Syntax: digits 7" NEWLINE
    },
    {   symeval,
        "The eval statement evaluates an expression. When evaluating an expression" NEWLINE
        "it is possible to omit the eval keyword." NEWLINE SYNTAXHIGHLIGHT
        "Syntax: eval 2.4*x+3.2" NEWLINE
        "Optional syntax: 2.4*x+3.2" NEWLINE
    },
    {   symexecute,
        "The execute statement reads the content of a file and execute all statements." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: execute \"savedfile\"" NEWLINE
    },
    {   syminput,
        "The input statement either changes or shows the how numeral input is interpreted." NEWLINE
        "Possible input systems are: binary, octal, decimal and hexadecimal. Default is"    NEWLINE
        "decimal. To use positional systems with other bases specify the base number."      NEWLINE
        "Numeral output system can be modified using the output statement." NEWLINE SYNTAXHIGHLIGHT
        "Syntax: input hexadecimal" NEWLINE
        "Syntax: input 4" NEWLINE
    },
    {   symhelp,
        "The help statement can be used to display help about topics and statements." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: help variables" NEWLINE
    },
    {   symoutput,
        "The output statement either changes or shows the how numeral output is shown."   NEWLINE
        "Possible output systems are: binary, octal, decimal and hexadecimal. Default"    NEWLINE
        "is decimal. To use positional systems with other bases specify the base number." NEWLINE
        "Numeral input system can be modified using the input statement." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: output octal" NEWLINE
    },
    {   symlist,
        "No description is available for the list statement." NEWLINE
    },
    {   symshow,
        "The show statement displays the content of a file." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: show \"filetosee\"" NEWLINE
    },
    {   symload,
        "The load statement retrieves a set of defined variables and functions from" NEWLINE
        "a file. Variables and functions can be saved using the save statement." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: load \"savedwork\"" NEWLINE
    },
    {   symsave,
        "The save statement saves defined variables and functions to a file in a" NEWLINE
        "plain text format. Saved variables and functions can be retrieved using" NEWLINE
        "the load statement." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: save \"worktokeep\"" NEWLINE
    },
    {   symversion,
        "Show which version of amath is running." NEWLINE
    },

    {   symvariable,
        "The variable statement shows a list of variables in memory." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: variables" NEWLINE
        NORMALTEXT "optional syntax: vars" NEWLINE
    },
    {   symexit,
        "The exit statement shuts down amath." NEWLINE
        SYNTAXHIGHLIGHT "Syntax: exit" NEWLINE
    }
};

#endif
