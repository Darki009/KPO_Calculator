#include "maintheme.h"
#include "ui_mainTheme.h"

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
        calculator.setExpr(ui->textEdit->toPlainText().toStdString());
        QString buf;
        ui->textEdit->setText(buf.setNum(calculator.calculateExpr(), 'g', 6));
    }
    catch (...){
        ui->textEdit->setText("Error");
    }
}

void mainTheme::deleteLastSymbol() {
    QString text = ui->textEdit->toPlainText();
    if (!text.isEmpty()) {
        text.chop(1);
        ui->textEdit->setText(text);
    }
}
