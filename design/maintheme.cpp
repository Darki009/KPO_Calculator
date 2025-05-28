#include "maintheme.h"
#include "ui_mainTheme.h"
#include <QRegularExpression>
#include <QPushButton>

mainTheme::mainTheme(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainTheme) {
    ui->setupUi(this);

    connect(ui->clearAllButton, SIGNAL(clicked()), this,  SLOT(clear()));
    connect(ui->deleteLastButton, SIGNAL(clicked()), this,  SLOT(deleteLastSymbol()));
    connect(ui->equalButton, SIGNAL(clicked()), this,SLOT(expressionEqual()));

    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("button%1").arg(i);
        auto* button = findChild<QPushButton*>(buttonName);
        if (button)
            connect(button, SIGNAL(clicked()), this, SLOT(addSymbol()));
    }
    for (const QString& buttonName : signButtons) {
        auto* button = findChild<QPushButton*>(buttonName);
        if (button)
            connect(button, SIGNAL(clicked()), this, SLOT(addSymbol()));
    }

    connect(ui->changeTheme, &QPushButton::clicked, this, &mainTheme::changeThemeSlot);
    applyDarkTheme();
}

mainTheme::~mainTheme() {
    delete ui;
}

void mainTheme::addSymbol() {
    if (ui->textEdit->toPlainText() == "Error" || ui->textEdit->toPlainText() == "inf") {
        clear();
    }

    auto* button = dynamic_cast<QPushButton *>(QObject::sender());
    if (button){
        if (Calculator::isCanBePlacedInExpression (
                ui->textEdit->toPlainText().toStdString(),
                button->text().toStdString().c_str()[0])) {
            ui->textEdit->setText(ui->textEdit->toPlainText() + button->text());
        }
    }

}

void mainTheme::clear() {
    calculator.clearExpr();
    ui->textEdit->setText("");
}

void mainTheme::expressionEqual() {
    try {
        QString input = ui->textEdit->toPlainText().trimmed();

        if (input.isEmpty()) {
            ui->textEdit->setText("0");
            return;
        }

        calculator.setExpr(input.toStdString());

        double result = calculator.calculateExpr();

        QString output;
        if (result == std::floor(result)) {
            output = QString::number(static_cast<long long>(result));
        } else {
            output = QString::number(result, 'f', 9).replace(QRegularExpression("\\.?0+$"), "");
        }

        ui->textEdit->setText(output);
    }
    catch (const std::exception& e) {
        ui->textEdit->setText("Error: " + QString(e.what()));
    }
    catch (...) {
        ui->textEdit->setText("Calculation error");
    }
}

void mainTheme::deleteLastSymbol() {
    QString text = ui->textEdit->toPlainText();
    if (!text.isEmpty()) {
        text.chop(1);
        ui->textEdit->setText(text);
    }
}
void mainTheme::changeThemeSlot() {
    darkTheme = !darkTheme;
    if (darkTheme) {
        applyDarkTheme();
    } else {
        applyLightTheme();
    }
}

void mainTheme::applyDarkTheme() {
    // Восстановить исходные значения из .ui
    this->setStyleSheet("background-color: rgb(0, 0, 0); color: black;");
    ui->textEdit->setStyleSheet("background-color: rgba(255, 255, 255, 220); border-width: 2px; border-radius: 10px; padding: 3px; color: black;");

    // Кнопки с оранжевым
    QString orange =
            "QPushButton { background-color: rgba(255, 128, 0, 200); border-style: outset; border-width: 2px; border-radius: 10px; padding: 6px; }"
            "QPushButton:pressed { background-color: rgba(193, 94, 0, 200); border-style: inset; }";
    // Кнопки с белым
    QString white =
            "QPushButton { background-color: rgba(255, 255, 255, 200); border-style: outset; border-width: 2px; border-radius: 10px; padding: 6px; }"
            "QPushButton:pressed { background-color: rgba(215, 215, 215, 200); border-style: inset; }";

    // Кнопки
    QList<QString> orangeButtons = {"plusButton", "minusButton", "multiplyButton", "divButton",
                                    "leftBracketButton", "rigthBracketButton", "clearAllButton", "deleteLastButton", "equalButton"};
    for (const QString& name : orangeButtons) {
        QPushButton* btn = findChild<QPushButton*>(name);
        if (btn) btn->setStyleSheet(orange);
    }
    // Числа и точка
    for (int i = 0; i <= 9; ++i) {
        QPushButton* btn = findChild<QPushButton*>(QString("button%1").arg(i));
        if (btn) btn->setStyleSheet(white);
    }
    QPushButton* btnPoint = findChild<QPushButton*>("buttonPoint");
    if (btnPoint) btnPoint->setStyleSheet(white);

    // Кнопка смены темы — иконка светлая
    ui->changeTheme->setStyleSheet(white);
    ui->changeTheme->setIcon(QIcon(":/icons/switchToLight.ico"));
}

void mainTheme::applyLightTheme() {
    // Светлая адаптация
    this->setStyleSheet("background-color: rgb(245,245,245); color: #222;");
    ui->textEdit->setStyleSheet("background-color: #fff; color: #222; border: 2px solid #bbb; border-radius: 10px; padding: 3px;");

    // Светлая оранжевая кнопка
    QString orange =
            "QPushButton { background-color: #ffd180; color: #222; border-style: outset; border-width: 2px; border-radius: 10px; padding: 6px; }"
            "QPushButton:pressed { background-color: #ffb300; border-style: inset; }";
    // Светлая обычная кнопка
    QString white =
            "QPushButton { background-color: #f5f5f5; color: #222; border-style: outset; border-width: 2px; border-radius: 10px; padding: 6px; }"
            "QPushButton:pressed { background-color: #e0e0e0; border-style: inset; }";

    QList<QString> orangeButtons = {"plusButton", "minusButton", "multiplyButton", "divButton",
                                    "leftBracketButton", "rigthBracketButton", "clearAllButton", "deleteLastButton", "equalButton"};
    for (const QString& name : orangeButtons) {
        QPushButton* btn = findChild<QPushButton*>(name);
        if (btn) btn->setStyleSheet(orange);
    }
    for (int i = 0; i <= 9; ++i) {
        QPushButton* btn = findChild<QPushButton*>(QString("button%1").arg(i));
        if (btn) btn->setStyleSheet(white);
    }
    QPushButton* btnPoint = findChild<QPushButton*>("buttonPoint");
    if (btnPoint) btnPoint->setStyleSheet(white);

    // Кнопка смены темы — иконка тёмная
    ui->changeTheme->setStyleSheet(white);
    ui->changeTheme->setIcon(QIcon(":/icons/switchToDark.ico"));
}