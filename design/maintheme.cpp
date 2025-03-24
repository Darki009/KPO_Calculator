#include "maintheme.h"
#include "ui_mainTheme.h"


mainTheme::mainTheme(QWidget *parent) :
        QWidget(parent), ui(new Ui::mainTheme) {
    ui->setupUi(this);
}

mainTheme::~mainTheme() {
    delete ui;
}
