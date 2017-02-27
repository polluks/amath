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

#include "amath.h"
#include "license.h"

LicenseStatement::LicenseStatement() :
    StatementNode(
    NEWLINE BOLD
    "Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>" NORMALTEXT NEWLINE
    "Copyright (c) 2007 The NetBSD Foundation, Inc." NEWLINE
    "Copyright (c) 1990, 1993 The Regents of the University of California." NEWLINE
    "All rights reserved." NEWLINE
    NEWLINE
    "This code is derived from software written by Stephen L. Moshier." NEWLINE
    "It is redistributed by the NetBSD Foundation by permission of the author." NEWLINE
    NEWLINE
    "This code is derived from software contributed to Berkeley by" NEWLINE
    "Mike Hibler and Chris Torek." NEWLINE
    NEWLINE
    "Redistribution and use in source and binary forms, with or without" NEWLINE
    "modification, are permitted provided that the following conditions are met:" NEWLINE
    NEWLINE
    "* Redistributions of source code must retain the above copyright notice, this" NEWLINE
    "  list of conditions and the following disclaimer." NEWLINE
    NEWLINE
    "* Redistributions in binary form must reproduce the above copyright notice," NEWLINE
    "  this list of conditions and the following disclaimer in the documentation" NEWLINE
    "  and/or other materials provided with the distribution." NEWLINE
    NEWLINE
    "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"" NEWLINE
    "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE" NEWLINE
    "IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE" NEWLINE
    "DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE" NEWLINE
    "FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL" NEWLINE
    "DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR" NEWLINE
    "SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER" NEWLINE
    "CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY," NEWLINE
    "OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE" NEWLINE
    "OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE." NEWLINE
    NEWLINE ITALICS
    "Specific details should be found in the source files." NORMALTEXT NEWLINE
    NEWLINE)
{
}

LicenseStatement::~LicenseStatement()
{
}

char* LicenseStatement::Execute()
{
    return statementText;
}
