#include "widget.h"
#include <QApplication>

int extCurrentProject;
QStringList extProjectList;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
