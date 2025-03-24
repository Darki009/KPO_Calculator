#include "Calculator.h"

bool Calculator::isCanBePlacedInExpression(std::string expr, char charToPlace) {
    int lastChar = expr.size() - 1;

    if (expr == "" && (charToPlace == '.' || charToPlace == '/' || charToPlace == '*' || charToPlace == ')')){
        return false;
    }

    if (equalOneOfOperations(expr[lastChar]) && equalOneOfOperations(charToPlace)) {
        return false;
    }

    if (expr[lastChar] == '(' && (charToPlace == '*' || charToPlace == '/')) {
        return false;
    }

    return true;
}

double Calculator::calculateExpr() {
    if (expression == ""){
        return 0;
    }

    std::string formatedString = "(.)";
    formatedString.replace(1,1,expression);
    expression = formatedString;

    calculateBrackets(0);
    return std::stod(expression);
}

void Calculator::calculateBrackets(int firstBracketPos) {

     int leftEnd=firstBracketPos + 1;
    std::stack<double> numbers{};
    std::stack<char> operations{};
    for (int i = firstBracketPos + 1; i < expression.size() + 1; i++) {


        if (equalOneOfOperations(expression[i]) || expression[i] == ')' || expression[i] == '\0') {
            if (i - leftEnd != 0) {
                numbers.push(std::stod(expression.substr(leftEnd, i - leftEnd)));
                leftEnd=i + 1;
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

            if (expression[i] == '*' || expression[i] == '/' ) {
                operations.push(expression[i]);
            }

            if (expression[i] == '+' || expression[i] == '-' ) {
                leftEnd=i;
            }

        }

        if (expression[i] == '(') {
            calculateBrackets(i);
            i = leftEnd;
        }



        if (expression[i] == '\0' || expression[i] == ')') {
            double result = 0;
            while (!numbers.empty()) {
                result += numbers.top();
                numbers.pop();
            }
            expression.replace(firstBracketPos, i - firstBracketPos + 1, std::to_string(result));
            return;
        }
    }
}

bool Calculator::equalOneOfOperations(char compare) {
    for (char operation : supportedOperations)
        if (compare == operation)
            return true;
    return false;
}
