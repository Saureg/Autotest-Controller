#include "dialogaddproject.h"
#include "ui_dialogaddproject.h"

DialogAddProject::DialogAddProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddProject)
{
    ui->setupUi(this);
}

DialogAddProject::~DialogAddProject()
{
    delete ui;
}
