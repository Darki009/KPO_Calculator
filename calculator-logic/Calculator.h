#include <string>
#include <array>
#include <stack>

#define ARRAY_LENGTH 4

class Calculator {
private:
    std::string expression;
    std::array<char, ARRAY_LENGTH> supportedOperations{'+', '-', '*', '/'};


public:
    Calculator() {expression = "";};

    inline void setExpr(const std::string& expr) { expression = expr; };
    inline void clearExpr() { expression = ""; };

    bool checkExpr(std::string expr);

    double calculateExpr();

    bool equalOneOfArray(char compare);
};



