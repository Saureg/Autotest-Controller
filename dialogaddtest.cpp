#include "dialogaddtest.h"
#include "ui_dialogaddtest.h"
#include "connectdb.h"
#include "widget.h"

#include <QtSql>
#include <QMessageBox>

extern int extCurrentProject;
extern QStringList extProjectList;

//QSqlTableModel *projects;


DialogAddTest::DialogAddTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddTest)
{
    ui->setupUi(this);

    //Конструктор

    ui->dateEdit->setEnabled(0);
    ui->dateEdit->setDate(QDate::currentDate());

    //Подключение к БД
    connectDB();



    //Настройка селекта с проектами
    ui->comboProject->addItems(extProjectList);

    ui->comboProject->setCurrentIndex(extCurrentProject);

    //Заполнение комбоокса блоков
    QSqlQuery blocks;
    blocks.exec("SELECT name FROM Block");
    while (blocks.next())
    {
        ui->comboBlock->addItem(blocks.value(0).toString());
    }

    //Обязательные поля
    QString requiredFieldToolTip = "Обязательное поле";
    ui->comboBlock->setToolTip(requiredFieldToolTip);
    ui->txtFunctional->setToolTip(requiredFieldToolTip);
    ui->txtName->setToolTip(requiredFieldToolTip);
    ui->comboProject->setToolTip(requiredFieldToolTip);
    ui->labelBlock->setToolTip(requiredFieldToolTip);
    ui->labelFunctionl->setToolTip(requiredFieldToolTip);
    ui->labelName->setToolTip(requiredFieldToolTip);
    ui->labelProject->setToolTip(requiredFieldToolTip);

}

DialogAddTest::~DialogAddTest()
{
    delete ui;
}

//Здесь и будет происходить добавление в базу
void DialogAddTest::on_pushButton_clicked()
{

//    QString txtBlock = ui->comboBlock->currentText();
    int idBlock = ui->comboBlock->currentIndex() + 1;
    QString txtFunctional = ui->txtFunctional->text();
    QString txtName = ui->txtName->text();
//    QString txtProject = ui->comboProject->currentText();
    int idProject = ui->comboProject->currentIndex() + 1;

    QString txtTestlink = ui->txtTestlink->text();
    QString txtAuthor = ui->txtAuthor->text();
    QString txtDate = ui->dateEdit->text();
    QString txtComment = ui->txtComment->text();


    if ( (idBlock==0) || (txtFunctional.isEmpty()) || (txtName.isEmpty()) || (idProject==0) )
            QMessageBox::warning(this, tr("Ошибка"),tr("Не заполнено обязательное поле"));
    else
    {

        //Добавление новой записи в базу
        QSqlQuery query1;
        query1.prepare("INSERT INTO Autotests (block, functional, name, project, testlink, author, date, comment) "
                       "VALUES (:block, :functional, :name, :project, :testlink, :author, :date, :comment)");
        query1.bindValue(":block", idBlock);
        query1.bindValue(":functional", txtFunctional);
        query1.bindValue(":name", txtName);
        query1.bindValue(":project", idProject);
        query1.bindValue(":testlink", txtTestlink);
        query1.bindValue(":author", txtAuthor);
        query1.bindValue(":date", txtDate);
        query1.bindValue(":comment", txtComment);
        query1.exec();

        //Закрытие диалога
        close();


    }
}

