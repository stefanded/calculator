#pragma once
#include "test_runner.h"
#include "Parse.h"
#include<iomanip>
string start_parse(string&& str_test)
{
    try {
        Parse p(str_test);
        stringstream str;
        str << setprecision(10) << p.result();
        return str.str();
    }
    catch (const logic_error & log)
    {
        return log.what();
    }

}

void test_input_error()
{
    cerr << start_parse("(") << endl;
    cerr << start_parse("") << endl;
    cerr << start_parse("()") << endl;;
    cerr << start_parse("+") << endl;;
    cerr << start_parse("5-") << endl;;
    cerr << start_parse("5-1-") << endl;;
    cerr << start_parse("5-1- ") << endl;;
    cerr << start_parse(" 5-1 ") << endl;;
    cerr << start_parse(" --512-1 ") << endl;;
    cerr << start_parse(" +++512-12-321 ") << endl;;
    cerr << start_parse(" +++512-12-321 ") << endl;;
    cerr << start_parse("1/0") << endl;;

}
void test_correct_result()
{
    ASSERT_EQUAL(start_parse("0"),"0");
    ASSERT_EQUAL(start_parse("-1"), "-1");
    ASSERT_EQUAL(start_parse("3+5"), "8");
    ASSERT_EQUAL(start_parse("(3+5)"), "8");
    ASSERT_EQUAL(start_parse("(3)+(5)"), "8");
    ASSERT_EQUAL(start_parse("((3)+(5))"), "8");
    ASSERT_EQUAL(start_parse("5*(3+5)"), "40");
    ASSERT_EQUAL(start_parse("(3+5)*5"), "40");
    ASSERT_EQUAL(start_parse("3-5*5"), "-22");
    ASSERT_EQUAL(start_parse("6+5-4*8*8"), "-245");
    ASSERT_EQUAL(start_parse("-1+(4*5)"), "19");
    ASSERT_EQUAL(start_parse("6815*(1*5)/5"), "6815");
    ASSERT_EQUAL(start_parse("1/5^4+5-6815/(1*5)"), "-1357.9984");

}
void all_test()
{
    test_input_error();
    test_correct_result();
}