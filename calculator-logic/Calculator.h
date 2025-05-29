#pragma once
#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include "Operation.h"

#ifdef _WIN32
#  ifdef CALC_CORE_EXPORTS
#    define CALC_CORE_API __declspec(dllexport)
#  else
#    define CALC_CORE_API __declspec(dllimport)
#  endif
#else
#  define CALC_CORE_API
#endif

class CALC_CORE_API Calculator {
private:
    std::string expression;
    std::vector<std::unique_ptr<Operation>> supportedOperations;

    void calculateBrackets(size_t firstBracketPos);

public:
    Calculator();
    inline void setExpr(const std::string& expr) { expression = expr; };
    inline void clearExpr() { expression = ""; };

    static bool isCanBePlacedInExpression(std::string expr, char charToPlace);

    static std::string doubleToString(double number, int precision);

    double calculateExpr();
};
