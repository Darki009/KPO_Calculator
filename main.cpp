#include <iostream>
#include "calculator-logic/Calculator.h"

int main()
{
    std::string sheet = "(2*5-6*9-(9-2*(9+35)/78)+51)";
    Calculator calc = Calculator();
    calc.setExpr(sheet);
    std::cout << calc.calculateExpr();
    return 0;
}