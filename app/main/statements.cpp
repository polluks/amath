/*
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

#include "mem.h"
#include "clib.h"
#include "lib/real.h"
#include "lib/charbuf.h"
#include "localize/help.h"
#include "localize/text.h"
#include "localize/start.h"
#include "main/parser.h"
#include "main/graphlist.h"
#include "main/statements.h"
#include "system/console.h"
#include "system/program.h"

// -----------------------------------------------------
// ------------------ ClearStatement -------------------
// -----------------------------------------------------

char* ClearStatement::Execute()
{
    Program->Console->Clear();
    return (char*)EMPTYSTRING;
}

// -----------------------------------------------------
// ------------------- ExitStatement -------------------
// -----------------------------------------------------

char* ExitStatement::Execute()
{
    Program->Exit();
    return (char*)EMPTYSTRING;
}

// -----------------------------------------------------
// ------------------ EmptyStatement -------------------
// -----------------------------------------------------

char* EmptyStatement::Execute()
{
    return (char*)EMPTYSTRING;
}

// -----------------------------------------------------
// ----------------- VersionStatement ------------------
// -----------------------------------------------------

char* VersionStatement::Execute()
{
    output->Empty();
    output->EnsureSize(
        StrLen(BOLD) +
        StrLen(TXTVERSMSG) +
        StrLen(NEWLINE) * 2 +
        StrLen(NORMALTEXT) +
        StrLen(TXTCOMPMSG));

    output->Append(BOLD);
    output->Append(TXTVERSMSG);
    output->Append(NORMALTEXT);
    output->Append(NEWLINE);
    output->Append(TXTCOMPMSG);
    output->Append(NEWLINE);

    return output->GetString();
}

// -----------------------------------------------------
// ------------------ PromptStatement ------------------
// -----------------------------------------------------

PromptStatement::PromptStatement(char* prompt)
{
    AllocAndCopy(&this->prompt,prompt);
}

PromptStatement::~PromptStatement()
{
    delete prompt;
}

char* PromptStatement::Execute()
{
    CharBuffer *buf = new CharBuffer();
    buf->ClearAndCopy(prompt);
    while(buf->RemoveTrailing(' '));
    buf->Append(' ');
    Program->SetPrompt(buf->GetString());
    delete buf;
    return (char*)EMPTYSTRING;
}

// -----------------------------------------------------
// ----------------- PrefsStatement --------------------
// -----------------------------------------------------

PrefsStatement::PrefsStatement()
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

    if (argument == symsave) {
        success = Program->Preferences->Keep();
        success &= Program->Preferences->Save();
        return (success ? HELPPREFSAVE : HELPPREFNOSA);
    } else if (argument == symload) {
        success = Program->Preferences->Load();

        if (success) {
            Program->Console->SetPrompt(
                Program->Preferences->GetPrompt());
            Program->Input->SetDigits(
                Program->Preferences->GetDigits());
            Program->Output->SetDigits(
                Program->Preferences->GetDigits());
            return(HELPPREFLOAD);
        } else {
            return(HELPPREFNOLO);
        }
    }

    return Program->Preferences->GetDescription();
}

// -----------------------------------------------------
// ----------------- MemoryStatement ------------------
// -----------------------------------------------------

char* MemoryStatement::Execute()
{
    long blocks, size, peak;
    MemUsage(&blocks, &size, &peak);
    Number *a = new RealNumber((int)blocks);
    Number *b = new RealNumber((int)size);
    Number *c = new RealNumber((int)peak);

    NumeralSystem *ns = new DecimalSystem(8);
    output->Empty();
    output->EnsureSize(
        StrLen(TXTMEMBLOCKS) + 8 +
        StrLen(TXTMEMSIZE) + 12 +
        StrLen(TXTMEMMAXSIZE) + 12);
    output->Append(TXTMEMBLOCKS);
    output->Append(ns->GetText(a));
    output->Append(NEWLINE);
    output->Append(TXTMEMSIZE);
    output->Append(ns->GetText(b));
    output->Append(NEWLINE);
    output->Append(TXTMEMMAXSIZE);
    output->Append(ns->GetText(c));
    output->Append(NEWLINE);

    delete a;
    delete b;
    delete c;
    delete ns;
    return output->GetString();
}

// -----------------------------------------------------
// ------------------ SilentStatement ------------------
// -----------------------------------------------------

SilentStatement::SilentStatement(StatementNode* statement) :
    statement(statement) { }

SilentStatement::~SilentStatement()
{
    if (statement != NOMEM) {
        delete statement;
    }
}

char* SilentStatement::Execute()
{
    statement->Execute();
    return (char*)EMPTYSTRING;
}

SyntaxNode* SilentStatement::GetNext()
{
    if (iterator == NOMEM) {
        iterator = statement;
        return iterator;
    }

    return NOMEM;
}

void SilentStatement::Attach(SyntaxNode* node)
{
    if (statement == NOMEM) {
        statement = (StatementNode*)node;
        node->SetParent(this);
    }
}

void SilentStatement::Detach(SyntaxNode* node)
{
    if (statement == node) {
        statement = NOMEM;
    }
}

void SilentStatement::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (statement == n) {
        delete statement;
        statement = (StatementNode*)x;
    }
}

// -----------------------------------------------------
// ------------------- EvalStatement -------------------
// -----------------------------------------------------

EvalStatement::EvalStatement(ExpressionNode* expression) :
    StatementNode(), expression(expression) { }

EvalStatement::~EvalStatement()
{
    if (expression != NOMEM) {
        delete expression;
    }
}

char* EvalStatement::Execute()
{
    Number* result = expression->Evaluate();
    Program->SetLastResult(result);
    const char *text = expression->GetText();
    const char *val = Program->Output->GetText(result);

    output->Empty();
    output->EnsureSize(
        StrLen(text) + 3 +
        StrLen(val) +
        StrLen(NEWLINE) + 1);

    output->Append(text);
    output->Append(" = ");
    output->Append(val);
    output->Append(NEWLINE);

    return output->GetString();
}

SyntaxNode* EvalStatement::GetNext()
{
    if (iterator == NOMEM) {
        iterator = expression;
        return iterator;
    }

    return NOMEM;
}

void EvalStatement::Attach(SyntaxNode* node)
{
    if (expression == NOMEM) {
        expression = (ExpressionNode*)node;
        node->SetParent(this);
    }
}

void EvalStatement::Detach(SyntaxNode* node)
{
    if (expression == node) {
        expression = NOMEM;
    }
}

void EvalStatement::Replace(SyntaxNode* n, SyntaxNode* x)
{
    if (expression == n) {
        delete expression;
        expression = (ExpressionNode*)x;
    }
}

// -----------------------------------------------------
// ------------------- HelpStatement -------------------
// -----------------------------------------------------

HelpStatement::HelpStatement() :
    StatementNode() {
    argument = (Symbol)0;
    ident = NOMEM;
}

HelpStatement::HelpStatement(Symbol argument) :
    StatementNode(), argument(argument) {
    ident = NOMEM;
}

HelpStatement::HelpStatement(const char *ident)
{
    argument = symident;
    AllocAndCopy(&this->ident, ident);
}

HelpStatement::~HelpStatement()
{
    if (ident != NOMEM) {
        delete [] ident;
    }
}

char* HelpStatement::Execute()
{
    char *text = argument != symident ?
                 Program->Language->GetHelpText(argument) :
                 Program->Language->GetHelpText(ident);

    output->ClearAndCopy(text);
    return output->GetString();
}

// -----------------------------------------------------
// ----------------- DeleteStatement -------------------
// -----------------------------------------------------

/**
 * @brief Constructor used to delete either all variable or functions.
 *
 */
DeleteStatement::DeleteStatement(Symbol symbol)
{
    type = symbol;
    name = NOMEM;
    argument = NOMEM;
}

/**
 * @brief Constructor used to delete a Variable.
 *
 */
DeleteStatement::DeleteStatement(const char *name) :
    StatementNode()
{
    type = symvariable;
    AllocAndCopy(&this->name, name);
    argument = NOMEM;
}

/**
 * @brief Constructor used to delete a function.
 *
 */
DeleteStatement::DeleteStatement(const char *name, const char *argument) :
    StatementNode()
{
    type = symfunction;
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->argument, argument);
}


DeleteStatement::~DeleteStatement()
{
    if (name != NOMEM) {
        delete [] name;
    }

    if (argument != NOMEM) {
        delete [] argument;
    }
}

char* DeleteStatement::Execute()
{
    bool success = true;
    output->Empty();

    if (type == symvariable && name == NOMEM) {
        Program->Variables->Clear();
    } else if (type == symvariable && name != NOMEM) {
        success = Program->Variables->Delete(name);
        const char *msg = HELPVARNDEF;

        output->EnsureSize(
            StrLen(msg) +
            StrLen(name) +
            StrLen(NEWLINE) + 1);

        output->Append(msg);
        output->Append(name);
        output->Append(NEWLINE);

    } else if (type == symfunction && name == NOMEM) {
        Program->Functions->Clear();
    } else if (type == symfunction && name != NOMEM) {
        success = Program->Functions->Delete(name, argument);
        const char *msg = HELPFUNNDEF;

        output->EnsureSize(
            StrLen(msg) +
            StrLen(name) + 2 +
            StrLen(argument) +
            StrLen(NEWLINE) + 1);

        output->Append(msg);
        output->Append(name);
        output->Append("(");
        output->Append(argument);
        output->Append(")");
        output->Append(NEWLINE);
    }

    return (char*)(success ? EMPTYSTRING : output->GetString());
}

// -----------------------------------------------------
// ----------------- InputStatement --------------------
// -----------------------------------------------------

/**
 * @brief Constructor used to show number of active digits.
 *
 */
InputStatement::InputStatement() :
    base(0) { }

/**
 * @brief Constructor used to set number of active digits.
 *
 */
InputStatement::InputStatement(unsigned int base) :
    StatementNode(), base(base) { }

char* InputStatement::Execute()
{
    const char *text;

    if (base != 0) {
        int digits = Program->Input->GetDigits();
        Program->NewPositionalInput(base, digits);
        text = HELPINPUSETT;
    } else {
        text = HELPINPUSHOW;
    }

    const char *desc = Program->Input->GetName();

    output->Empty();
    output->EnsureSize(StrLen(text) + StrLen(desc) + StrLen(NEWLINE) + 1);
    output->Append(text);
    output->Append(desc);
    output->Append(NEWLINE);
    return output->GetString();
}

// -----------------------------------------------------
// ----------------- OutputStatement -------------------
// -----------------------------------------------------

/**
 * @brief Constructor used to show number of active digits.
 *
 */
OutputStatement::OutputStatement() :
    base(0) { }

/**
 * @brief Constructor used to set number of active digits.
 *
 */
OutputStatement::OutputStatement(unsigned int base) :
    StatementNode(), base(base) { }

char* OutputStatement::Execute()
{
    const char *text;

    if (base != 0) {
        int digits = Program->Output->GetDigits();
        Program->NewPositionalOutput(base, digits);
        text = HELPOUTPSETT;
    } else {
        text = HELPOUTPSHOW;
    }

    const char *desc = Program->Output->GetName();

    output->Empty();
    output->EnsureSize(StrLen(text) + StrLen(desc) + StrLen(NEWLINE) + 1);
    output->Append(text);
    output->Append(desc);
    output->Append(NEWLINE);
    return output->GetString();
}

// -----------------------------------------------------
// ----------------- DigitsStatement -------------------
// -----------------------------------------------------

/**
 * @brief Constructor used to show number of active digits.
 *
 */DigitsStatement::DigitsStatement()
{
    show = true;
}

/**
 * @brief Constructor used to show number of active digits.
 *
 */
DigitsStatement::DigitsStatement(unsigned int digits) :
    digits(digits) {
    show = false;
}

char* DigitsStatement::Execute()
{
    const char *text;

    if (!show) {
        Program->Input->SetDigits(digits);
        Program->Output->SetDigits(digits);
        Program->Preferences->SetDigits(digits);
        text = HELPDIGISETT;
    } else {
        text = HELPDIGISHOW;
        digits = Program->Output->GetDigits();
    }

    Number *d = new RealNumber(digits);
    NumeralSystem *ns = new DecimalSystem(2);
    const char *dtext = ns->GetText(d);
    delete d;

    output->Empty();
    output->EnsureSize(StrLen(text) + StrLen(dtext) + StrLen(NEWLINE) + 1);
    output->Append(text);
    output->Append(dtext);
    output->Append(NEWLINE);

    delete ns;
    return output->GetString();
}

// -----------------------------------------------------
// ------------------ ShowStatement --------------------
// -----------------------------------------------------

ShowStatement::ShowStatement(const char* file)
{
    AllocAndCopy(&this->file, file);
}

ShowStatement::~ShowStatement()
{
    delete [] file;
}

char* ShowStatement::Execute()
{
    CharBuffer *text = Program->Filesystem->LoadTextFile(file);
    if (text == NOMEM)
    {
        return (char*)(MSGNOFILE);
    }

    delete output;
    output = text;
    return text->GetString();
}

// -----------------------------------------------------
// ------------------ ListStatement --------------------
// -----------------------------------------------------

ListStatement::ListStatement() :
    StatementNode()
{
    directory = NOMEM;
}

ListStatement::ListStatement(const char *directory) :
    StatementNode()
{
    AllocAndCopy(&this->directory,  directory);
}

ListStatement::~ListStatement()
{
    if (directory != NOMEM) {
        delete [] directory;
    }
}

char* ListStatement::Execute()
{
    CharBuffer *text = Program->Filesystem->ListDirectory(directory);
    if (text == NOMEM)
    {
        return (char*)(MSGNODIR);
    }

    delete output;
    output = text;
    return text->GetString();
}

// -----------------------------------------------------
// ------------------ LoadStatement --------------------
// -----------------------------------------------------

LoadStatement::LoadStatement(const char *file)
{
    AllocAndCopy(&this->file, file);
}

LoadStatement::~LoadStatement()
{
    delete [] file;
}

char* LoadStatement::Execute()
{
    CharBuffer *input = Program->Filesystem->LoadTextFile(file);
    if (input == NOMEM)
    {
        return (char*)(MSGNOFILE);
    }

    Parser *parser = new Parser(input->GetString());
    delete input;

    SyntaxNode *node = parser->Parse();
    delete parser;

    node->Execute();
    delete node;

    return (char*)HELPLOADSUCC;
}

// -----------------------------------------------------
// ------------------ SaveStatement --------------------
// -----------------------------------------------------

SaveStatement::SaveStatement(const char *file)
{
    AllocAndCopy(&this->file, file);
}

SaveStatement::~SaveStatement()
{
    delete [] file;
}

char* SaveStatement::Execute()
{
    const char *vars = Program->Variables->ListDefinitions();
    const char *funcs = Program->Functions->ListDefinitions();

    if (vars == NOMEM && funcs == NOMEM) {
        return (char*)HELPSAVENOTH;
    }

    int len = 1;
    len += vars  != NOMEM ? StrLen(vars)  : 0;
    len += funcs != NOMEM ? StrLen(funcs) : 0;

    CharBuffer *text = new CharBuffer(len);
    text->Empty();

    if (vars != NOMEM) {
        text->Append(vars);
    }
    if (funcs != NOMEM) {
        text->Append(funcs);
    }

    bool success = Program->Filesystem->SaveTextFile(file, text->GetString());
    delete text;

    return (char*)(success ? HELPSAVESUCC : HELPSAVEFAIL);
}

// -----------------------------------------------------
// ---------------- ExecuteStatement -------------------
// -----------------------------------------------------

ExecuteStatement::ExecuteStatement(const char *file)
{
    AllocAndCopy(&this->file, file);
}

ExecuteStatement::~ExecuteStatement()
{
    delete [] file;
}

char* ExecuteStatement::Execute()
{
    CharBuffer *input = Program->Filesystem->LoadTextFile(file);
    if (input == NOMEM)
    {
        return (char*)(MSGNOFILE);
    }

    Parser *parser = new Parser(input->GetString());
    delete input;

    SyntaxNode *node = parser->Parse();
    delete parser;

    const char *res = node->Execute();
    output->ClearAndCopy(res);
    delete node;

    return output->GetString();
}

// -----------------------------------------------------
// ------------------ PlotStatement --------------------
// -----------------------------------------------------

PlotStatement::PlotStatement(const char* name, const char* parameter, const char* file) :
    StatementNode()
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
    AllocAndCopy(&this->file, file);
}

PlotStatement::PlotStatement(const char* name, const char* parameter) :
    StatementNode()
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
    file = NOMEM;
}

PlotStatement::~PlotStatement()
{
    delete [] name;
    delete [] parameter;

    if (file != NOMEM) {
        delete [] file;
    }
}

char* PlotStatement::Execute()
{
    UserFunction *function = Program->Functions->GetFunctionDef(name, parameter);

    if (function == NOMEM) {
        return (char*)("Function does not exists." NEWLINE);
    }

    output->Empty();

    Grid *grid = new Grid(function);
    static const int width = 400;
    static const int height = 300;

    grid->SetScreenBounderues(0, width, 20, height);
    bool first = true;

    static const double min = -5.0;
    static const double max = +5.0;
    grid->SetFunctionBounderies(min, max);

    double x = min;
    double step = grid->GetHorizontalResolution();

    int screenX;
    int screenY;

    RealNumber *n = new RealNumber();
    NumeralSystem *ns = new DecimalSystem(5);

    while (x < max) {
        grid->GetScreenCoordinates(x, &screenX, &screenY);

        output->EnsureGrowth(32);

        if (screenX != -1 && screenY != -1) {
            if (first) {
                output->Append('(');
                n->SetRealValue(screenX);
                output->Append(ns->GetText(n));
                output->Append(',');
                n->SetRealValue(height - screenY);
                output->Append(ns->GetText(n));
                output->Append(')');
                output->Append(NEWLINE);
                first = false;
            } else {
                output->Append('(');
                n->SetRealValue(screenX);
                output->Append(ns->GetText(n));
                output->Append(',');
                n->SetRealValue(height - screenY);
                output->Append(ns->GetText(n));
                output->Append(')');
                output->Append(NEWLINE);
            }
        }

        x = x + step;
    }

    delete n;
    delete ns;

    return output->GetString();
}

// -----------------------------------------------------
// ------------------ DrawStatement --------------------
// -----------------------------------------------------

DrawStatement::DrawStatement(const char* name, const char* parameter)
{
    AllocAndCopy(&this->name, name);
    AllocAndCopy(&this->parameter, parameter);
}

DrawStatement::~DrawStatement()
{
    delete [] name;
    delete [] parameter;
}

char* DrawStatement::Execute()
{
    UserFunction *function = Program->Functions->GetFunctionDef(name, parameter);

    if (function == NOMEM) {
        return (char*)("Function does not exists." NEWLINE);
    }

    GraphWindow *graph = Program->Graphs->CreateNewWindow();

    if (graph == NOMEM) {
        return (char*)"Graphs are not supported in this version.";
    }

    graph->OpenGraphWindow(function);
    graph->DrawGraph(function);

    return (char*)EMPTYSTRING;
}

