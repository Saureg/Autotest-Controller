#include "widget.h"
#include "ui_widget.h"
#include "connectdb.h"

#include <QtSql>
#include <QDebug>

QSqlTableModel *projects;
QSqlTableModel *autotests;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Конструктор=================================

    //Подключение к БД
    connectDB();

    //Заполнение модели проектов
    projects = new QSqlTableModel;
    projects->setTable("Project");
    projects->select();

    //Настройка селекта с проектами
    int countProjectModel = projects->rowCount();
    for (int i=0; i<countProjectModel; i++)
    {
        ui->comboProjects->addItem(projects->record(i).value(1).toString());
    }

    //Настройка ширины столбцов
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->setColumnWidth(3, 200);
    ui->tableWidget->setColumnWidth(4, 180);
    ui->tableWidget->setColumnWidth(5, 70);
    ui->tableWidget->setColumnWidth(6, 160);
    ui->tableWidget->setColumnWidth(7, 150);
    ui->tableWidget->setColumnWidth(8, 160);

    //Настройка ограничений таблицы
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setSortingEnabled(1);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboProjects_activated(int index)
{
    //Заполнение модели автотестов
//    autotests = new QSqlTableModel;
//    autotests->setTable("Autotests");
//    autotests->select();

    //Очищение таблицы
    int n=ui->tableWidget->rowCount();
    for (int i=0; i<n; i++) ui->tableWidget->removeRow(0);

    //Выбор автотестов конкретного проекта
    QSqlQuery query;
    query.exec("SELECT * FROM Autotests WHERE project = " + QString::number(index+1) + ";");

    //Добавление строк
//    int lengthQuery = 0;
//    while (query.next()) lengthQuery++;
//    for (int i=0; i<lengthQuery; i++)
//    {
//        ui->tableWidget->insertRow(i);
//    }

    //Заполнение таблицв
    while (query.next())
         {
              ui->tableWidget->insertRow(0);
              ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
              ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toString()));
              ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
              ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
              ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));
              ui->tableWidget->setItem(0, 5, new QTableWidgetItem(query.value(5).toString()));
              ui->tableWidget->setItem(0, 6, new QTableWidgetItem(query.value(6).toString()));
              ui->tableWidget->setItem(0, 7, new QTableWidgetItem(query.value(7).toString()));
              ui->tableWidget->setItem(0, 8, new QTableWidgetItem(query.value(8).toString()));
              ui->tableWidget->setRowHeight(0, 20);
         }


    //ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(index)));
//    ui->tableWidget
}
