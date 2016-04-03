/*
 * Copyright (c) 2015-2016 Carsten Sonne Larsen
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

#include "clib.h"
#include "lib/numb.h"
#include "lib/real.h"
#include "lib/cplex.h"
#include "main/parser.h"
#include "main/values.h"
#include "main/operators.h"
#include "main/functions.h"
#include "main/statements.h"
#include "localize/text.h"
#include "system/program.h"

Parser::Parser(const char *input)
{
    lexer = new Lexer(input);
}

Parser::~Parser()
{
    delete lexer;
}

SyntaxNode* Parser::Parse()
{
    lexer->Tokenize();
    token = NOMEM;

    StatementBlockNode *block = NOMEM;
    SyntaxNode *result;
    Token *current;

    do {
        result = TryParseStatement();

        GetToken();
        if (token->symbol == symdelimiter || (token->symbol == symend && block != NOMEM)) {
            if (block == NOMEM) {
                block = new StatementBlockNode();
            }

            if (result != NOMEM) {
                block->Add(result);
            }

            while (token->symbol == symdelimiter) {
                GetToken();
            }
        } else if (token->symbol != symend) {
            if (result != NOMEM) {
                delete result;
            }

            result = new ErrorNode(lexer->GetInput(), token->GetPos());
            if (block != NOMEM) {
                block->Add(result);
            }

            GetToken();
        }

        current = token;
        PutToken();
    } while (current->symbol != symend);

    return block != NOMEM ? block :
           result != NOMEM ? result : new EmptyStatement();;
}

SyntaxNode* Parser::TryParseStatement()
{
    GetToken();
    if(token->symbol == symend || token->symbol == symdelimiter) {
        PutToken();
        return NOMEM;
    }
    PutToken();

    errorNode = NOMEM;
    syntaxError = -1;
    SyntaxNode *result = ParseStatement();

    if (errorNode == NOMEM && syntaxError != -1) {
        errorNode = new ErrorNode(lexer->GetInput(), syntaxError);
    }

    if (errorNode != NOMEM) {
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
    SyntaxNode* res = NOMEM;

    GetToken();
    switch (token->symbol) {
    case symhelp:
        res = ParseHelpStatement();
        break;
    case symdelete:
        res = ParseDeleteStatement();
        break;
    case symdef:
        res = ParseFunctionDef();
        break;
    case symlist:
        res = ParseListStatement();
        break;
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
    case symversion:
        res = new VersionStatement();
        break;
    case  symexit:
        res = new ExitStatement();
        break;
    case symclear:
        res =  new ClearStatement();
        break;
    case symmem:
        res = new MemoryStatement();
        break;
    case  symvariable:
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
    Token *temp = token;

    // Peek tokens
    bool funcdef = Expect(symident);
    funcdef = funcdef && Expect(symlparen);
    funcdef = funcdef && Expect(symident);
    funcdef = funcdef && Expect(symrparen);
    funcdef = funcdef && Expect(symassign);

    // Restart parsing
    syntaxError = -1;
    errorNode = NOMEM;
    token = temp;

    if (funcdef) {
        return ParseFunctionDef();
    } else {
        return ParseEvaluation();
    }
}

SyntaxNode* Parser::ParseEvaluation()
{
    ExpressionNode *exp = ParseExpression();
    if (exp == NOMEM) {
        return NOMEM;
    }

    StatementNode *sta = new EvalStatement(exp);
    if (exp->IsSilent()) {
        sta = new SilentStatement(sta);
    }

    return sta;
}

ExpressionNode* Parser::ParseExpression ()
{
    return ParseAddSubstract();
}

ExpressionNode* Parser::ParseAddSubstract ()
{
    ExpressionNode* node = ParseFactor ();

    GetToken();
    while (token->symbol == symplus || token->symbol == symminus) {
        if (token->symbol == symplus) {
            node = new AdditionNode (node, ParseFactor ());
        } else if (token->symbol == symminus) {
            node = new SubtractionNode (node, ParseFactor ());
        }

        GetToken();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParseFactor ()
{
    ExpressionNode* node = ParsePower ();

    GetToken();
    while (token->symbol == symtimes || token->symbol == symslash) {
        if (token->symbol == symtimes) {
            node = new MultiplicationNode (node, ParsePower ());
        } else if (token->symbol == symslash) {
            node = new DivisionNode (node, ParsePower ());
        }

        GetToken();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParsePower()
{
    ExpressionNode* node = ParseUnary ();

    GetToken();
    while (token->symbol == sympower) {
        node = new PowerNode (node, ParseUnary ());
        GetToken ();
    }

    PutToken();
    return node;
}

ExpressionNode* Parser::ParseUnary()
{
    ExpressionNode* node;

    GetToken();
    if (token->symbol == symminus) {
        node = new UnaryNode(ParseAtomic ());
    } else {
        PutToken();
        node = ParseAtomic();
    }

    return node;
}

ExpressionNode* Parser::ParseAtomic ()
{
    ExpressionNode* node;

    GetToken();
    if (token->symbol == symlparen) {
        node = ParseExpression();
        Expect(symrparen);
    } else if (token->symbol == symabsolute) {
        node = new AbsoluteNode(ParseExpression());
        Expect(symabsolute);
    } else if (token->symbol == symident) {
        node = ParseIdent();
    } else if (token->symbol == sympi) {
        node = new PiNode();
    } else if (token->symbol == syme) {
        node = new EulersNumberNode();
    } else if (token->symbol == symi) {
        node = new ComplexiNode();
    } else if (token->symbol == symins) {
        node = new InsVariableNode();
    } else if (token->symbol == symnumber) {
        node = ParseNumber();
    } else {
        node = new NumericValueNode();
        syntaxError = token->GetPos();
    }

    return node;
}

ExpressionNode* Parser::ParseIdent()
{
    ExpressionNode *node;
    Token *identToken = token;

    GetToken();
    if (token->symbol == symlparen) {
        ExpressionNode* parameter = ParseExpression();
        Expect(symrparen);
        node = Program->Functions->GetFunctionCall(identToken->GetText(), parameter);

        if (node == NOMEM) {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPFUNNDEF,
                identToken->GetText(),
                identToken->GetPos());

            delete parameter;
            node = new NumericValueNode();
        }
    } else if (token->symbol == symassign) {
        Variable* var = Program->Variables->CreateVariable(identToken->GetText());
        node = new AssignmentNode(new VariableNode(var), ParseExpression());
    } else {
        PutToken();
        Variable* var = Program->Variables->GetVariable(token->GetText());

        if (var == NOMEM) {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPVARNDEF,
                identToken->GetText(),
                identToken->GetPos());

            node = new NumericValueNode();
        } else {
            node = new VariableNode(var);
        }
    }

    return node;
}

ExpressionNode* Parser::ParseNumber()
{
    const char *a = token->GetText();
    Number *number = NOMEM;

    GetToken();
    if (token->symbol == symi) {
        Number *imag = Program->Input->Parse(a);
        number = new ComplexNumber(0.0, imag->GetRealValue());
        delete imag;
    } else {
        PutToken();
        number = Program->Input->Parse(a);
    }

    return new NumericValueNode (number);
}

// -----------------------------------------------------
// ------------------- Token logic ---------------------
// -----------------------------------------------------

void Parser::GetToken ()
{
    token = (token == NOMEM ? lexer->GetFirstToken() : token->GetNextToken());
}

void Parser::PutToken()
{
    token = token->GetLastToken();
}

bool Parser::Expect(Symbol symbol)
{
    GetToken();
    if (token->symbol != symbol) {
        syntaxError = token->GetPos();
        return false;
    } else {
        return true;
    }
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

    if (Program->Functions->IsSystemFunction(funcToken->GetText())) {
        errorNode = new ErrorNode(
            lexer->GetInput(),
            HELPFUNRDEF,
            funcToken->GetText(),
            funcToken->GetPos());

        return NOMEM;
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

    if (token->symbol == symdelimiter || token->symbol == symend) {
        PutToken();
        return new HelpStatement();
    } else if (token->symbol == symident) {
        return new HelpStatement(token->GetText());
    } else {
        return new HelpStatement(token->symbol);
    }
}

SyntaxNode* Parser::ParseDeleteStatement()
{
    GetToken();
    if (token->symbol == symvariable || token->symbol == symfunction) {
        return new DeleteStatement(token->symbol);
    } else if (token->symbol != symident) {
        syntaxError = token->GetPos();
        return NOMEM;
    }

    Token *identToken = token;

    GetToken();
    if (token->symbol == symlparen) {
        Expect(symident);
        Token *parameter = token;
        Expect(symrparen);
        return new DeleteStatement(identToken->GetText(), parameter->GetText());
    } else {
        PutToken();
        return new DeleteStatement(token->GetText());
    }
}

SyntaxNode* Parser::ParseListStatement()
{
    GetToken();
    if (token->symbol == symqident)
        return new ListStatement(token->GetText());
    else if (token->symbol == symend || symdelimiter) {
        PutToken();
        return new ListStatement();
    } else {
        syntaxError = token->GetPos();
        return NOMEM;
    }
}

SyntaxNode* Parser::ParseFileStatement()
{
    Token *statement = token;

    Expect(symqident);
    Token *identToken = token;

    if (statement->symbol == symload) {
        return new LoadStatement(identToken->GetText());
    } else if (statement->symbol == symsave) {
        return new SaveStatement(identToken->GetText());
    } else if (statement->symbol == symexecute) {
        return new ExecuteStatement(identToken->GetText());
    } else if (statement->symbol == symshow) {
        return new ShowStatement(identToken->GetText());
    } else {
        return new ErrorNode(
                   lexer->GetInput(),
                   HELPUERROR, EMPTYSTRING,
                   statement->GetPos());
    }
}

SyntaxNode* Parser::ParseNumeralStatement()
{
    Token *statement = token;
    unsigned int base;

    GetToken();
    switch (token->symbol) {
    case symend:
    case symdelimiter:
        PutToken();
        return (statement->symbol == syminput) ?
               (SyntaxNode*)new InputStatement() :
               (SyntaxNode*)new OutputStatement();
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

    if (base == 0 && token->symbol != symnumber) {
        syntaxError = token->GetPos();
        return NOMEM;
    }

    if (base == 0) {
        NumeralSystem *nsys = new DecimalSystem(0);
        Number *number = nsys->Parse(token->GetText());
        base = number->GetIntegerValue();
        delete number;
        delete nsys;

        if (base < 2 || base > 32) {
            errorNode = new ErrorNode(
                lexer->GetInput(),
                HELPPNUMERA,
                token->GetText(),
                token->GetPos());

            return NOMEM;
        }
    }

    return (statement->symbol == syminput) ?
           (SyntaxNode*)new InputStatement(base) :
           (SyntaxNode*)new OutputStatement(base);
}

SyntaxNode* Parser::ParseDigistStatement()
{
    GetToken();
    if (token->symbol == symdelimiter || token->symbol == symend) {
        PutToken();
        return new DigitsStatement();
    } else if (token->symbol != symnumber) {
        syntaxError = token->GetPos();
        return NOMEM;
    }

    NumeralSystem *nsys = new DecimalSystem(0);
    Number *number = nsys->Parse(token->GetText());
    int digits = number->GetIntegerValue();
    delete number;
    delete nsys;

    if (digits < 0 || digits > 15) {
        errorNode = new ErrorNode(
            lexer->GetInput(),
            HELPPDIGITS,
            token->GetText(),
            token->GetPos());

        return NOMEM;
    }

    return new DigitsStatement(digits);
}

SyntaxNode* Parser::ParsePromptStatement()
{
    GetToken();
    if (token->symbol == symqident) {
        return new PromptStatement(token->GetText());
    }

    PutToken();
    return NOMEM;
}

SyntaxNode* Parser::ParsePrefsStatement()
{
    GetToken();
    if (token->symbol == symload || token->symbol == symsave) {
        return new PrefsStatement(token->symbol);
    }

    PutToken();
    return new PrefsStatement();;
}

SyntaxNode* Parser::ParseDrawStatement()
{
    Token *statement = token;

    Expect(symident);
    Token *identToken = token;
    Expect(symlparen);
    Expect(symident);
    Token *paramToken = token;
    Expect(symrparen);

    if (statement->symbol == symplot) {
        return new PlotStatement(identToken->GetText(), paramToken->GetText());
    } else {
        return new DrawStatement(identToken->GetText(), paramToken->GetText());
    }
}
