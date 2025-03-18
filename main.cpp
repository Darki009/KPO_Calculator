#include <QApplication>
#include <QFile>
#include <QWidget>
#include "design/mainwindow/ui_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget widget;
    Ui::MainWindow ui;
    ui.setupUi(&widget);

    widget.show();

    return QApplication::exec();
}
