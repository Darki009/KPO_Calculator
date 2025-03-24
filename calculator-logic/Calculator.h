#include <string>
#include <array>
#include <stack>

#define ARRAY_LENGTH 4


static std::array<char, ARRAY_LENGTH> supportedOperations{'+', '-', '*', '/'};
class Calculator {
private:
    std::string expression;

    void calculateBrackets(int firstBracketPos);
public:

    Calculator() {expression = "";};
    inline void setExpr(const std::string& expr) { expression = expr; };

    inline void clearExpr() { expression = ""; };

    static bool isCanBePlacedInExpression(std::string expr, char charToPlace);
    double calculateExpr();

    static bool equalOneOfOperations(char compare);
};



