#include "enteranimalscreennew.h"
#include "ui_enteranimalscreennew.h"

#include <QtSql>
#include <QSqlDatabase>

EnterAnimalScreenNew::EnterAnimalScreenNew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreenNew)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("/home/boveg/database");

            if (!db.open())
            {

            }
            else {
            QSqlQuery q;

            q.exec("SELECT DISTINCT ATTRIBUTE FROM ANIMALATTRIBUTES");

            while (q.next()) {
                        QString ans = "";
                        ans += q.value(0).toString();
                        ui->listWidget->addItem(ans);
                    }
            }
}

EnterAnimalScreenNew::~EnterAnimalScreenNew()
{
    delete ui;
}

void EnterAnimalScreenNew::on_backButton_clicked()
{
    emit Back();
}

void EnterAnimalScreenNew::on_enterButton_clicked()
{

}
