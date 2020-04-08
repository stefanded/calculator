#pragma once
#include "Common.h"
#include<string>
#include<stack>


class Parse 
{
   
    std::string str;
    std::stack<ExpressionPtr> number;
    std::stack<char> opeartion;
    ExpressionPtr new_number(ExpressionPtr left, char op, ExpressionPtr right)const;
    template<class T>
    T& correct_top(std::stack<T>& cont)const;//функция для коректного обращение к stack
    template<class T>
    void correct_pop(std::stack<T>& cont);//функция для коректного удаления с stack
    void erase_and_push();//удаляет операцию с operation и додает новое число в number
    size_t priority_op(char op) const;//возвращает приоритет операции
public:
    Parse(const std::string& str);
    void get_string(const std::string& str);//получает новою строку
    double result();//возвращает результат
 
};

