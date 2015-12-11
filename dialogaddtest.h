#ifndef DIALOGADDTEST_H
#define DIALOGADDTEST_H

#include <QDialog>

namespace Ui {
class DialogAddTest;
}

class DialogAddTest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTest(QWidget *parent = 0);
    ~DialogAddTest();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogAddTest *ui;
};

#endif // DIALOGADDTEST_H
