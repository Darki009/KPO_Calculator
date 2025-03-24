#include <string>
#include <array>
#include <stack>

#define ARRAY_LENGTH 4

class Calculator {
private:
    std::array<char, ARRAY_LENGTH> supportedOperations{'+', '-', '*', '/'};
    std::string expression;

    void calculateBrackets(int firstBracketPos);
public:

    Calculator() {expression = "";};
    inline void setExpr(const std::string& expr) { expression = expr; };

    inline void clearExpr() { expression = ""; };

    bool checkExpr();
    double calculateExpr();

    bool equalOneOfArray(char compare);
};



