#include "maintheme.h"
#include "ui_mainTheme.h"
#include <QRegularExpression>

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
