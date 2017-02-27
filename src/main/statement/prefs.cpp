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

#include "prefs.h"
#include "localize/lex.h"
#include "localize/help.h"
#include "system/program.h"

PrefsStatement::PrefsStatement()
    : StatementNode()
{
    argument = Symbol(0);
}

PrefsStatement::PrefsStatement(Symbol argument)
{
    this->argument = argument;
}

char* PrefsStatement::Execute()
{
    bool success;
    
    if (argument == symsave)
    {
        success = Program->Preferences->Keep();
        success &= Program->Preferences->Save();
        return (success ? HELPPREFSAVE : HELPPREFNOSA);
    }
    
    if (argument == symload)
    {
        success = Program->Preferences->Load();
        
        if (success)
        {
            Program->Console->SetPrompt(Program->Preferences->GetPrompt());
            Program->Input->SetDigits(Program->Preferences->GetDigits());
            Program->Output->SetDigits(Program->Preferences->GetDigits());
            return HELPPREFLOAD;
        }
        
        return HELPPREFNOLO;
    }
    
    return Program->Preferences->GetDescription();
}