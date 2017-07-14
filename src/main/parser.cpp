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
 * https://amath.innolan.net
 * 
 */

#include "amath.h"
#include "amathc.h"
#include "parser.h"
#include "values.h"
#include "operators.h"
#include "statements.h"
#include "userfunction.h"
#include "lib/numb.h"
#include "lib/cplex.h"
#include "lib/ntextd.h"
#include "loc/text.h"
#include "system/program.h"

Parser::Parser(const char* input)
{
    lexer = new Lexer(input);
    token = nullptr;
    errorNode = nullptr;
    syntaxError = 0;
}

Parser::~Parser()
{
    delete lexer;
}

SyntaxNode* Parser::Parse()
{
    lexer->Tokenize();
    token = nullptr;

    StatementBlockNode* block = nullptr;
    SyntaxNode* result;
    Token* current;

    do
    {
        result = TryParseStatement();

        GetToken();
        if (token->symbol == symdelimiter || (token->symbol == symend && block != nullptr))
        {
            if (block == nullptr)
            {
                block = new StatementBlockNode();
            }

            if (result != nullptr)
            {
                block->Add(result);
            }

            while (token->symbol == symdelimiter)
            {
                GetToken();
            }
        }
        else if (token->symbol != symend)
        {
            if (result != nullptr)
            {
                delete result;
            }

            if (block == nullptr)
            {
                block = new StatementBlockNode();
            }

            result = new ErrorNode(lexer->GetInput(), token->GetPos());
            block->Add(result);

            // Skip until next statement
            do
            {
                GetToken();
            }
            while (token->symbol != symdelimiter && token->symbol != symend);
        }

        current = token;
        PutToken();
    }
    while (current->symbol != symend);

    if (block != nullptr)
        return block;

    if (result == nullptr)
        return new EmptyStatement();

    return result;;
}

SyntaxNode* Parser::TryParseStatement()
{
    GetToken();
    if (token->symbol == symend || token->symbol == symdelimiter)
    {
        PutToken();
        return nullptr;
    }
    PutToken();

    errorNode = nullptr;
    syntaxError = -1;
    SyntaxNode* result = ParseStatement();

    if (errorNode == nullptr && syntaxError != -1)
    {
        errorNode = new ErrorNode(lexer->GetInput(), syntaxError);
    }

    if (errorNode != nullptr)
    {
        delete result;
        result = errorNode;
    }

    return result;
}

// -----------------------------------------------------
// -------------- Recursive-descent logic --------------
// -----------------------------------------------------

SyntaxNode* Parser::ParseStatement()
{
    SyntaxNode* res;

    GetToken();
    switch (token->symbol)
    {
    case symhelp:
        res = ParseHelpStatement();
        break;
    case symdelete:
        res = ParseDeleteStatement();
        break;
    case symdef:
        res = ParseFunctionDef();
        break;
#if defined(UNIX) || defined(HAIKU) || defined(AMIGA)
    case symlist:
        res = ParseListStatement();
        break;
#endif
    case symshow:
    case symload:
    case symsave:
    case symexecute:
        res = ParseFileStatement();
        break;
    case syminput:
    case symoutput:
        res = ParseNumeralStatement();
        break;
    case symprompt:
        res = ParsePromptStatement();
        break;
    case symprefs:
        res = ParsePrefsStatement();
        break;
    case symdigits:
        res = ParseDigistStatement();
        break;
    case symdraw:
    case symplot:
        res = ParseDrawStatement();
        break;
    case symabout:
        res = new AboutStatement();
        break;
    case symlicense:
        res = new LicenseStatement();
        break;
    case symversion:
        res = new VersionStatement();
        break;
    case symexit:
        res = new ExitStatement();
        break;
#if defined(AMIGA) || defined(TERMIOS) || defined(WINDOWS)
    case symclear:
        res = new ClearStatement();
        break;
#endif
    case symmem:
        res = new MemoryStatement();
        break;
    case symvariable:
        res = new ListVariablesStatement();
        break;
    case symfunction:
        res = new ListFunctionsStatement();
        break;
    case symeval:
        res = new EvalStatement(ParseExpression());
        break;
    default:
        PutToken();
        res = ParseDefault();
    }

    return res;
}

SyntaxNode* Parser::ParseDefault()
{
    Token* temp = token;

    // Peek tokens
    bool funcdef = Expect(symident);
    funcdef = funcdef && Expect(symlparen);
    funcdef = funcdef && Expect(symident);
    funcdef = funcdef && Expect(symrparen);
    funcdef = funcdef && Expect(symassign);

    // Restart parsing
    syntaxError = -1;
    errorNode = nullptr;
    token = temp;

    if (funcdef)
    {
        return ParseFunctionDef();
    }

    return ParseEvaluation();
}

SyntaxNode* Parser::ParseEvaluation()
{
    ExpressionNode* exp = ParseExpression();
    if (exp == nullptr)
    {
        return nullptr;
    }

    StatementNode* sta = new EvalStatement(exp);
    if (exp->IsSilent())
    {
        sta = new SilentStatement(sta);
    }

    return sta;
}

ExpressionNode* Parser::ParseExpression()
{
    return ParseAddSubstract();
}

ExpressionNode* Parser::ParseAddSubstract()
{
    ExpressionNode* node = ParseFactor();

    GetToken();
    while (token->symbol == symplus || token->symbol == symminus)
    {
        if (token->symbol == symplus)
        {
            node = new AdditionNode(node, ParseFactor());
        }
        else if (token->symbol == symminus)
        {
            node = new SubtractionNode(node, ParseFactor());
        }

        GetToken();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParseFactor()
{
    ExpressionNode* node = ParsePower();

    GetToken();
    while (token->symbol == symtimes || token->symbol == symslash)
    {
        if (token->symbol == symtimes)
        {
            node = new MultiplicationNode(node, ParsePower());
        }
        else if (token->symbol == symslash)
        {
            node = new DivisionNode(node, ParsePower());
        }

        GetToken();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParsePower()
{
    ExpressionNode* node = ParseUnary();

    GetToken();
    while (token->symbol == sympower)
    {
        node = new PowerNode(node, ParseUnary());
        GetToken();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParseUnary()
{
    ExpressionNode* node;

    GetToken();
    if (token->symbol == symminus)
    {
        node = new UnaryNode(ParseAtomic());
    }
    else
    {
        PutToken();
        node = ParseAtomic();
    }

    return node;
}

ExpressionNode* Parser::ParseAtomic()
{
    ExpressionNode* node;

    GetToken();
    if (token->symbol == symlparen)
    {
        node = ParseExpression();
        Expect(symrparen);
    }
    else if (token->symbol == symabsolute)
    {
        node = new AbsoluteNode(ParseExpression());
        Expect(symabsolute);
    }
    else if (token->symbol == symident)
    {
        node = ParseIdent();
    }
    else if (token->symbol == sympi)
    {
        node = new PiNode();
    }
    else if (token->symbol == syme)
    {
        node = new EulersNumberNode();
    }
    else if (token->symbol == symi)
    {
        node = new ComplexiNode();
    }
    else if (token->symbol == symins)
    {
        node = new InsVariableNode();
    }
    else if (token->symbol == symnumber)
    {
        node = ParseNumber();
    }
    else
    {
        node = new NumericValueNode();
        syntaxError = token->GetPos();
    }

    if (Peek()->symbol == symfactorial)
    {
        GetToken();
        node = new FactorialNode(node);
    }

    return node;
}

ExpressionNode* Parser::ParseIdent()
{
    ExpressionNode* node;
    Token* identToken = token;

    GetToken();
    if (token->symbol == symlparen)
    {
        ExpressionNode* parameter = ParseExpression();
        Expect(symrparen);
        node = Program->Functions->GetFunctionCall(identToken->GetText(), parameter);

        if (node == nullptr)
        {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPFUNNDEF,
                identToken->GetText(),
                identToken->GetPos());

            delete parameter;
            node = new NumericValueNode();
        }
    }
    else if (token->symbol == symassign)
    {
        Variable* var = Program->Variables->CreateVariable(identToken->GetText());
        node = new AssignmentNode(new VariableNode(var), ParseExpression());
    }
    else
    {
        PutToken();
        Variable* var = Program->Variables->GetVariable(token->GetText());

        if (var == nullptr)
        {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPVARNDEF,
                identToken->GetText(),
                identToken->GetPos());

            node = new NumericValueNode();
        }
        else
        {
            node = new VariableNode(var);
        }
    }

    return node;
}

ExpressionNode* Parser::ParseNumber()
{
    const char* a = token->GetText();
    Number* number;

    GetToken();
    if (token->symbol == symi)
    {
        Number* imag = Program->Input->Parse(a);
        number = new ComplexNumber(0.0, imag->GetRealValue());
        delete imag;
    }
    else
    {
        PutToken();
        number = Program->Input->Parse(a);
    }

    return new NumericValueNode(number);
}

// -----------------------------------------------------
// ------------------- Token logic ---------------------
// -----------------------------------------------------

void Parser::GetToken()
{
    if (token == nullptr)
    {
        token = lexer->GetFirstToken();
    }
    else
    {
        token = token->GetNextToken();
    }
}

Token* Parser::Peek() const
{
    if (token == nullptr)
        return lexer->GetFirstToken();

    return token->GetNextToken();
}

void Parser::PutToken()
{
    token = token->GetLastToken();
}

bool Parser::Expect(Symbol symbol)
{
    GetToken();
    if (token->symbol != symbol)
    {
        syntaxError = token->GetPos();
        return false;
    }

    return true;
}

// -----------------------------------------------------
// ----------------- Statement logic -------------------
// -----------------------------------------------------

SyntaxNode* Parser::ParseFunctionDef()
{
    Expect(symident);
    Token* funcToken = token;
    Expect(symlparen);
    Expect(symident);
    Token* funcVariable = token;
    Expect(symrparen);
    Expect(symassign);

    if (Program->Functions->IsSystemFunction(funcToken->GetText()))
    {
        errorNode = new ErrorNode(
            lexer->GetInput(),
            HELPFUNRDEF,
            funcToken->GetText(),
            funcToken->GetPos());

        return nullptr;
    }

    UserFunction* function = Program->Functions->GetFunctionDef(funcToken->GetText());
    Variable* variable = function->CreateVariable(funcVariable->GetText());
    Program->Variables->InsertTemporaryVariable(variable);
    function->SetExpression(ParseExpression());
    Program->Variables->RemoveTemporaryVariable();

    // TODO: Move logic to FunctionDefinitionNode
    return new FunctionDefinitionNode();
}

SyntaxNode* Parser::ParseHelpStatement()
{
    GetToken();

    if (token->symbol == symdelimiter || token->symbol == symend)
    {
        PutToken();
        return new HelpStatement();
    }

    if (token->symbol == symident)
        return new HelpStatement(token->GetText());

    return new HelpStatement(token->symbol);
}

SyntaxNode* Parser::ParseDeleteStatement()
{
    GetToken();
    if (token->symbol == symvariable || token->symbol == symfunction)
    {
        return new DeleteStatement(token->symbol);
    }

    if (token->symbol != symident)
    {
        syntaxError = token->GetPos();
        return nullptr;
    }

    Token* identToken = token;

    GetToken();
    if (token->symbol == symlparen)
    {
        Expect(symident);
        Token* parameter = token;
        Expect(symrparen);
        return new DeleteStatement(identToken->GetText(), parameter->GetText());
    }

    PutToken();
    return new DeleteStatement(token->GetText());
}

SyntaxNode* Parser::ParseListStatement()
{
    GetToken();
    if (token->symbol == symqident)
        return new ListStatement(token->GetText());

    if (token->symbol == symend || token->symbol == symdelimiter)
    {
        PutToken();
        return new ListStatement();
    }

    syntaxError = token->GetPos();
    return nullptr;
}

SyntaxNode* Parser::ParseFileStatement()
{
    Token* statement = token;

    Expect(symqident);
    Token* identToken = token;

    if (statement->symbol == symload)
        return new LoadStatement(identToken->GetText());

    if (statement->symbol == symsave)
        return new SaveStatement(identToken->GetText());

    if (statement->symbol == symexecute)
        return new ExecuteStatement(identToken->GetText());

    if (statement->symbol == symshow)
        return new ShowStatement(identToken->GetText());

    return new ErrorNode(
        lexer->GetInput(),
        HELPUERROR, EMPTYSTRING,
        statement->GetPos());
}

SyntaxNode* Parser::ParseNumeralStatement()
{
    Token* statement = token;
    unsigned int base;

    GetToken();
    switch (token->symbol)
    {
    case symend:
    case symdelimiter:
        PutToken();
        return (statement->symbol == syminput)
                   ? static_cast<SyntaxNode*>(new InputStatement())
                   : static_cast<SyntaxNode*>(new OutputStatement());
    case symbin:
        base = 2;
        break;
    case symoct:
        base = 8;
        break;
    case symdec:
        base = 10;
        break;
    case symhex:
        base = 16;
        break;
    default:
        base = 0;
    }

    if (base == 0 && token->symbol != symnumber)
    {
        syntaxError = token->GetPos();
        return nullptr;
    }

    if (base == 0)
    {
        NumeralSystem* nsys = new DecimalSystem(0);
        Number* number = nsys->Parse(token->GetText());
        base = number->GetIntegerValue();
        delete number;
        delete nsys;

        if (base < 2 || base > 32)
        {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPPNUMERA,
                token->GetText(),
                token->GetPos());

            return nullptr;
        }
    }

    return (statement->symbol == syminput)
               ? static_cast<SyntaxNode*>(new InputStatement(base))
               : static_cast<SyntaxNode*>(new OutputStatement(base));
}

SyntaxNode* Parser::ParseDigistStatement()
{
    GetToken();
    if (token->symbol == symdelimiter || token->symbol == symend)
    {
        PutToken();
        return new DigitsStatement();
    }

    if (token->symbol != symnumber)
    {
        syntaxError = token->GetPos();
        return nullptr;
    }

    NumeralSystem* nsys = new DecimalSystem(0);
    Number* number = nsys->Parse(token->GetText());
    int digits = number->GetIntegerValue();
    delete number;
    delete nsys;

    if (digits < 0 || digits > 15)
    {
        errorNode = new ErrorNode(
            lexer->GetInput(),
            HELPPDIGITS,
            token->GetText(),
            token->GetPos());

        return nullptr;
    }

    return new DigitsStatement(digits);
}

SyntaxNode* Parser::ParsePromptStatement()
{
    GetToken();
    if (token->symbol == symqident)
    {
        return new PromptStatement(token->GetText());
    }

    PutToken();
    return nullptr;
}

SyntaxNode* Parser::ParsePrefsStatement()
{
    GetToken();
    if (token->symbol == symload || token->symbol == symsave)
    {
        return new PrefsStatement(token->symbol);
    }

    PutToken();
    return new PrefsStatement();;
}

SyntaxNode* Parser::ParseDrawStatement()
{
    Token* statement = token;

    Expect(symident);
    Token* identToken = token;
    Expect(symlparen);
    Expect(symident);
    Token* paramToken = token;
    Expect(symrparen);

    if (statement->symbol == symplot)
        return new PlotStatement(identToken->GetText(), paramToken->GetText());

    return new DrawStatement(identToken->GetText(), paramToken->GetText());
}
