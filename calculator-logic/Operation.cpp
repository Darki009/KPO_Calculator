#include "Operation.h"

std::unique_ptr<Operation> OperationFactory::createOperation(char op) {
    switch (op) {
        case '+': return std::make_unique<AddOperation>();
        case '-': return std::make_unique<SubtractOperation>();
        case '*': return std::make_unique<MultiplyOperation>();
        case '/': return std::make_unique<DivideOperation>();
        default: throw std::invalid_argument("Unsupported operation");
    }
}

bool OperationFactory::isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
