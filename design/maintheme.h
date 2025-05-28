#include <QWidget>
#include <QIcon>
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
    void changeThemeSlot(); // Новый слот

private:
    void applyDarkTheme();  // Исходные значения
    void applyLightTheme(); // Светлая адаптация

    Ui::mainTheme *ui;
    Calculator calculator;
    bool darkTheme = true;
};