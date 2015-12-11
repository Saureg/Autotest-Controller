#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_comboProjects_activated(int index);

    void on_btn_AddTest_clicked();

    void on_btnEditTest_clicked();

    void on_btnDeleteTest_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
