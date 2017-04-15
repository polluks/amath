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

#include "help.h"
#include "amath.h"
#include "amathc.h"
#include "loc/help.h"
#include "loc/text.h"
#include "system/program.h"

HelpStatement::HelpStatement() :
    StatementNode()
{
    argument = static_cast<Symbol>(0);
    ident = nullptr;
}

HelpStatement::HelpStatement(Symbol argument) :
    StatementNode(), argument(argument)
{
    ident = nullptr;
}

HelpStatement::HelpStatement(const char* ident)
{
    argument = symident;
    AllocAndCopy(&this->ident, ident);
}

HelpStatement::~HelpStatement()
{
    if (ident != nullptr)
    {
        delete [] ident;
    }
}

char* HelpStatement::Execute()
{
    if (argument == symstatement)
    {
        return StatementHelp();
    }
    else if (argument == symident)
    {
        char* text = Program->Language->GetHelpText(ident);
        output->ClearAndCopy(text);
        return output->GetString();
    }

    char* text = Program->Language->GetHelpText(argument);
    output->ClearAndCopy(text);
    return output->GetString();
}

#define APPENDHELP(x) \
    text = x; \
    output->EnsureGrowth(StrLen(text)); \
    output->Append(text);

char* HelpStatement::StatementHelp() const
{
    char* text;
    output->ClearBuffer();

    APPENDHELP(STATEMENTLINE)
#if defined(AMIGA) || defined(TERMIOS) || defined(WINDOWS)
    APPENDHELP(STATEMENTCLEAR)
#endif
    APPENDHELP(STATEMENTDEF)
    APPENDHELP(STATEMENTDELETE)
    APPENDHELP(STATEMENTDIGITS)
    APPENDHELP(STATEMENTDEF)
    APPENDHELP(STATEMENTDELETE)
    APPENDHELP(STATEMENTDIGITS)
    APPENDHELP(STATEMENTEVAL)
    APPENDHELP(STATEMENTEXECUTE)
    APPENDHELP(STATEMENTFUNCS)
    APPENDHELP(STATEMENTINPUT)
    APPENDHELP(STATEMENTHELP)
    APPENDHELP(STATEMENTOUTPUT)
#if defined(UNIX) || defined(HAIKU) || defined(AMIGA)
    APPENDHELP(STATEMENTLIST)
#endif
    APPENDHELP(STATEMENTSHOW)
    APPENDHELP(STATEMENTLOAD)
    APPENDHELP(STATEMENTSAVE)
    APPENDHELP(STATEMENTVARS)
    APPENDHELP(STATEMENTVERSION)
    APPENDHELP(STATEMENTMEMORY)
    APPENDHELP(STATEMENTEXIT)
    APPENDHELP(STATEMENTLINE)
    APPENDHELP(STATEMENTFOOTER)

    return output->GetString();
}
