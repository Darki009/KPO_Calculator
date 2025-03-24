#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class mainTheme; }
QT_END_NAMESPACE

class mainTheme : public QWidget {
Q_OBJECT

public:
    explicit mainTheme(QWidget *parent = nullptr);

    ~mainTheme() override;

private:
    Ui::mainTheme *ui;
};

