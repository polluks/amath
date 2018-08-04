/*-
 * Copyright (c) 2014-2018 Carsten Sonne Larsen <cs@innolan.net>
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

#if defined(WITHTEST)
#include "amath.h"
#include "amathc.h"
#include "program_test.h"
#include "console_stdc.h"
#include "lib/charbuf.h"
#include "lib/ntext.h"
#include "lib/ntextd.h"
#include "main/evaluator.h"

void WriteOut(const char *string);
void WriteOutInt(int value);

TestProgram::TestProgram(bool silent)
    : Program()
{
    this->silent = silent;
    pass = 0;
    fail = 0;

    // Ignore type of locale fraction point.
    delete Input;
    Input = new DecimalSystem(10, '.');

    delete Output;
    Output = new DecimalSystem(10, '.');
}

TestProgram::~TestProgram()
{
}

void TestProgram::Start()
{
    WriteOut("Testing " TXTVERSMSG NEWLINE);
    WriteOut(TXTCOMPMSG NEWLINE);
    WriteOut(NEWLINE);

    RunTests();

    if (fail == 0)
    {
        WriteOut("All tests passed(");
        WriteOutInt(pass);
        WriteOut(")" NEWLINE);
    }
    else
    {
        WriteOut("Passed: ");
        WriteOutInt(pass);
        WriteOut(", failed: ");
        WriteOutInt(fail);
        WriteOut(NEWLINE);
        status = 5; // Set exit status 5
    }
}

void TestProgram::Initialize(int argc, char** argv)
{
    Preferences->Load();
    Preferences->SetRefactorNames(true);
}

void TestProgram::Exit()
{
}

void TestProgram::RunTests()
{
    pass = 0;
    fail = 0;

    RunTestset01();
    RunTestset02();
    RunTestset03();
    RunTestset04();
    RunTestset06();
    RunTestset07();
    RunTestset05();
    RunTestset08();
    RunTestset09();
    RunTestset10();
    RunTestset11();
}

void TestProgram::TestExpression(const char* expression, const char* result)
{
    PerformTest(expression, result, true, true);
}

void TestProgram::TestStatement(const char* statement, const char* result)
{
    PerformTest(statement, result, false, true);
}

void TestProgram::TestExecution(const char* statement)
{
    PerformTest(statement, EMPTYSTRING, false, false);
}

void TestProgram::PerformTest(const char* input, const char* result, bool show, bool check)
{
    Evaluator* evaluator = new Evaluator(input);
    evaluator->Evaluate();
    char* res = evaluator->GetResult();

    CharBuffer* buf = new CharBuffer();
    buf->ClearAndCopy(res);
    buf->RemoveTrailing(NEWLINE);
    delete evaluator;

    if (buf->Is(result) || !check)
    {
        pass++;
        if (!silent)
        {
            WriteOut("PASS: [");
            WriteOut(show ? result : input);
            WriteOut("]" NEWLINE);
        }
    }
    else
    {
        fail++;
        if (!silent)
        {
            WriteOut("FAIL: [");
            WriteOut(input);
            WriteOut("] expected [");
            WriteOut(result);
            WriteOut("] but got [");
            WriteOut(buf->GetString());
            WriteOut("]" NEWLINE);
        }
    }

    delete buf;
}

void TestProgram::RunTestset01()
{
    Input->SetDigits(9);
    Output->SetDigits(9);

    TestExpression("-1", "-1 = -1");
    TestExpression("-(-1)", "1 = 1");
    TestExpression("2+3*4+5", "2+3*4+5 = 19");
    TestExpression("(2+3)*(4+5)", "(2+3)*(4+5) = 45");
    TestExpression("-(-2*3)+(-5*3)", "-(-2*3)+(-5)*3 = -9");
    TestExpression("4*5+2*3", "4*5+2*3 = 26");
    TestExpression("(4*5)+(2*3)", "4*5+2*3 = 26");
    TestExpression("67 + 75 + 150 + 200", "67+75+150+200 = 492");
    TestExpression("(1-1/3+1/5)/(1/2-1/4+1/6)", "(1-1/3+1/5)/(1/2-1/4+1/6) = 2.08");
    TestExpression("1.5439", "1.5439 = 1.5439");
    TestExpression("1.123456789", "1.12345679 = 1.12345679");
    TestExpression("-1.01234567890123456789", "-1.01234568 = -1.01234568");
    TestExpression("1.1+1.1", "1.1+1.1 = 2.2");
    TestExpression("2.2*2.20", "2.2*2.2 = 4.84");
    TestExpression("3.3/1.1", "3.3/1.1 = 3");
    TestExpression("3.3/1.05", "3.3/1.05 = 3.14285714");
    TestExpression("2^3", "2^3 = 8");
    TestExpression("2^1.5", "2^1.5 = 2.82842712");
    TestExpression("10^3", "10^3 = 1000");
    TestExpression("10.2^1.2", "10.2^1.2 = 16.230063");
    TestExpression("100^0.5", "100^0.5 = 10");
    TestExpression("100^-0.3", "100^(-0.3) = 0.251188643");
    TestExpression("283500/1050", "283500/1050 = 270");
    TestExpression("|1-2|", "|1-2| = 1");
    TestExpression("|1-|1-5||", "|1-|1-5|| = 3");
    TestExpression("sgn(2.3)", "sgn(2.3) = 1");
    TestExpression("sgn(-12.7)", "sgn(-12.7) = -1");
    TestExpression("sgn(0)", "sgn(0) = 0");
    TestExpression("round(1.5461)", "round(1.5461) = 2");
    TestExpression("round(-1.5461)", "round(-1.5461) = -2");
    TestExpression("ceil(43.5461)", "ceil(43.5461) = 44");
    TestExpression("ceil(-43.5461)", "ceil(-43.5461) = -43");
    TestExpression("floor(39.9531)", "floor(39.9531) = 39");
    TestExpression("floor(-39.9531)", "floor(-39.9531) = -40");
    TestExpression("trunc(23.827)", "trunc(23.827) = 23");
    TestExpression("trunc(-23.827)", "trunc(-23.827) = -23");
    TestExpression("log(1000)", "lg(1000) = 3");
    TestExpression("log(100)", "lg(100) = 2");
    TestExpression("log(23.2)", "lg(23.2) = 1.36548798");
    TestExpression("log2(512)", "lb(512) = 9");
    TestExpression("lb(128)", "lb(128) = 7");
    TestExpression("lb(15.32)", "lb(15.32) = 3.93734439");
    TestExpression("ln(103)", "ln(103) = 4.63472899");
    TestExpression("ln(e)", "ln(e) = 1");
    TestExpression("sqrt(100)", "sqrt(100) = 10");
    TestExpression("sqrt(52.23)", "sqrt(52.23) = 7.22703259");
    TestExpression("sqrt(-43.5)", "sqrt(-43.5) = 6.59545298i");
    TestExpression("cbrt(1000)", "cbrt(1000) = 10");
    TestExpression("cbrt(52.23)", "cbrt(52.23) = 3.73800612");
    TestExpression("cbrt(1/0)", "cbrt(1/0) = NaN");
    TestExpression("cbrt(tan(pi/2))", "cbrt(tan(pi/2)) = Inf");
    TestExpression("cbrt(1e-20)", "cbrt(1e-20) = 0.00000021544347");
    TestExpression("cbrt(-1e-20)", "cbrt(-1e-20) = 0.00000010772173+0.00000018657952i");
}

void TestProgram::RunTestset02()
{
    Input->SetDigits(9);
    Output->SetDigits(14);

    TestExpression("pi", "pi = 3.1415926535898");
    TestExpression("pi*2", "pi*2 = 6.2831853071796");
    TestExpression("pi/2", "pi/2 = 1.5707963267949");
    TestExpression("cos(pi)", "cos(pi) = -1");
    TestExpression("cos(-pi)", "cos(-pi) = -1");
    TestExpression("cos(pi/2)", "cos(pi/2) = 0");
    TestExpression("sin(pi)", "sin(pi) = 0");
    TestExpression("sin(-pi)", "sin(-pi) = 0");
    TestExpression("sin(pi/2)", "sin(pi/2) = 1");
    TestExpression("tan(pi)", "tan(pi) = 0");
    TestExpression("tan(-pi)", "tan(-pi) = 0");
    TestExpression("tan(pi/2)", "tan(pi/2) = Inf");
    TestExpression("tan(-pi/2)", "tan(-pi/2) = -Inf");
    TestExpression("sin(1/12*pi)", "sin(1/12*pi) = 0.25881904510252");
    TestExpression("sin(11/12*pi)", "sin(11/12*pi) = 0.25881904510252");
    TestExpression("sin(1/6*pi)", "sin(1/6*pi) = 0.5");
    TestExpression("sin(5/6*pi)", "sin(5/6*pi) = 0.5");
    TestExpression("sin(1/4*pi)", "sin(1/4*pi) = 0.70710678118655");
    TestExpression("sin(3/4*pi)", "sin(3/4*pi) = 0.70710678118655");
    TestExpression("sin(1/3*pi)", "sin(1/3*pi) = 0.86602540378444");
    TestExpression("sin(2/3*pi)", "sin(2/3*pi) = 0.86602540378444");
    TestExpression("sin(5/12*pi)", "sin(5/12*pi) = 0.96592582628907");
    TestExpression("sin(7/12*pi)", "sin(7/12*pi) = 0.96592582628907");
    TestExpression("cos(0.5)", "cos(0.5) = 0.87758256189037");
    TestExpression("sin(0.5)", "sin(0.5) = 0.4794255386042");
    TestExpression("tan(0.5)", "tan(0.5) = 0.54630248984379");
    TestExpression("cot(0.5)", "cot(0.5) = 1.8304877217125");
    TestExpression("sec(0.5)", "sec(0.5) = 1.1394939273245");
    TestExpression("csc(0.5)", "csc(0.5) = 2.0858296429335");
    TestExpression("crd(0.5)", "crd(0.5) = 0.49480791850905"); // Check
    TestExpression("exsec(0.5)", "exsec(0.5) = 0.13949392732455");
    TestExpression("excsc(0.5)", "excsc(0.5) = 1.0858296429335");
    TestExpression("arccos(0.35)", "acos(0.35) = 1.2132252231494");
    TestExpression("arcsin(0.35)", "asin(0.35) = 0.35757110364551");
    TestExpression("arctan(0.35)", "atan(0.35) = 0.33667481938673");
    TestExpression("arccot(0.41)", "acot(0.41) = 1.1816990957396");
    TestExpression("arcsec(1.41)", "asec(1.41) = 0.78240533832346");
    TestExpression("arccsc(1.41)", "acsc(1.41) = 0.78839098847143");
    TestExpression("arccrd(1.41)", "acrd(1.41) = 1.5648462916869"); // Check
    TestExpression("cosh(0.56)", "cosh(0.56) = 1.1609407820725");
    TestExpression("sinh(0.56)", "sinh(0.56) = 0.58973171822364");
    TestExpression("tanh(0.56)", "tanh(0.56) = 0.5079774328979");
    TestExpression("coth(0.56)", "coth(0.56) = 1.9685913885883");
    TestExpression("sech(0.56)", "sech(0.56) = 0.86137037775075");
    TestExpression("csch(0.56)", "csch(0.56) = 1.6956863080252");
    TestExpression("arccosh(1.44)", "acosh(1.44) = 0.90670360498911");
    TestExpression("arcsinh(0.45)", "asinh(0.45) = 0.43604966885174");
    TestExpression("arctanh(0.45)", "atanh(0.45) = 0.48470027859405");
    TestExpression("arccoth(1.51)", "acoth(1.51) = 0.79681365320373");
    TestExpression("arcsech(0.51)", "asech(0.51) = 1.2940148005294");
    TestExpression("arccsch(0.51)", "acsch(0.51) = 1.4259588665675");
    TestExpression("ver(0.51)", "ver(0.51) = 0.12725549235425");
    //TestExpression("vcs(0.51)", "vcs(0.51) = 0000");
    TestExpression("cvs(0.51)", "cvs(0.51) = 0.51182275311709");
    //TestExpression("cvc(0.51)", "cvc(0.51) = 0000");
    TestExpression("hv(0.51)", "hv(0.51) = 0.06362774617712");
    //TestExpression("hvc(0.51)", "hvc(0.51) = 0000");
    TestExpression("hcv(0.51)", "hcv(0.51) = 0.25591137655855");
    //TestExpression("hcc(0.51)", "hcc(0.51) = 0000");
    TestExpression("2+3-cos(3)", "2+3-cos(3) = 5.9899924966004");
    TestExpression("(sqrt(6)-sqrt(2))/4", "(sqrt(6)-sqrt(2))/4 = 0.25881904510252");
    TestExpression("(sqrt(6)+sqrt(2))/4", "(sqrt(6)+sqrt(2))/4 = 0.96592582628907");
    TestExpression("sqrt(2)/2", "sqrt(2)/2 = 0.70710678118655");
    TestExpression("sqrt(3)/2", "sqrt(3)/2 = 0.86602540378444");
}

void TestProgram::RunTestset03()
{
    Input->SetDigits(9);
    Output->SetDigits(11);

    TestExpression("-(1-2i)", "-(1-2i) = -1+2i");
    TestExpression("-2i-(-3i)", "-2i-(-3i) = 1i");
    TestExpression("1-2i+5.3i-2.1", "1-2i+(-2.1+5.3i) = -1.1+3.3i");
    TestExpression("1-2i+5.3i-2.1+1.3+1.3+1.3i+2/7i", "1-2i+5.3i-2.1+1.3+1.3+1.3i+2/7i = 1.5+4.3142857143i");
    TestExpression("2.3*(2i-1)", "2.3*(-1+2i) = -2.3+4.6i");
    TestExpression("2.3*(2i-1)*3*2i", "2.3*(-1+2i)*3*2i = -27.6-13.8i");
    TestExpression("2.3i*(-1.27)", "2.3i*(-1.27) = -2.921i");
    TestExpression("4.3/3.3i", "4.3/3.3i = -1.303030303i");
    TestExpression("4.3i/3.3", "4.3i/3.3 = 1.303030303i");
    TestExpression("1/(12+7i)", "1/(12+7i) = 0.062176165803-0.036269430052i");
    TestExpression("4.3i/(2.3i+1.1)", "4.3i/(1.1+2.3i) = 1.5215384615+0.72769230769i");
    TestExpression("(2+3.2i)*(4+7i)", "(2+3.2i)*(4+7i) = -14.4+26.8i");
    TestExpression("(2-3i)*(4-7i)", "(2-3i)*(4-7i) = -13-26i");
    TestExpression("(-2+3i)*(-4+7.2i)", "(-2+3i)*(-4+7.2i) = -13.6-26.4i");
    TestExpression("(2+3i)*(-4+7i)", "(2+3i)*(-4+7i) = -29+2i");
    TestExpression("(2.3i+3)/(2.2i+9)", "(3+2.3i)/(9+2.2i) = 0.37348555452+0.16425908667i");
    TestExpression("(2.3i-3)/(2.2i+9)", "(-3+2.3i)/(9+2.2i) = -0.2555917987+0.31803355079i");
    TestExpression("(-2.3i+3)/(2.2i+9)", "(3-2.3i)/(9+2.2i) = 0.2555917987-0.31803355079i");
    TestExpression("(-2.3i-3)/(2.2i+9)", "(-3-2.3i)/(9+2.2i) = -0.37348555452-0.16425908667i");
    TestExpression("(2.3i-3)/(2.2i-9)", "(-3+2.3i)/(-9+2.2i) = 0.37348555452-0.16425908667i");
    TestExpression("(-2.3i+3)/(-2.2i+9)", "(3-2.3i)/(9-2.2i) = 0.37348555452-0.16425908667i");
    TestExpression("(-2.3i-3)/(-2.2i-9)", "(-3-2.3i)/(-9-2.2i) = 0.37348555452+0.16425908667i");
    TestExpression("abs(2.1-3.7i)", "abs(2.1-3.7i) = 4.2544094772");
    TestExpression("abs(-2.1+3.7i)", "abs(-2.1+3.7i) = 4.2544094772");
    TestExpression("abs(-2.1-3.7i)", "abs(-2.1-3.7i) = 4.2544094772");
    TestExpression("sgn(2.1-3.7i)", "sgn(2.1-3.7i) = 1");
    TestExpression("sgn(-2.1+3.7i)", "sgn(-2.1+3.7i) = -1");
    TestExpression("sgn(-2.1-3.7i)", "sgn(-2.1-3.7i) = -1");
    TestExpression("round(1.5461+2.57i)", "round(1.5461+2.57i) = 2+3i");
    TestExpression("round(-1.5461-2.57i)", "round(-1.5461-2.57i) = -2-3i");
    TestExpression("ceil(43.5461+2.57i)", "ceil(43.5461+2.57i) = 44+3i");
    TestExpression("ceil(-43.5461-2.57i)", "ceil(-43.5461-2.57i) = -43-2i");
    TestExpression("floor(39.9531+2.57i)", "floor(39.9531+2.57i) = 39+2i");
    TestExpression("floor(-39.9531-2.57i)", "floor(-39.9531-2.57i) = -40-3i");
    TestExpression("trunc(23.827+2.57i)", "trunc(23.827+2.57i) = 23+2i");
    TestExpression("trunc(-23.827-2.57i)", "trunc(-23.827-2.57i) = -23-2i");
    TestExpression("2^2.2i", "2^2.2i = 0.045856443079+0.99894804i");
    TestExpression("3i^4.4", "3i^4.4 = 101.6930248+73.884307317i");
    TestExpression("(2+4i)^2.2i", "(2+4i)^2.2i = -0.086501993747-0.013402188424i");
    TestExpression("(2-4i)^(2.2i-2)", "(2-4i)^(-2+2.2i) = 0.40864788198-0.39910321822i");
    TestExpression("sqrt(20+50i)", "sqrt(20+50i) = 6.0766622447+4.1141006351i");
    TestExpression("sqrt(20-50i)", "sqrt(20-50i) = 6.0766622447-4.1141006351i");
    TestExpression("sqrt(-20-50i)", "sqrt(-20-50i) = 4.1141006351-6.0766622447i");
    TestExpression("cbrt(120+75i)", "cbrt(120+75i) = 5.1210176499+0.96470708458i");
    TestExpression("cbrt(120-75i)", "cbrt(120-75i) = 5.1210176499-0.96470708458i");
    TestExpression("ln(20+40i)", "ln(20+40i) = 3.8004512298+1.1071487178i");
    TestExpression("ln(20-40i)", "ln(20-40i) = 3.8004512298-1.1071487178i");
    TestExpression("log2(17+35i)", "lb(17+35i) = 5.282074745+1.6138599361i");
    TestExpression("log2(17-35i)", "lb(17-35i) = 5.282074745-1.6138599361i");
    TestExpression("log(20+50i)", "lg(20+50i) = 1.7311989989+0.51693635701i");
    TestExpression("log(20-50i)", "lg(20-50i) = 1.7311989989-0.51693635701i");
}

void TestProgram::RunTestset04()
{
    Input->SetDigits(9);
    Output->SetDigits(14);

    TestExpression("ln(-15)", "ln(-15) = 2.7080502011022+3.1415926535898i");
    TestExpression("log2(-15)", "lb(-15) = 3.9068905956085+4.5323601418272i"); // Check
    TestExpression("log10(-15)", "lg(-15) = 1.1760912590557+1.3643763538418i");
    TestExpression("cos(1+2i)", "cos(1+2i) = 2.0327230070197-3.0518977991518i");
    TestExpression("sin(1+2i)", "sin(1+2i) = 3.1657785132162+1.9596010414216i");
    TestExpression("tan(1+2i)", "tan(1+2i) = 0.0338128260799+1.0147936161466i");
    TestExpression("cot(1+2i)", "cot(1+2i) = 0.03279775553375-0.98432922645819i");
    TestExpression("sec(1+2i)", "sec(1+2i) = 0.15117629826558+0.22697367539372i");
    TestExpression("csc(1+2i)", "csc(1+2i) = 0.22837506559969-0.14136302161241i");
    TestExpression("arccos(1+2i)", "acos(1+2i) = 1.1437177404024-1.528570919481i");
    TestExpression("arcsin(1+2i)", "asin(1+2i) = 0.42707858639248+1.528570919481i");
    TestExpression("arctan(1+2i)", "atan(1+2i) = 1.3389725222945+0.40235947810853i");
    TestExpression("arccot(1+2i)", "acot(1+2i) = 0.2318238045004-0.40235947810853i");
    TestExpression("arcsec(1+2i)", "asec(1+2i) = 1.3844782726871+0.39656823011233i");
    TestExpression("arccsc(1+2i)", "acsc(1+2i) = 0.18631805410782-0.39656823011233i");
    TestExpression("cosh(1+2i)", "cosh(1+2i) = -0.64214812471552+1.0686074213828i");
    TestExpression("sinh(1+2i)", "sinh(1+2i) = -0.48905625904129+1.403119250622i");
    TestExpression("tanh(1+2i)", "tanh(1+2i) = 1.1667362572409-0.24345820118573i");
    TestExpression("coth(1+2i)", "coth(1+2i) = 0.82132979749385+0.17138361290919i");
    TestExpression("sech(1+2i)", "sech(1+2i) = -0.41314934426694-0.68752743865548i");
    TestExpression("csch(1+2i)", "csch(1+2i) = -0.22150093085051-0.6354937992539i");
    TestExpression("arccosh(1+2i)", "acosh(1+2i) = 1.528570919481+1.1437177404024i");
    TestExpression("arcsinh(1+2i)", "asinh(1+2i) = 1.4693517443682+1.0634400235778i");
    TestExpression("arctanh(1+2i)", "atanh(1+2i) = 0.17328679513999+1.1780972450962i");
    TestExpression("arccoth(1+2i)", "acoth(1+2i) = 0.17328679513999-0.39269908169872i");
    TestExpression("arcsech(1+2i)", "asech(1+2i) = 0.39656823011233-1.3844782726871i");
    TestExpression("arccsch(1+2i)", "acsch(1+2i) = 0.21561241855583-0.40158639166781i");
    TestExpression("cos(-1.43-3.23i)", "cos(-1.43-3.23i) = 1.7765430126591-12.495168795382i");
    TestExpression("sin(-1.43-3.23i)", "sin(-1.43-3.23i) = -12.534334855328-1.7709918453308i");
    TestExpression("tan(-1.43-3.23i)", "tan(-1.43-3.23i) = -0.00087228966374-1.003010475525i");
    TestExpression("cot(-1.43-3.23i)", "cot(-1.43-3.23i) = -0.00086706061634+0.99699780617804i");
    TestExpression("sec(-1.43-3.23i)", "sec(-1.43-3.23i) = 0.01115321045915+0.07844518613085i");
    TestExpression("csc(-1.43-3.23i)", "csc(-1.43-3.23i) = -0.07821934898722+0.01105170962818i");
    TestExpression("arccos(-1.43-3.23i)", "acos(-1.43-3.23i) = 1.9733334521871+1.9686290896497i");
    TestExpression("arcsin(-1.43-3.23i)", "asin(-1.43-3.23i) = -0.40253712539219-1.9686290896497i");
    TestExpression("arctan(-1.43-3.23i)", "atan(-1.43-3.23i) = -1.4486945189384-0.26104191221162i");
    TestExpression("arccot(-1.43-3.23i)", "acot(-1.43-3.23i) = -0.1221018078565+0.26104191221162i");
    TestExpression("arcsec(-1.43-3.23i)", "asec(-1.43-3.23i) = 1.6819282086005-0.25760781134815i");
    TestExpression("arccsc(-1.43-3.23i)", "acsc(-1.43-3.23i) = -0.11113188180565+0.25760781134815i");
    TestExpression("cosh(-1.43-3.23i)", "cosh(-1.43-3.23i) = -2.2003770462293-0.17390877229544i");
    TestExpression("sinh(-1.43-3.23i)", "sinh(-1.43-3.23i) = 1.9620027174115+0.19503789026432i");
    TestExpression("tanh(-1.43-3.23i)", "tanh(-1.43-3.23i) = -0.89309335200203-0.01805196156745i");
    TestExpression("coth(-1.43-3.23i)", "coth(-1.43-3.23i) = -1.1192464990635+0.02262316110662i");
    TestExpression("sech(-1.43-3.23i)", "sech(-1.43-3.23i) = -0.4516462791984+0.03569626853807i");
    TestExpression("csch(-1.43-3.23i)", "csch(-1.43-3.23i) = 0.50469595437383-0.05017059012838i");
    TestExpression("arccosh(-1.43-3.23i)", "acosh(-1.43-3.23i) = -1.9686290896497+1.9733334521871i");
    TestExpression("arcsinh(-1.43-3.23i)", "asinh(-1.43-3.23i) = -1.9417349567173-1.1385610418228i");
    TestExpression("arctanh(-1.43-3.23i)", "atanh(-1.43-3.23i) = -0.10773740084981-1.3144779329543i");
    TestExpression("arccoth(-1.43-3.23i)", "acoth(-1.43-3.23i) = -0.10773740084981+0.25631839384056i");
    TestExpression("arcsech(-1.43-3.23i)", "asech(-1.43-3.23i) = -0.25760781134815-1.6819282086005i");
    TestExpression("arccsch(-1.43-3.23i)", "acsch(-1.43-3.23i) = -0.1183123934959+0.2599771870207i");
    TestExpression("2+3.2i*cos(-1i)+5/7", "2+3.2i*cos(-1i)+5/7 = 2.7142857142857+4.9378580314088i");
}

void TestProgram::RunTestset05()
{
    TestExecution("delete funtions");
    TestStatement("2", "2 = 2");
    TestStatement("ins+2", "ins+2 = 4");
    TestStatement("f(x)=x*2+1", EMPTYSTRING);
    TestStatement("g(y)=y^2+y*1.5+2", EMPTYSTRING);
    TestStatement("h(x)=x^3-2*x^2-16*x+6", EMPTYSTRING);
    TestStatement("a=2;b=3;c=a+b;", EMPTYSTRING);
    TestStatement("vars", "a = 2" NEWLINE "b = 3" NEWLINE "c = 5");
    TestStatement("funcs", "f(x)=x*2+1" NEWLINE "g(y)=y^2+y*1.5+2" NEWLINE "h(x)=x^3-2*x^2-16*x+6");
    TestStatement("f(2.2)", "f(2.2) = 5.4");
    TestStatement("h(8.3)", "h(8.3) = 307.207");
    TestStatement("c+1.1", "c+1.1 = 6.1");
    TestStatement("d=1.1", EMPTYSTRING);
    TestStatement("eval d=d+1", "d=(d+1) = 2.1");
    TestStatement("eval d=d+1", "d=(d+1) = 3.1");
    TestStatement("eval d=d*2", "d=(d*2) = 6.2");
    TestStatement("vars", "a = 2" NEWLINE "b = 3" NEWLINE "c = 5" NEWLINE "d = 6.2");
    TestExecution("delete funtions");
    TestExecution("delete variable");
}

void TestProgram::RunTestset06()
{
    TestExecution("help");
    TestExecution("help functions");
    TestExecution("help trigon");
    TestExecution("help hyper");
    TestExecution("help complex");
    TestExecution("help statements");
    TestExecution("help operators");
    TestExecution("help sin");
    TestExecution("help help");
    TestExecution("input hex");
    TestExecution("input dec");
    TestExecution("input oct");
    TestExecution("input bin");
    TestExecution("input 25");
    TestExecution("output hex");
    TestExecution("output dec");
    TestExecution("output oct");
    TestExecution("output bin");
    TestExecution("output 25");
    TestExecution("digits 1");
    TestExecution("digits 5");
    TestExecution("digits 9");
    TestExecution("digits 15");
    TestExecution("digits 33");
    TestExecution("input");
    TestExecution("output");
    TestExecution("digits");
    TestExecution("eval 7+7");
    TestExecution("delete x");
    TestExecution("delete pi");
    TestExecution("eval pi/2");
    TestExecution("list");
    TestExecution("memory");
    TestExecution("variables");
}

void TestProgram::RunTestset07()
{
    delete Input;
    Input = new DecimalSystem(4, ',');
    delete Output;
    Output = new DecimalSystem(14, ',');

    TestExpression("cos(0,5)", "cos(0,5) = 0,87758256189037");
    TestExpression("sin(0,5)", "sin(0,5) = 0,4794255386042");

    delete Output;
    Output = new DecimalSystem(14, '.');
    TestExpression("cos(0,5)", "cos(0,5) = 0.87758256189037");
    TestExpression("sin(0,5)", "sin(0,5) = 0.4794255386042");

    delete Input;
    Input = new DecimalSystem(14, '.');
    TestExpression("cos(0.5)", "cos(0.5) = 0.87758256189037");
    TestExpression("sin(0.5)", "sin(0.5) = 0.4794255386042");
}

void TestProgram::RunTestset08()
{
    Input->SetDigits(9);
    Output->SetDigits(9);
    
    TestExpression("1/0", "1/0 = NaN");
    TestExpression("1.0/0", "1/0 = NaN");
    TestExpression("1i/0", "1i/0 = NaN");
    TestExpression("1.0i/0", "1i/0 = NaN");
    TestExpression("1/0.0", "1/0 = NaN");
    TestExpression("1.0/0.0", "1/0 = NaN");
    TestExpression("1i/0.0", "1i/0 = NaN");
    TestExpression("1.0i/0.0", "1i/0 = NaN");
    TestExpression("1/0i", "1/0 = NaN");
    TestExpression("1.0/0i", "1/0 = NaN");
    TestExpression("1i/0i", "1i/0 = NaN");
    TestExpression("1.0i/0i", "1i/0 = NaN");
    TestExpression("1/0.0i", "1/0 = NaN");
    TestExpression("1.0/0.0i", "1/0 = NaN");
    TestExpression("1i/0.0i", "1i/0 = NaN");
    TestExpression("1.0i/0.0i", "1i/0 = NaN");
    TestExpression("lb(0)*10", "lb(0)*10 = NaN");
    TestExpression("ln(0)*10", "ln(0)*10 = NaN");
    TestExpression("lg(0)*10", "lg(0)*10 = NaN");
    TestExpression("1+1", "1+1 = 2");
    TestExpression("1.1+1", "1.1+1 = 2.1");
    TestExpression("1i+1", "1+1i = 1+1i");
    TestExpression("1.1i+1", "1+1.1i = 1+1.1i");
    TestExpression("1+1.0", "1+1 = 2");
    TestExpression("1.1+1.0", "1.1+1 = 2.1");
    TestExpression("1i+1.0", "1+1i = 1+1i");
    TestExpression("1.1i+1.0", "1+1.1i = 1+1.1i");
    TestExpression("1+1i", "1+1i = 1+1i");
    TestExpression("1.1+1i", "1.1+1i = 1.1+1i");
    TestExpression("1i+1i", "1i+1i = 2i");
    TestExpression("1.1i+1i", "1.1i+1i = 2.1i");
    TestExpression("1+1.0i", "1+1i = 1+1i");
    TestExpression("1.1+1.0i", "1.1+1i = 1.1+1i");
    TestExpression("1i+1.0i", "1i+1i = 2i");
    TestExpression("1.1i+1.0i", "1.1i+1i = 2.1i");
    TestExpression("1i+1i", "1i+1i = 2i");
    TestExpression("1.0i+1i", "1i+1i = 2i");
    TestExpression("1i+1.0i", "1i+1i = 2i");
    TestExpression("1.0i+1.0i", "1i+1i = 2i");
    TestExpression("1-1", "1-1 = 0");
    TestExpression("1.1-1", "1.1-1 = 0.1");
    TestExpression("1i-1", "-1+1i = -1+1i");
    TestExpression("1.1i-1", "-1+1.1i = -1+1.1i");
    TestExpression("1-1.0", "1-1 = 0");
    TestExpression("1.1-1.0", "1.1-1 = 0.1");
    TestExpression("1i-1.0", "-1+1i = -1+1i");
    TestExpression("1.1i-1.0", "-1+1.1i = -1+1.1i");
    TestExpression("1-1i", "1-1i = 1-1i");
    TestExpression("1.1-1i", "1.1-1i = 1.1-1i");
    TestExpression("1i-1i", "1i-1i = 0");
    TestExpression("1.1i-1i", "1.1i-1i = 0.1i");
    TestExpression("1-1.0i", "1-1i = 1-1i");
    TestExpression("1.1-1.0i", "1.1-1i = 1.1-1i");
    TestExpression("1i-1.0i", "1i-1i = 0");
    TestExpression("1.1i-1.0i", "1.1i-1i = 0.1i");
    TestExpression("1i-1i", "1i-1i = 0");
    TestExpression("1.0i-1i", "1i-1i = 0");
    TestExpression("1i-1.0i", "1i-1i = 0");
    TestExpression("1.0i-1.0i", "1i-1i = 0");

// Mul, Div ...
}

void TestProgram::RunTestset09()
{
    Input->SetDigits(9);
    Output->SetDigits(9);

    TestExpression("lb(0)", "lb(0) = NaN");
    TestExpression("ln(0)", "ln(0) = NaN");
    TestExpression("lg(0)", "lg(0) = NaN");
    TestExpression("lb(0i)", "lb(0) = NaN");
    TestExpression("ln(0i)", "ln(0) = NaN");
    TestExpression("lg(0i)", "lg(0) = NaN");
    TestExpression("tan(0)", "tan(0) = 0");
    TestExpression("tan(pi)", "tan(pi) = 0");
    TestExpression("cot(0)", "cot(0) = NaN");
    TestExpression("cot(pi)", "cot(pi) = NaN");
    TestExpression("sec(0)", "sec(0) = 1");
    TestExpression("sec(pi)", "sec(pi) = 1");
    TestExpression("csc(0)", "csc(0) = NaN");
    TestExpression("csc(pi)", "csc(pi) = NaN");
    TestExpression("exsec(0)", "exsec(0) = 0");
    TestExpression("excsc(0)", "excsc(0) = Inf");
    TestExpression("arcsin(0)", "asin(0) = 0");
    TestExpression("arctan(0)", "atan(0) = 0");
    TestExpression("arcsec(0)", "asec(0) = NaN");
    TestExpression("arccsc(0)", "acsc(0) = NaN");
    TestExpression("aexsec(0)", "aexsec(0) = 0");
    TestExpression("cosh(0)", "cosh(0) = 1");
    TestExpression("sinh(0)", "sinh(0) = 0");
    TestExpression("tanh(0)", "tanh(0) = 0");
    TestExpression("coth(0)", "coth(0) = NaN");
    TestExpression("sech(0)", "sech(0) = 1");
    TestExpression("csch(0)", "csch(0) = NaN");
    TestExpression("arcsinh(0)", "asinh(0) = 0");
    TestExpression("arctanh(0)", "atanh(0) = 0");
    TestExpression("arccoth(0)", "acoth(0) = NaN");
    TestExpression("arcsech(0)", "asech(0) = NaN");
    TestExpression("arccsch(0)", "acsch(0) = NaN");
}

void TestProgram::RunTestset10()
{
    Input->SetDigits(9);
    Output->SetDigits(9);

    TestExpression("-1e-309", "-Inf = -Inf");
    TestExpression("-1e-308", "-Inf = -Inf");
    TestExpression("1e-309", "Inf = Inf");
    TestExpression("1e-308", "Inf = Inf");
    TestExpression("1e-307", "1e-307 = 1e-307");
    TestExpression("1e-300", "1e-300 = 1e-300");
    TestExpression("1e-267", "1e-267 = 1e-267");
    TestExpression("1e-165", "1e-165 = 1e-165");
    TestExpression("1e-150", "1e-150 = 1e-150");
    TestExpression("1e-75", "1e-75 = 1e-75");
    TestExpression("1e-40", "1e-40 = 1e-40");
    TestExpression("1e-20", "1e-20 = 1e-20");
    TestExpression("1e-19", "1e-19 = 1e-19");
    TestExpression("1e-18", "1e-18 = 1e-18");
    TestExpression("1e-17", "1e-17 = 1e-17");
    TestExpression("1e-16", "1e-16 = 1e-16");
    TestExpression("1e-15", "1e-15 = 1e-15");
    TestExpression("1e-14", "1e-14 = 1e-14");
    TestExpression("1e-13", "1e-13 = 1e-13");
    TestExpression("1e-12", "1e-12 = 1e-12");
    TestExpression("1e-11", "1e-11 = 1e-11");
    TestExpression("1e-10", "1e-10 = 1e-10");
    TestExpression("1e-9", "1e-9 = 1e-9");
    TestExpression("1e-8", "0.00000001 = 0.00000001");
    TestExpression("1e-7", "0.0000001 = 0.0000001");
    TestExpression("1e-6", "0.000001 = 0.000001");
    TestExpression("1e-5", "0.00001 = 0.00001");
    TestExpression("1e-4", "0.0001 = 0.0001");
    TestExpression("1e-3", "0.001 = 0.001");
    TestExpression("1e-2", "0.01 = 0.01");
    TestExpression("1e-1", "0.1 = 0.1");
    TestExpression("1e-0", "1 = 1");
    TestExpression("1e+0", "1 = 1");
    TestExpression("1e+1", "10 = 10");
    TestExpression("1e+2", "100 = 100");
    TestExpression("1e+3", "1000 = 1000");
    TestExpression("1e+4", "10000 = 10000");
    TestExpression("1e+5", "100000 = 100000");
    TestExpression("1e+6", "1000000 = 1000000");
    TestExpression("1e+7", "10000000 = 10000000");
    TestExpression("1e+8", "100000000 = 100000000");
    TestExpression("1e+9", "1e+9 = 1e+9");
    TestExpression("1e+10", "1e+10 = 1e+10");
    TestExpression("1e+11", "1e+11 = 1e+11");
    TestExpression("1e+12", "1e+12 = 1e+12");
    TestExpression("1e+13", "1e+13 = 1e+13");
    TestExpression("1e+14", "1e+14 = 1e+14");
    TestExpression("1e+15", "1e+15 = 1e+15");
    TestExpression("1e+16", "1e+16 = 1e+16");
    TestExpression("1e+17", "1e+17 = 1e+17");
    TestExpression("1e+18", "1e+18 = 1e+18");
    TestExpression("1e+19", "1e+19 = 1e+19");
    TestExpression("1e+20", "1e+20 = 1e+20");
    TestExpression("1e+40", "1e+40 = 1e+40");
    TestExpression("1e+75", "1e+75 = 1e+75");
    TestExpression("1e+150", "1e+150 = 1e+150");
    TestExpression("1e+165", "1e+165 = 1e+165");
    TestExpression("1e+267", "1e+267 = 1e+267");
    TestExpression("1e+300", "1e+300 = 1e+300");
    TestExpression("1e+306", "1e+306 = 1e+306");
    TestExpression("1e+307", "1e+307 = 1e+307");
    TestExpression("1e+308", "1e+308 = 1e+308");
    TestExpression("1e+309", "Inf = Inf");
    TestExpression("1e+310", "Inf = Inf");
    TestExpression("-1e+308", "-1e+308 = -1e+308");
    TestExpression("-1e+309", "-Inf = -Inf");
    TestExpression("-1e+310", "-Inf = -Inf");
    TestExpression("1.7e-20", "1.7e-20 = 1.7e-20");
    TestExpression("1.7e-19", "1.7e-19 = 1.7e-19");
    TestExpression("1.7e-18", "1.7e-18 = 1.7e-18");
    TestExpression("1.7e-17", "1.7e-17 = 1.7e-17");
    TestExpression("1.7e-16", "1.7e-16 = 1.7e-16");
    TestExpression("1.7e-15", "1.7e-15 = 1.7e-15");
    TestExpression("1.7e-14", "1.7e-14 = 1.7e-14");
    TestExpression("1.7e-13", "1.7e-13 = 1.7e-13");
    TestExpression("1.7e-12", "1.7e-12 = 1.7e-12");
    TestExpression("1.7e-11", "1.7e-11 = 1.7e-11");
    TestExpression("1.7e-10", "1.7e-10 = 1.7e-10");
    TestExpression("1.7e-9", "1.7e-9 = 1.7e-9");
    TestExpression("1.7e-8", "0.000000017 = 0.000000017");
    TestExpression("1.7e-7", "0.00000017 = 0.00000017");
    TestExpression("1.7e-6", "0.0000017 = 0.0000017");
    TestExpression("1.7e-5", "0.000017 = 0.000017");
    TestExpression("1.7e-4", "0.00017 = 0.00017");
    TestExpression("1.7e-3", "0.0017 = 0.0017");
    TestExpression("1.7e-2", "0.017 = 0.017");
    TestExpression("1.7e-1", "0.17 = 0.17");
    TestExpression("1.7e-0", "1.7 = 1.7");
    TestExpression("1.7e+0", "1.7 = 1.7");
    TestExpression("1.7e+1", "17 = 17");
    TestExpression("1.7e+2", "170 = 170");
    TestExpression("1.7e+3", "1700 = 1700");
    TestExpression("1.7e+4", "17000 = 17000");
    TestExpression("1.7e+5", "170000 = 170000");
    TestExpression("1.7e+6", "1700000 = 1700000");
    TestExpression("1.7e+7", "17000000 = 17000000");
    TestExpression("1.7e+8", "170000000 = 170000000");
    TestExpression("1.7e+9", "1.7e+9 = 1.7e+9");
    TestExpression("1.7e+10", "1.7e+10 = 1.7e+10");
    TestExpression("1.7e+11", "1.7e+11 = 1.7e+11");
    TestExpression("1.7e+12", "1.7e+12 = 1.7e+12");
    TestExpression("1.7e+13", "1.7e+13 = 1.7e+13");
    TestExpression("1.7e+14", "1.7e+14 = 1.7e+14");
    TestExpression("1.7e+15", "1.7e+15 = 1.7e+15");
    TestExpression("1.7e+16", "1.7e+16 = 1.7e+16");
    TestExpression("1.7e+17", "1.7e+17 = 1.7e+17");
    TestExpression("1.7e+18", "1.7e+18 = 1.7e+18");
    TestExpression("1.7e+19", "1.7e+19 = 1.7e+19");
    TestExpression("1.7e+20", "1.7e+20 = 1.7e+20");
    TestExpression("-1.7e-20", "-1.7e-20 = -1.7e-20");
    TestExpression("-1.7e-19", "-1.7e-19 = -1.7e-19");
    TestExpression("-1.7e-18", "-1.7e-18 = -1.7e-18");
    TestExpression("-1.7e-17", "-1.7e-17 = -1.7e-17");
    TestExpression("-1.7e-16", "-1.7e-16 = -1.7e-16");
    TestExpression("-1.7e-15", "-1.7e-15 = -1.7e-15");
    TestExpression("-1.7e-14", "-1.7e-14 = -1.7e-14");
    TestExpression("-1.7e-13", "-1.7e-13 = -1.7e-13");
    TestExpression("-1.7e-12", "-1.7e-12 = -1.7e-12");
    TestExpression("-1.7e-11", "-1.7e-11 = -1.7e-11");
    TestExpression("-1.7e-10", "-1.7e-10 = -1.7e-10");
    TestExpression("-1.7e-9", "-1.7e-9 = -1.7e-9");
    TestExpression("-1.7e-8", "-0.000000017 = -0.000000017");
    TestExpression("-1.7e-7", "-0.00000017 = -0.00000017");
    TestExpression("-1.7e-6", "-0.0000017 = -0.0000017");
    TestExpression("-1.7e-5", "-0.000017 = -0.000017");
    TestExpression("-1.7e-4", "-0.00017 = -0.00017");
    TestExpression("-1.7e-3", "-0.0017 = -0.0017");
    TestExpression("-1.7e-2", "-0.017 = -0.017");
    TestExpression("-1.7e-1", "-0.17 = -0.17");
    TestExpression("-1.7e-0", "-1.7 = -1.7");
    TestExpression("-1.7e+0", "-1.7 = -1.7");
    TestExpression("-1.7e+1", "-17 = -17");
    TestExpression("-1.7e+2", "-170 = -170");
    TestExpression("-1.7e+3", "-1700 = -1700");
    TestExpression("-1.7e+4", "-17000 = -17000");
    TestExpression("-1.7e+5", "-170000 = -170000");
    TestExpression("-1.7e+6", "-1700000 = -1700000");
    TestExpression("-1.7e+7", "-17000000 = -17000000");
    TestExpression("-1.7e+8", "-170000000 = -170000000");
    TestExpression("-1.7e+9", "-1.7e+9 = -1.7e+9");
    TestExpression("-1.7e+10", "-1.7e+10 = -1.7e+10");
    TestExpression("-1.7e+11", "-1.7e+11 = -1.7e+11");
    TestExpression("-1.7e+12", "-1.7e+12 = -1.7e+12");
    TestExpression("-1.7e+13", "-1.7e+13 = -1.7e+13");
    TestExpression("-1.7e+14", "-1.7e+14 = -1.7e+14");
    TestExpression("-1.7e+15", "-1.7e+15 = -1.7e+15");
    TestExpression("-1.7e+16", "-1.7e+16 = -1.7e+16");
    TestExpression("-1.7e+17", "-1.7e+17 = -1.7e+17");
    TestExpression("-1.7e+18", "-1.7e+18 = -1.7e+18");
    TestExpression("-1.7e+19", "-1.7e+19 = -1.7e+19");
    TestExpression("-1.7e+20", "-1.7e+20 = -1.7e+20");
}

void TestProgram::RunTestset11()
{
    delete Input;
    Input = new DecimalSystem(10, '.');

    delete Output;
    Output = new PositionalNumeralSystem(16, 13, '.');

    TestExpression("5", "5 = 5");
    TestExpression("10", "10 = A");
    TestExpression("100", "100 = 64");
    TestExpression("2000", "2000 = 7D0");
    TestExpression("50000", "50000 = C350");
    TestExpression("121254544", "121254544 = 7.3A329e+6");
    TestExpression("-5", "-5 = -5");
    TestExpression("-10", "-10 = -A");
    TestExpression("-100", "-100 = -64");
    TestExpression("-2000", "-2000 = -7D0");
    TestExpression("-50000", "-50000 = -C350");
    TestExpression("-121254544", "-121254544 = -7.3A329e+6");
    TestExpression("1.5", "1.5 = 1.8");
    TestExpression("3.546", "3.546 = 3.8BC6A7EF9DB2");
    TestExpression("-77777.843", "-77777.843 = -12FD1.D7CED917");

    delete Output;
    Output = new PositionalNumeralSystem(2, 20, '.');
    TestExpression("9", "9 = 1001");
    TestExpression("999", "999 = 1111100111");
    TestExpression("999997", "999997 = 11110100001000111101");
    TestExpression("-9", "-9 = -1001");
    TestExpression("-999", "-999 = -1111100111");
    TestExpression("-999997", "-999997 = -11110100001000111101");
    TestExpression("0.5", "0.5 = 0.1");
    TestExpression("9.45", "9.45 = 1001.0111001100110011");
    TestExpression("-0.5", "-0.5 = -0.1");
    TestExpression("-9.45", "-9.45 = -1001.0111001100110011");
}

#endif
