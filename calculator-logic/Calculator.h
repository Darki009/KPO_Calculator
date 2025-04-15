#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <sstream>
#include <cmath>
#include <stdexcept>

// Базовый класс для операции (оставляем как было)
class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(double a, double b) const = 0;
    virtual char getSymbol() const = 0;
    virtual int getPriority() const = 0;
};

// Конкретные операции (оставляем как было)
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

// Фабрика операций (оставляем как было)
class OperationFactory {
public:
    static std::unique_ptr<Operation> createOperation(char op) {
        switch (op) {
            case '+': return std::make_unique<AddOperation>();
            case '-': return std::make_unique<SubtractOperation>();
            case '*': return std::make_unique<MultiplyOperation>();
            case '/': return std::make_unique<DivideOperation>();
            default: throw std::invalid_argument("Unsupported operation");
        }
    }

    static bool isOperation(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
};

class Calculator {
private:
    std::string expression;
    std::vector<std::unique_ptr<Operation>> supportedOperations;

    void calculateBrackets(size_t firstBracketPos);

public:
    Calculator() {
        // Инициализация поддерживаемых операций (как было)
        supportedOperations.push_back(std::make_unique<AddOperation>());
        supportedOperations.push_back(std::make_unique<SubtractOperation>());
        supportedOperations.push_back(std::make_unique<MultiplyOperation>());
        supportedOperations.push_back(std::make_unique<DivideOperation>());
    }

    // Интерфейс класса полностью сохранен
    inline void setExpr(const std::string& expr) { expression = expr; };
    inline void clearExpr() { expression = ""; };

    static bool isCanBePlacedInExpression(std::string expr, char charToPlace);

    static std::string doubleToString(double number, int precision);

    double calculateExpr();
};



