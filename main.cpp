#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QRegularExpression>
#include <memory>

class Calculator : public QWidget {
Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr) : QWidget(parent) {
        // Создаем поле для ввода
        display = std::make_unique<QLineEdit>(this);
        display->setReadOnly(true);
        display->setAlignment(Qt::AlignRight);
        display->setMaxLength(15);

        // Создаем кнопки
        QString buttons[16] = {
                "7", "8", "9", "/",
                "4", "5", "6", "*",
                "1", "2", "3", "-",
                "0", ".", "=", "+"
        };

        // Создаем сетку для размещения кнопок
        auto grid = std::make_unique<QGridLayout>(this);
        grid->addWidget(display.get(), 0, 0, 1, 4);

        int row = 1, col = 0;
        for (int i = 0; i < 16; ++i) {
            auto button = std::make_unique<QPushButton>(buttons[i], this);
            grid->addWidget(button.get(), row, col);
            connect(button.get(), &QPushButton::clicked, this, &Calculator::onButtonClicked);
            button.release(); // Передаем владение сетке
            col++;
            if (col > 3) {
                col = 0;
                row++;
            }
        }

        setLayout(grid.release()); // Передаем владение виджету
        setWindowTitle("Calculator");
    }

private slots:
    void onButtonClicked() {
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        QString value = button->text();

        if (value == "=") {
            // Вычисляем результат
            try {
                double result = evaluateExpression(display->text());
                display->setText(QString::number(result));
            } catch (const std::exception &e) {
                display->setText("Error");
            }
        } else {
            // Добавляем символ в поле ввода
            display->setText(display->text() + value);
        }
    }

private:
    std::unique_ptr<QLineEdit> display;

    // Функция для вычисления выражения
    double evaluateExpression(const QString &expression) {
        // Простая реализация вычисления (без учета приоритетов операций)
        // Для более сложных случаев можно использовать библиотеки или парсеры
        QStringList tokens = expression.split(QRegularExpression("([+\\-*/])"), Qt::KeepEmptyParts);
        if (tokens.size() != 2) {
            throw std::invalid_argument("Invalid expression");
        }

        double num1 = tokens[0].toDouble();
        double num2 = tokens[1].toDouble();
        QString op = expression[tokens[0].length()];

        if (op == "+") return num1 + num2;
        if (op == "-") return num1 - num2;
        if (op == "*") return num1 * num2;
        if (op == "/") {
            if (num2 == 0) throw std::invalid_argument("Division by zero");
            return num1 / num2;
        }

        throw std::invalid_argument("Unknown operation");
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.show();

    return app.exec();
}

#include "main.moc"