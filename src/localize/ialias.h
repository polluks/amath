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
 * Project homepage:
 * http://amath.innolan.net
 * 
 */

#ifndef AMATH_LOCALIZE_IDENT_ALIAS_H
#define AMATH_LOCALIZE_IDENT_ALIAS_H

#include "amatht.h"

static const identalias identaliases[] = {
    {"squareroot", "sqrt"},
    {"sqr", "sqrt"},
    {"cuberoot", "cbrt"},
    {"cbr", "cbrt"},
    {"log2", "lb"},
    {"log", "lg"},
    {"log10", "lg"},
    {"sine", "sin"},
    {"cosine", "cos"},
    {"tangent", "tan"},
    {"secant", "sec"},
    {"cosec", "csc"},
    {"cosecant", "csc"},
    {"ctg", "cot"},
    {"ctn", "cot"},
    {"cotangent", "cot"},   
    {"arcsine", "asin"},
    {"arccosine", "acos"},
    {"arctangent", "atan"},
    {"arccotangent", "acot"},
    {"arcsecant", "asec"},
    {"arccosecant", "acsc"},
    {"arsin", "asin"},
    {"arcos", "acos"},
    {"artan", "atan"},
    {"arcot", "acot"},
    {"arsec", "asec"},
    {"arcsc", "acsc"},
    {"arcsin", "asin"},
    {"arccos", "acos"},
    {"arctan", "atan"},
    {"arccot", "acot"},
    {"arcsec", "asec"},
    {"arccsc", "acsc"},
    {"arsinh", "asinh"},
    {"arcosh", "acosh"},
    {"artanh", "atanh"},
    {"arcoth", "acoth"},
    {"arsech", "asech"},
    {"arcsch", "acsch"},
    {"arcsinh", "asinh"},
    {"arccosh", "acosh"},
    {"arctanh", "atanh"},
    {"arccoth", "acoth"},
    {"arcsech", "asech"},
    {"arccsch", "acsch"},
    // exsecant
    {"exsecant", "exsec"},
    {"exteriorsecant", "exsec"},
    {"externalsecant", "exsec"},
    {"outwardsecant", "exsec"},
    {"outersecant", "exsec"},
    {"exs", "exsec"},
    // excosecant
    {"excosecant", "excsc"},
    {"exteriorcosecant", "excsc"},
    {"externalcosecant", "excsc"},
    {"outwardcosecant", "excsc"},
    {"outercosecant", "excsc"},
    {"excosec", "excsc"},
    {"coexsec", "excsc"},
    {"exc", "excsc"},
    // inverse exsecant
    {"arcexsecant", "aexsec"},
    {"arcexsec", "aexsec"},
    {"aexs", "aexsec"},
    // inverse excosecant
    {"arcexcosecant", "aexcsc"},
    {"arcexcosec", "aexcsc"},
    {"arcexcsc", "aexcsc"},
    {"aexc", "aexcsc"},
    // versed sine
    {"versedsine", "ver"},
    {"versine", "ver"},
    {"siv", "ver"},
    {"vers", "ver"},
    {"sinver", "ver"},
    {"versin", "ver"},
    // versed cosine
    {"versedcosine", "vcs"},
    {"vercosine", "vcs"},
    {"vercos", "vcs"},
    {"vercosin", "vcs"},
    // coversed sine
    {"coversedsine", "cvs"},
    {"coversine", "cvs"},
    {"cosinusversus", "cvs"},
    {"coversinus", "cvs"},
    {"cosiv", "cvs"},
    {"covers", "cvs"},
    {"coversin", "cvs"},
    // coversed cosine
    {"coversedcosine", "cvc"},
    {"covercosine", "cvc"},
    {"covercos", "cvc"},
    {"covercos", "cvc"},
    {"covercosin", "cvc"},
    // haversed sine
    {"haversedsine", "hv"},
    {"haversine", "hv"},
    {"semiversus", "hv"},
    {"haversin", "hv"},
    {"semiversin", "hv"},
    {"semiversinus", "hv"},
    {"havers", "hv"},
    {"hav", "hv"},
    {"hvs", "hv"},
    {"sem", "hv"},
    // haversed cosine
    {"haversedcosine", "hvc"},
    {"havercosine", "hvc"},
    {"havercosin", "hvc"},
    {"havercos", "hvc"},
    {"hac", "hvc"},
    {"sem", "hvc"},
    // hacoversed sine
    {"hacoversedsine", "hcv"},
    {"hacoversine", "hcv"},
    {"cohaversine", "hcv"},
    {"hacoversin", "hcv"},
    {"semicoversin", "hcv"},
    {"hacovers", "hcv"},
    {"hacov", "hcv"},
    // hacoversed cosine
    {"hacoversedcosine", "hcc"},
    {"hacovercosine", "hcc"},
    {"cohavercosine", "hcc"},
    {"hacovercosin", "hcc"},
    {"hacovercos", "hcc"},
    // inverse versed sine
    {"avers", "aver"},
    {"arcvers", "aver"},
    {"arcversin", "aver"},
    {"arcversine", "aver"},
    // inverse versed cosine
    {"avercos", "avcs"},
    {"arcvercos", "avcs"},
    {"arcvercosin", "avcs"},
    {"arcvercosine", "avcs"},
    // inverse coversed sine
    {"acovers", "acvs"},
    {"arccovers", "acvs"},
    {"arccoversin", "acvs"},
    {"arccoversine", "acvs"},
    // inverse coversed cosine
    {"acovercos", "acvc"},
    {"arccovercos", "acvc"},
    {"arccovercosin", "acvc"},
    {"arccovercosine", "acvc"},
    // inverse haversed sine
    {"ahvs", "ahv"},
    {"ahav", "ahv"},
    {"invhav", "ahv"},
    {"archav", "ahv"},
    {"archaversin", "ahv"},
    {"archaversine", "ahv"},
    // inverse haversed cosine
    {"archavercos", "ahvc"},
    {"archavercosin", "ahvc"},
    {"archavercosine", "ahvc"},
    // inverse hacoversed sine
    {"archacoversine", "ahcv"},
    {"archacoversin", "ahcv"},
    // inverse hacoversed cosine
    {"archacovercos", "ahcc"},
    {"archacovercosin", "ahcc"},
    {"archacovercosine", "ahcc"},
    // exsecant
    {"exsecant", "exsec"},
    {"outwardsecant", "exsec"},
    {"outersecant", "exsec"},
    {"exteriorsecant", "exsec"},
    {"externalsecant", "exsec"},
    {"exs", "exsec"},
    // excosecant
    {"excosecant", "excsc"},
    {"coexsecant", "excsc"},
    {"exteriorcosecant", "excsc"},
    {"externalcosecant", "excsc"},
    {"outwardcosecant", "excsc"},
    {"outercosecant", "excsc"},
    {"excosecant", "excsc"},
    {"excosec", "excsc"},
    {"coexsec", "excsc"},
    {"exc", "excsc"}
};

#endif
