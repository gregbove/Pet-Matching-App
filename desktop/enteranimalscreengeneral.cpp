#include "enteranimalscreengeneral.h"
#include "ui_enteranimalscreengeneral.h"
#include <QtSql>
#include <QSqlDatabase>

EnterAnimalScreenGeneral::EnterAnimalScreenGeneral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreenGeneral)
{
    ui->setupUi(this);


}

EnterAnimalScreenGeneral::~EnterAnimalScreenGeneral()
{
    delete ui;
}

void EnterAnimalScreenGeneral::on_backButton_clicked()
{
    emit Back();

}

void EnterAnimalScreenGeneral::on_enterButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("/home/boveg/database");

            if (!db.open())
            {

            }
            else {
            QSqlQuery q;

            QString a = ui->lineEdit->text();

            q.exec("INSERT INTO PET (id, shelterid, name) values (1, 1, \"" + a +"\")");
            }
}

void EnterAnimalScreenGeneral::setupScreen(QString a) {

    ui->title->setText("Screen for " + a + "s");


        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/boveg/database");

        if (!db.open())
        {

        }
        else {
        QSqlQuery q;

        q.exec("SELECT * FROM ANIMALATTRIBUTES WHERE ANIMAL = \"" + a + "\"");

        if (q.next()) { ui->checkBox->setText(q.value(1).toString()); }
        else { ui->checkBox->setText(""); }
        if (q.next()) { ui->checkBox_2->setText(q.value(1).toString()); }
        else { ui->checkBox_2->setText(""); }
        if (q.next()) { ui->checkBox_3->setText(q.value(1).toString()); }
        else { ui->checkBox_3->setText(""); }
        if (q.next()) { ui->checkBox_4->setText(q.value(1).toString()); }
        else { ui->checkBox_4->setText(""); }
        if (q.next()) { ui->checkBox_5->setText(q.value(1).toString()); }
        else { ui->checkBox_5->setText(""); }
        if (q.next()) { ui->checkBox_6->setText(q.value(1).toString()); }
        else { ui->checkBox_6->setText(""); }
        }
}
