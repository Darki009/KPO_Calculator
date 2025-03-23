#include <iostream>
#include "calculator-logic/Calculator.h"

int main()
{
    std::string sheet = "10+7-6*4/8-78";
    Calculator calc = Calculator();
    calc.setExpr(sheet);
    std::cout << calc.calculateExpr();
    return 0;
}