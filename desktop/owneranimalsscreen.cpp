#include "owneranimalsscreen.h"
#include "ui_owneranimalsscreen.h"
#include <QtSql>
#include <QSqlDatabase>

OwnerAnimalsScreen::OwnerAnimalsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OwnerAnimalsScreen)
{
    ui->setupUi(this);
}

OwnerAnimalsScreen::~OwnerAnimalsScreen()
{
    delete ui;
}

void OwnerAnimalsScreen::on_deleteButton_clicked()
{
    const QString& s = ui->listWidget->currentItem()->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/boveg/database");

    if (!db.open())
    {

    }
    else {
        QSqlQuery q;

        q.exec("DELETE FROM PET WHERE PET.NAME = \"" + s + "\"");
    }

    set();

}

void OwnerAnimalsScreen::on_backButton_clicked()
{
    emit Back();
}

void OwnerAnimalsScreen::set() {
    ui->listWidget->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/boveg/database");

    if (!db.open())
    {

    }
    else {
        QSqlQuery q;

        q.exec("SELECT * FROM PET WHERE SHELTERID = " + QString::number(num));

        while (q.next()) {
            QString ans = "";
            ans += q.value(2).toString();
            ui->listWidget->addItem(ans);
        }
    }
    ui->label->setText(QString::number(num));
}
