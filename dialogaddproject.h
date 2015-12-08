#ifndef DIALOGADDPROJECT_H
#define DIALOGADDPROJECT_H

#include <QDialog>

namespace Ui {
class DialogAddProject;
}

class DialogAddProject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddProject(QWidget *parent = 0);
    ~DialogAddProject();

private:
    Ui::DialogAddProject *ui;
};

#endif // DIALOGADDPROJECT_H
