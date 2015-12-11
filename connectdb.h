#ifndef CONNECTDB
#define CONNECTDB

#include <QtSql>

static bool connectDB()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName( "/home/test/krit");
    db.setDatabaseName("../Autotest-Controller/autotest_db");
    db.open();

    return true;

}

#endif // CONNECTDB

