#pragma once

#include <memory>
#include <string>
#include <stdexcept>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual double Evaluate() const = 0;

};

//using ExpressionPtr = std::unique_ptr<Expression>;
//Класс, представляющий конкретное число - лист дерева выражения
class ValueExpr;

// Базовый класс бинарных операций
class BinaryExpr;

// Класс для операции умножения
class ProductExpr;

// Класс для операции сложения
class SumExpr;

// Класс для операции вичитания
class SubExpr;

// Класс для операции вознесение в степень
class PowExpr;

// Класс для операции деления
class DivExpr;

using ExpressionPtr = std::unique_ptr<Expression>;

// Функции для формирования выражения
 inline ExpressionPtr Value(double value);
template<class T>
 
inline ExpressionPtr formation_binary_expr(ExpressionPtr left, ExpressionPtr right);
 
 
 class ValueExpr : public Expression {
 public:
     ValueExpr(double value) : value_(value) {}

     double Evaluate() const override {
         return value_;
     }


 private:
     double value_;
 };
 class BinaryExpr : public Expression {
 public:
     BinaryExpr(ExpressionPtr left, ExpressionPtr right) :
         left_(move(left)),
         right_(move(right)) {}

     // Здесь виртуальные функции переопределяются с ключевым словом "final".
     // Это то же самое, что и "override", но только мы запрещаем дальнейшее
     // их переопределение в наследниках. 
     double Evaluate() const final {
         return EvaluateOnValues(left_->Evaluate(), right_->Evaluate());
     }

 private:
     // Введение этих новых вирутальных функций позволяет уменьшить дублирование
     // кода в наследниках,
     virtual double EvaluateOnValues(double l, double r) const = 0;

     ExpressionPtr left_;
     ExpressionPtr right_;
 };
 class ProductExpr : public BinaryExpr {
 public:
     // Данное выражение позволяет унаследовать конструктор из базового класса.
     using BinaryExpr::BinaryExpr;
 private:

     double EvaluateOnValues(double left, double right) const override {
         return left * right;
     }
 };
 class SumExpr : public BinaryExpr {
 public:

     using BinaryExpr::BinaryExpr;

 private:

     double EvaluateOnValues(double left, double right) const override {
         return left + right;
     }
 };
 class SubExpr : public BinaryExpr {
 public:

     using BinaryExpr::BinaryExpr;

 private:

     double EvaluateOnValues(double left, double right) const override {
         return left - right;
     }
 };
 class DivExpr : public BinaryExpr {
 public:
     using BinaryExpr::BinaryExpr;

 private:

     double EvaluateOnValues(double left, double right) const override {
         if (right == 0)
         {
             throw std::logic_error("can not division by zero");
         }
         return left / right;
     }
 };
 class PowExpr : public BinaryExpr {
 public:
     using BinaryExpr::BinaryExpr;
 private:

     double EvaluateOnValues(double left, double right) const override {
         return pow(left, right);
     }
 };

 ExpressionPtr Value(double value)
 {
     return std::make_unique<ValueExpr>(value);
 }
 template<class T>//функция для формирования выражения
 ExpressionPtr formation_binary_expr(ExpressionPtr left, ExpressionPtr right) {
     return std::make_unique<T>(move(left), move(right));
 }





