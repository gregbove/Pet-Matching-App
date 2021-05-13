#include "userpreferencesscreen.h"
#include "ui_userpreferencesscreen.h"
#include <QtSql>
#include <QSqlDatabase>

UserPreferencesScreen::UserPreferencesScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPreferencesScreen)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/boveg/database");

    if (!db.open())
    {
        ui->animalList->addItem("Didn't open");
    }

    else {
        QSqlQuery q;

        q.exec("SELECT DISTINCT ANIMAL FROM ANIMALATTRIBUTES");

        while (q.next()) {
            QString ans = "";
            ans += q.value(0).toString() + "\n";
            ui->animalList->addItem(ans);
        }
    }
}

UserPreferencesScreen::~UserPreferencesScreen()
{
    delete ui;
}

void UserPreferencesScreen::on_backButton_clicked()
{
    emit Back();
}

void UserPreferencesScreen::on_nextButton_clicked()
{
    QString animalToCheck = ui->animalType->text();

    // check if animal is in DB

    bool inDB;

    if (animalToCheck == "dog" || animalToCheck == "cat" || animalToCheck == "snake") {
        ui->stackedWidget->addWidget(&uPreferencesScreen2); 
        uPreferencesScreen2.setType(animalToCheck);
        uPreferencesScreen2.setNames();
        connect(&uPreferencesScreen2, SIGNAL(Back()), this, SLOT(back()));
        connect(&uPreferencesScreen2, SIGNAL(Done()), this, SLOT(done()));

        ui->stackedWidget->setCurrentIndex(1);
    }

    else {
        // Nothing
    }

}

void UserPreferencesScreen::back()
{
    ui->stackedWidget->removeWidget(&uPreferencesScreen2);
    ui->stackedWidget->setCurrentIndex(0);
}

void UserPreferencesScreen::done()
{
    ui->stackedWidget->removeWidget(&uPreferencesScreen2);
    ui->stackedWidget->setCurrentIndex(0);
    emit Done();
}

void UserPreferencesScreen::on_animalList_clicked(const QModelIndex &index)
{
    QListWidgetItem* curItm = ui->animalList->item(index.row());
    QString a = curItm->text();

    // Remove the space
    int pos = a.length() - 1;
    a = a.left(pos);


    ui->animalType->setText(a);
}
