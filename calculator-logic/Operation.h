#pragma once
#include <memory>
#include <stdexcept>

// Базовый класс для операции
class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(double a, double b) const = 0;
    virtual char getSymbol() const = 0;
    virtual int getPriority() const = 0;
};

class AddOperation : public Operation {
public:
    double execute(double a, double b) const override { return a + b; }
    char getSymbol() const override { return '+'; }
    int getPriority() const override { return 1; }
};

class SubtractOperation : public Operation {
public:
    double execute(double a, double b) const override { return a - b; }
    char getSymbol() const override { return '-'; }
    int getPriority() const override { return 1; }
};

class MultiplyOperation : public Operation {
public:
    double execute(double a, double b) const override { return a * b; }
    char getSymbol() const override { return '*'; }
    int getPriority() const override { return 2; }
};

class DivideOperation : public Operation {
public:
    double execute(double a, double b) const override {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    char getSymbol() const override { return '/'; }
    int getPriority() const override { return 2; }
};

class OperationFactory {
public:
    static std::unique_ptr<Operation> createOperation(char op);
    static bool isOperation(char c);
};
