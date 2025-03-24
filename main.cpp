#include "design/maintheme.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainTheme window;

    window.show();

    return QApplication::exec();

}