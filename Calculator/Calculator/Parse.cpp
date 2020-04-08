#include "Parse.h"

using namespace std;
ExpressionPtr Parse::new_number(ExpressionPtr left, char op, ExpressionPtr right) const

{
    if (op == '+')
    {
        return formation_binary_expr<SumExpr>(move(left), move(right));
    }
    else if (op == '-')
    {
        return formation_binary_expr<SubExpr>(move(left), move(right));
    }
    else if (op == '*') {
        return formation_binary_expr<ProductExpr>(move(left), move(right));
    }
    else if (op == '/')
    {
        return formation_binary_expr<DivExpr>(move(left), move(right));

    }
    else if (op == '^')
    {
        return formation_binary_expr<PowExpr>(move(left), move(right));

    }
    throw logic_error("there is no such sign");

}
template<class T>
T& Parse::correct_top(stack<T>& cont) const

{
    if (cont.empty())
    {
        throw logic_error("erroe syntax: " + str);
    }
    return cont.top();
}

template<class T>
void Parse::correct_pop(stack<T>& cont)
{
    if (cont.empty())
    {
        throw logic_error("erroe syntax: " + str);
    }
    cont.pop();
}
void Parse::erase_and_push()
{
    if (correct_top(opeartion) != ')' && correct_top(opeartion) != '(') {
        ExpressionPtr left = move(correct_top(number));
        correct_pop(number);
        ExpressionPtr temp = new_number(move(correct_top(number)), correct_top(opeartion), move(left));
        correct_top(number) = move(temp);
    }
    correct_pop(opeartion);
}

size_t Parse::priority_op(char op) const

{
    switch (op) {
    case '+':return 1;
    case '-':return 1;  
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
    }
    return 0;
    //
}

Parse::Parse(const string& str):str(str)
{
    if (str.empty())
    {

        throw logic_error("string can not be empty");
    }
    if ((str[0] == '+' || str[0] == '-'))
    {
        number.push(Value(0));
    }
}

void Parse::get_string(const string& str)
{
    //*this = Parse(str);
}

double Parse::result()
{
    string str_number;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
            str_number += str[i];
        }
        else if (str[i] == ')')
        {
            if (!str_number.empty())
            {
                number.push(Value(stoi((str_number))));
                str_number.clear();
            }
            while (correct_top(opeartion) != '(')
            {
                erase_and_push();
            }
            correct_pop(opeartion);
        }
        else if (str[i] == '(')
        {
            opeartion.push(str[i]);
        }
        else if (opeartion.empty() || priority_op(str[i]) > priority_op(correct_top(opeartion)))
        {
            if (!str_number.empty())
            {
                number.push(Value(stoi((str_number))));
                str_number.clear();
            }
            opeartion.push(str[i]);
        }

        else if (priority_op(str[i]) <= priority_op(correct_top(opeartion)))
        {
            if (!str_number.empty())
            {
                number.push(Value(stoi((str_number))));
                str_number.clear();
            }
            if (correct_top(opeartion) != '(') {
                erase_and_push();
                i--;
            }
            else
            {
                opeartion.push(str[i]);
            }

        }

    }
    if (!str_number.empty())
    {
        number.push(Value(stoi((str_number))));
    }
    while (!opeartion.empty())
    {
        erase_and_push();
    }
    return correct_top(number)->Evaluate();
}