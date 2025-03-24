#include <QWidget>
#include "../calculator-logic/Calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainTheme; }
QT_END_NAMESPACE

static QString signButtons[7] = {"plusButton", "minusButton", "multiplyButton",
                                 "divButton", "leftBracketButton", "rigthBracketButton", "buttonPoint"};

class mainTheme : public QWidget {

Q_OBJECT
public:

    explicit mainTheme(QWidget *parent = nullptr);

    ~mainTheme() override;
private slots:
    void addSymbol();
    void clear();
    void expressionEqual();

    void deleteLastSymbol();
private:

    Ui::mainTheme *ui;
    Calculator calculator;
};

