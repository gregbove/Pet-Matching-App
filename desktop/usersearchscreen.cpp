#include "usersearchscreen.h"
#include "ui_usersearchscreen.h"
#include <QtSql>
#include <QSqlDatabase>

UserSearchScreen::UserSearchScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSearchScreen)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/boveg/database");

    if (!db.open())
    {
        ui->answerList->addItem("Didn't open");
    }

    else {
        QSqlQuery q;

        q.exec("SELECT * FROM PET");

        while (q.next()) {
            QString ans = "";
            ans += q.value(2).toString() + "\n";
            ans += "At Shelter: " +  q.value(1).toString();
            ui->answerList->addItem(ans);
        }
    }
}

UserSearchScreen::~UserSearchScreen()
{
    delete ui;
}

void UserSearchScreen::on_backButton_clicked()
{
    emit Back();
}
