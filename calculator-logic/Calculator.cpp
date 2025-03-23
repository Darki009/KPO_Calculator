#include "Calculator.h"

bool Calculator::checkExpr(std::string expr) {

}

double Calculator::calculateExpr() {
    int leftEnd = 0;
    std::stack<double> numbers{};
    std::stack<char> operations{};
    for (int i = 0; i < expression.size() + 1; i++) {



        if (equalOneOfArray(expression[i]) || expression[i] == '\0') {
            numbers.push(std::stod(expression.substr(leftEnd, i - leftEnd)));
            leftEnd = i + 1;

            if (expression[i] == '+' || expression[i] == '-' ) {
                leftEnd = i;
            }

            if (!operations.empty()) {
                switch(operations.top()) {
                    case '*': {
                        double num1 = numbers.top();
                        numbers.pop();
                        double num2 = numbers.top();
                        numbers.pop();
                        numbers.push(num1 * num2);

                        operations.pop();
                        break;
                    }
                    case '/': {
                        double num1 = numbers.top();
                        numbers.pop();
                        double num2 = numbers.top();
                        numbers.pop();
                        numbers.push(num2 / num1);

                        operations.pop();
                        break;
                    }
                }
            }
            operations.push(expression[i]);
        }




        if (expression[i] == '\0') {
            double result = 0;
            while (!numbers.empty()) {
                result += numbers.top();
                numbers.pop();
            }
            return result;
        }
    }
}

bool Calculator::equalOneOfArray(char compare) {
    for (char operation : supportedOperations)
        if (compare == operation)
            return true;
    return false;
}
