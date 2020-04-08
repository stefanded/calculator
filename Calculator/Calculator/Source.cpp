#include"my_test.h"
#include <sstream>
#include <deque>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>


using namespace std;

int main()
{
    TestRunner tr;
    RUN_TEST(tr, all_test);
    string expression;
    cin >> expression;
    cout << expression<< "=" <<start_parse(move(expression)) << endl;
    return 0;
}