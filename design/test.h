//
// Created by darki on 28.05.2025.
//

#ifndef CALCULATOR_TEST_H
#define CALCULATOR_TEST_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class test; }
QT_END_NAMESPACE

class test : public QWidget {
Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);

    ~test() override;

private:
    Ui::test *ui;
};


#endif //CALCULATOR_TEST_H
