#include "Calculator.h"

bool Calculator::isCanBePlacedInExpression(std::string expr, char charToPlace) {
    int lastChar = expr.size() - 1;

    if (expr == "" && (charToPlace == '.' || charToPlace == '/' ||
                       charToPlace == '*' || charToPlace == ')')){
        return false;
    }

    if (OperationFactory::isOperation(expr[lastChar]) &&
        OperationFactory::isOperation(charToPlace)) {
        return false;
    }

    if (expr[lastChar] == '(' && (charToPlace == '*' || charToPlace == '/')) {
        return false;
    }

    return true;
}

std::string Calculator::doubleToString(double number, int precision) {
    std::ostringstream stream;
    stream.precision(precision);
    stream << std::fixed << number;
    return stream.str();
}

double Calculator::calculateExpr() {
    if (expression == ""){
        return 0;
    }

    expression = "(" + expression + ")";
    calculateBrackets(0);

    return std::stod(expression);
}

void Calculator::calculateBrackets(size_t firstBracketPos) {
    std::stack<double> numbers;
    std::stack<std::unique_ptr<Operation>> operations;
    size_t leftEnd = firstBracketPos + 1;

    for (size_t i = firstBracketPos + 1; i <= expression.size(); ++i) {
        char c = i < expression.size() ? expression[i] : ')';

        if (c == '(') {
            calculateBrackets(i);
            i = leftEnd;
            continue;
        }

        if (OperationFactory::isOperation(c) || c == ')' || i == expression.size()) {
            if (i > leftEnd) {
                numbers.push(std::stod(expression.substr(leftEnd, i - leftEnd)));
                leftEnd = i + 1;
            }

            if (OperationFactory::isOperation(c)) {
                auto op = OperationFactory::createOperation(c);

                // Обрабатываем операции с более высоким приоритетом
                while (!operations.empty() &&
                       operations.top()->getPriority() >= op->getPriority()) {
                    auto prev_op = std::move(operations.top());
                    operations.pop();

                    double b = numbers.top();
                    numbers.pop();
                    double a = numbers.top();
                    numbers.pop();

                    numbers.push(prev_op->execute(a, b));
                }

                operations.push(std::move(op));
            }
        }

        if (c == ')') {
            // Обрабатываем оставшиеся операции
            while (!operations.empty()) {
                auto op = std::move(operations.top());
                operations.pop();

                double b = numbers.top();
                numbers.pop();
                double a = numbers.top();
                numbers.pop();

                numbers.push(op->execute(a, b));
            }

            if (numbers.size() != 1) {
                throw std::runtime_error("Invalid expression");
            }

            expression.replace(firstBracketPos, i - firstBracketPos + 1,
                               doubleToString(numbers.top(), 9));
            return;
        }
    }
}
