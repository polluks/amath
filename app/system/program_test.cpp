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

#ifdef WITHTEST
#include "clib.h"
#include "lib/charbuf.h"
#include "main/viewer.h"
#include "main/evaluator.h"
#include "system/program_test.h"
#include "system/base/io.h"
#include <stdio.h>

TestProgram::TestProgram()
    : Program()
{
    // Ignore type of locale fraction point.
    delete Input;
    Input = new DecimalSystem(Preferences->GetDigits(), '.');

    delete Output;
    Output = new DecimalSystem(Preferences->GetDigits(), '.');
}

TestProgram::~TestProgram()
{ }

void TestProgram::Run()
{
    RunTests();

    if (fail == 0) {
        printf("All tests passed (%i)." NEWLINE, pass);
    } else {
        printf("Something went wrong ..." NEWLINE);
        printf("Passed: %i, failed: %i" NEWLINE, pass, fail);
    }
}

void TestProgram::Initialize(int argc, char** argv)
{
    Preferences->Load();
}

void TestProgram::Exit()
{ }

void TestProgram::RunTests()
{
    pass = 0;
    fail = 0;

    RunTestset1();
    RunTestset2();
    RunTestset3();
    RunTestset4();
    RunTestset5();
}

void TestProgram::TestExpression(const char* expression, const char* result)
{
    PerformTest(expression, result, true);
}

void TestProgram::TestStatement(const char* statement, const char* result)
{
    PerformTest(statement, result, false);
}

void TestProgram::PerformTest(const char* input, const char* result, bool show)
{
    Evaluator *evaluator = new Evaluator(input);
    evaluator->Evaluate();
    char *res = evaluator->GetResult();

    CharBuffer *buf = new CharBuffer();
    buf->ClearAndCopy(res);
    buf->RemoveTrailing(NEWLINE);
    delete evaluator;

    if (buf->Is(result)) {
        pass++;
        printf("PASS: [%s]" NEWLINE, show ? result : input);
    } else {
        fail++;
        printf("FAIL: [%s] expected [%s] but got [%s]" NEWLINE, input, result, buf->GetString());
    }

    delete buf;
}

void TestProgram::RunTestset1()
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
    TestExpression("(1-1/3+1/5)/(1/2-1/4+1/6)", "(1-1/3+1/5)/(1/2-1/4+1/6) = 2.08");
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
}

void TestProgram::RunTestset2()
{
    Output->SetDigits(9);
    Output->SetDigits(14);
    //                                    12345678901234
    TestExpression("pi",          "pi = 3.1415926535898");
    TestExpression("pi*2",      "pi*2 = 6.2831853071796");
    TestExpression("pi/2",      "pi/2 = 1.5707963267949");
    TestExpression("cos(pi)",   "cos(pi) = -1");
    TestExpression("cos(-pi)",  "cos(-pi) = -1");
    TestExpression("cos(pi/2)", "cos(pi/2) = 0");
    TestExpression("sin(pi)",   "sin(pi) = 0");
    TestExpression("sin(-pi)",  "sin(-pi) = 0");
    TestExpression("sin(pi/2)", "sin(pi/2) = 1");
    TestExpression("tan(pi)",   "tan(pi) = 0");
    TestExpression("tan(-pi)",  "tan(-pi) = 0");
    TestExpression("tan(pi/2)", "tan(pi/2) = INF");
    //                                               12345678901234
    TestExpression("cos(0.5)",         "cos(0.5) = 0.87758256189037");
    TestExpression("sin(0.5)",         "sin(0.5) = 0.4794255386042");
    TestExpression("tan(0.5)",         "tan(0.5) = 0.54630248984379");
    TestExpression("cot(0.5)",         "cot(0.5) = 1.8304877217125");
    TestExpression("sec(0.5)",         "sec(0.5) = 1.1394939273245");
    TestExpression("csc(0.5)",         "csc(0.5) = 2.0858296429335");
    TestExpression("arccos(0.35)",   "acos(0.35) = 1.2132252231494");
    TestExpression("arcsin(0.35)",   "asin(0.35) = 0.35757110364551");
    TestExpression("arctan(0.35)",   "atan(0.35) = 0.33667481938673");
    TestExpression("arccot(0.41)",   "acot(0.41) = 1.1816990957396");
    TestExpression("arcsec(1.41)",   "asec(1.41) = 0.78240533832346");
    TestExpression("arccsc(1.41)",   "acsc(1.41) = 0.78839098847143");
    TestExpression("cosh(0.56)",     "cosh(0.56) = 1.1609407820725");
    TestExpression("sinh(0.56)",     "sinh(0.56) = 0.58973171822364");
    TestExpression("tanh(0.56)",     "tanh(0.56) = 0.5079774328979");
    TestExpression("coth(0.56)",     "coth(0.56) = 1.9685913885883");
    TestExpression("sech(0.56)",     "sech(0.56) = 0.86137037775075");
    TestExpression("csch(0.56)",     "csch(0.56) = 1.6956863080252");
    TestExpression("arccosh(1.44)", "acosh(1.44) = 0.90670360498911");
    TestExpression("arcsinh(0.45)", "asinh(0.45) = 0.43604966885174");
    TestExpression("arctanh(0.45)", "atanh(0.45) = 0.48470027859405");
    TestExpression("arccoth(1.51)", "acoth(1.51) = 0.79681365320373");
    TestExpression("arcsech(0.51)", "asech(0.51) = 1.2940148005294");
    TestExpression("arccsch(0.51)", "acsch(0.51) = 1.4259588665675");
}

void TestProgram::RunTestset3()
{
    Output->SetDigits(9);
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
    TestExpression("1/(12+7i)", "1/(12+7i) = 0.0621761658-0.03626943005i");
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
    TestExpression("2^2.2i", "2^2.2i = 0.04585644308+0.99894804i");
    TestExpression("3i^4.4", "3i^4.4 = 101.6930248+73.884307317i");
    TestExpression("(2+4i)^2.2i", "(2+4i)^2.2i = -0.08650199375-0.01340218842i");
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

void TestProgram::RunTestset4()
{
    Output->SetDigits(9);
    Output->SetDigits(14);

    TestExpression("cos(1+2i)",       "cos(1+2i) = 2.0327230070197-3.0518977991518i");
    TestExpression("sin(1+2i)",       "sin(1+2i) = 3.1657785132162+1.9596010414216i");
    TestExpression("tan(1+2i)",       "tan(1+2i) = 0.0338128260799+1.0147936161466i");
    TestExpression("cot(1+2i)",       "cot(1+2i) = 0.03279775553375-0.98432922645819i");
    TestExpression("sec(1+2i)",       "sec(1+2i) = 0.15117629826558+0.22697367539372i");
    TestExpression("csc(1+2i)",       "csc(1+2i) = 0.22837506559969-0.14136302161241i");
    TestExpression("arccos(1+2i)",   "acos(1+2i) = 1.1437177404024-1.528570919481i");
    TestExpression("arcsin(1+2i)",   "asin(1+2i) = 0.42707858639248+1.528570919481i");
    TestExpression("arctan(1+2i)",   "atan(1+2i) = 1.3389725222945+0.40235947810853i");
    TestExpression("arccot(1+2i)",   "acot(1+2i) = 0.2318238045004-0.40235947810853i");
    TestExpression("arcsec(1+2i)",   "asec(1+2i) = 1.3844782726871+0.39656823011233i");
    TestExpression("arccsc(1+2i)",   "acsc(1+2i) = 0.18631805410782-0.39656823011233i");
    TestExpression("cosh(1+2i)",     "cosh(1+2i) = -0.64214812471552+1.0686074213828i");
    TestExpression("sinh(1+2i)",     "sinh(1+2i) = -0.48905625904129+1.403119250622i");
    TestExpression("tanh(1+2i)",     "tanh(1+2i) = 1.1667362572409-0.24345820118573i");
    TestExpression("coth(1+2i)",     "coth(1+2i) = 0.82132979749385+0.17138361290919i");
    TestExpression("sech(1+2i)",     "sech(1+2i) = -0.41314934426694-0.68752743865548i");
    TestExpression("csch(1+2i)",     "csch(1+2i) = -0.22150093085051-0.6354937992539i");
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
}

void TestProgram::RunTestset5()
{
    TestStatement("f(x)=x*2+1", "");
    TestStatement("g(y)=y^2+y*1.5+2", "");
    TestStatement("h(x)=|x^3-2*x^2-16*x+6|", "");
    TestStatement("a=2;b=3;c=a+b;", "");
    TestStatement("vars", "a = 2\nb = 3\nc = 5");
    TestStatement("funcs", "f(x)=x*2+1\ng(y)=y^2+y*1.5+2\nh(x)=|x^3-2*x^2-16*x+6|");
    TestStatement("f(2.2)", "f(2.2) = 5.4");
    TestStatement("h(8.3)", "h(8.3) = 307.207");
    TestStatement("c+1.1", "c+1.1 = 6.1");
    TestStatement("d=1.1", "");
    TestStatement("eval d=d+1", "d=(d+1) = 2.1");
    TestStatement("eval d=d+1", "d=(d+1) = 3.1");
    TestStatement("eval d=d*2", "d=(d*2) = 6.2");
    TestStatement("vars", "a = 2\nb = 3\nc = 5\nd = 6.2");
}

#endif
