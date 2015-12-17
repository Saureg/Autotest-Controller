#include "widget.h"
#include "ui_widget.h"
#include "connectdb.h"
#include "dialogaddtest.h"

#include <QtSql>
#include <QDebug>
#include <QMessageBox>


extern int extCurrentProject;
extern QStringList extProjectList;

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

    //Скрвтие кнопки "Добавить проект"
    ui->btnAddProject->setHidden(1);

    //Заполнение модели проектов
    projects = new QSqlTableModel;
    projects->setTable("Project");
    projects->select();

    //Настройка селекта с проектами
//    ui->comboProjects->setView(QAbstractItemView::QFrame);
    int countProjectModel = projects->rowCount();
    for (int i=0; i<countProjectModel; i++)
    {
        ui->comboProjects->addItem(projects->record(i).value(1).toString());
        extProjectList.append(projects->record(i).value(1).toString());
    }

    //Настройка ширины столбцов
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->setColumnWidth(3, 200);
//    ui->tableWidget->setColumnWidth(4, 180);
    ui->tableWidget->setColumnWidth(4, 70);
    ui->tableWidget->setColumnWidth(5, 160);
    ui->tableWidget->setColumnWidth(6, 150);
    ui->tableWidget->setColumnWidth(7, 160);

    //Настройка ограничений таблицы
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setSortingEnabled(1);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->verticalHeader()->setStretchLastSection(true);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboProjects_activated(int index)
{

    //Очищение таблицы
    int n=ui->tableWidget->rowCount();
    for (int i=0; i<n; i++) ui->tableWidget->removeRow(0);

    //Выбор автотестов конкретного проекта
    QSqlQuery query;
    query.exec("SELECT Autotests.id, Block.name, Autotests.functional, Autotests.name, Autotests.project, Autotests.testlink, Autotests.author, Autotests.date, Autotests.comment "
               "FROM Autotests, Block WHERE project = " + QString::number(index+1) + " AND Autotests.block = Block.id_block;");

    //Заполнение таблицв
    while (query.next())
         {
              ui->tableWidget->insertRow(0);
              ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toString())); //id
              ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toString())); //Блок
              ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value(2).toString())); //Функциональные возможности
              ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));  //Название
              //ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
              ui->tableWidget->setItem(0, 4, new QTableWidgetItem(ui->comboProjects->currentText())); //Проект
              ui->tableWidget->setItem(0, 5, new QTableWidgetItem(query.value(5).toString())); //Тестлинк
              ui->tableWidget->setItem(0, 6, new QTableWidgetItem(query.value(6).toString())); //автор
              ui->tableWidget->setItem(0, 7, new QTableWidgetItem(query.value(7).toString())); //Дата
              ui->tableWidget->setItem(0, 8, new QTableWidgetItem(query.value(8).toString())); //Комментарий
              //ui->tableWidget->setRowHeight(0, 20);
         }

    ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->labelRowCount->setText("Количество записей: "+QString::number(ui->tableWidget->rowCount()));
}

//Добавить информацию об автотесте
void Widget::on_btn_AddTest_clicked()
{

    extCurrentProject = ui->comboProjects->currentIndex();

    //Отображение диалога добавления теста
    DialogAddTest dialogAddTest(this);
    dialogAddTest.exec();

    //Добавление
    //ui->tableWidget->insertRow(ui->tableWidget->rowCount());

}

//Изменить информацию об автотесте
void Widget::on_btnEditTest_clicked()
{

}

//Удалить информацию об автотесте
void Widget::on_btnDeleteTest_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
//    qDebug() << "Current row " + QString::number(ui->tableWidget->currentRow());

    //Удаление записи из базы
    int idRecord = ui->tableWidget->item(currentRow, 0)->text().toInt();
    qDebug() << "ID = " + ui->tableWidget->item(currentRow, 0)->text();
    QSqlQuery queryRemove;
    //queryRemove.exec("DELETE FROM Autotests WHERE id = '" + idRecord + "'");

    queryRemove.prepare("DELETE FROM Autotests WHERE id = :id");
    queryRemove.bindValue(":id", idRecord);
    queryRemove.exec();


    //Тест******************************************
    //Обновление таблицы после удаления

    //Очищение таблицы
    int n=ui->tableWidget->rowCount();
    for (int i=0; i<n; i++) ui->tableWidget->removeRow(0);

    //Выбор автотестов конкретного проекта
    QSqlQuery query;
    query.exec("SELECT Autotests.id, Block.name, Autotests.functional, Autotests.name, Autotests.project, Autotests.testlink, Autotests.author, Autotests.date, Autotests.comment "
               "FROM Autotests, Block WHERE project = " + QString::number(ui->comboProjects->currentIndex()+1) + " AND Autotests.block = Block.id_block;");

    //Заполнение таблицв
    while (query.next())
         {
              ui->tableWidget->insertRow(0);
              ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toString())); //id
              ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toString())); //Блок
              ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value(2).toString())); //Функциональные возможности
              ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));  //Название
              //ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
              ui->tableWidget->setItem(0, 4, new QTableWidgetItem(ui->comboProjects->currentText())); //Проект
              ui->tableWidget->setItem(0, 5, new QTableWidgetItem(query.value(5).toString())); //Тестлинк
              ui->tableWidget->setItem(0, 6, new QTableWidgetItem(query.value(6).toString())); //автор
              ui->tableWidget->setItem(0, 7, new QTableWidgetItem(query.value(7).toString())); //Дата
              ui->tableWidget->setItem(0, 8, new QTableWidgetItem(query.value(8).toString())); //Комментарий
              //ui->tableWidget->setRowHeight(0, 20);
         }

    ui->labelRowCount->setText("Количество записей: "+QString::number(ui->tableWidget->rowCount()));
    //**************************************************8
}

//Не работает
void Widget::refresh_table()
{

}
