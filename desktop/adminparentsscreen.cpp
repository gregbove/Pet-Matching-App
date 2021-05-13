#include "adminparentsscreen.h"
#include "ui_adminparentsscreen.h"
#include <QtSql>
#include <QSqlDatabase>

#include <iostream>
#include <memory>
#include <QUrl>
#include <QCoreApplication>
#include <QString>
#include <QVector>

#include "../common/user.h"
#include "../common/parent.h"
#include "../common/shelterowner.h"
#include "../common/administrator.h"
#include "../common/bnbclient.h"


AdminParentsScreen::AdminParentsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminParentsScreen)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName("/home/boveg/database");

                if (!db.open())
                {

                }
                else {
                QSqlQuery q;

                q.exec("SELECT * FROM PARENTS");

                while (q.next()) {
                            QString ans = "";
                            ans += q.value(1).toString();
                            ui->listWidget->addItem(ans);
                        }
                }


    BNBClient c(QUrl("http://localhost:1312"));

    connect(&c, SIGNAL(getParentsFailed(QString)), this, SLOT(GetParentsFailed(QString)));
    connect(&c, SIGNAL(getParentsSucceeded(QVector<shared_ptr<Parent> >)), this, SLOT(GetParentsWorked(QVector<shared_ptr<Parent> >)));

    QObject::connect(&c, &BNBClient::getParentsFailed, [&] (QString s) {
        ui->listWidget->addItem(s);
    });

    QObject::connect(&c, &BNBClient::getParentsSucceeded, [&] (QVector<shared_ptr<Parent>> ps) {
        for (shared_ptr<Parent> p : ps)
        {
            ui->listWidget->addItem(p->getName());
        }
    });

    c.getParents();
}

AdminParentsScreen::~AdminParentsScreen()
{
    delete ui;
}

void AdminParentsScreen::on_backButton_clicked()
{
    emit BackClicked();
}

void AdminParentsScreen::GetParentsFailed(QString s) {
    ui->listWidget->addItem("Failed");
}

void AdminParentsScreen::GetParentsWorked(QVector<shared_ptr<Parent> > ps) {
    ui->listWidget->addItem("Worked");
}

