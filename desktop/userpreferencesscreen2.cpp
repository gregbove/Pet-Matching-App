#include "userpreferencesscreen2.h"
#include "ui_userpreferencesscreen2.h"
#include <QtSql>
#include <QSqlDatabase>

UserPreferencesScreen2::UserPreferencesScreen2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPreferencesScreen2)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/boveg/database");

        if (!db.open())
        {

        }
}

UserPreferencesScreen2::~UserPreferencesScreen2()
{
    delete ui;
}

void UserPreferencesScreen2::on_backButton_clicked()
{
    emit Back();
}

void UserPreferencesScreen2::on_doneButton_clicked()
{
    emit Done();
}

void UserPreferencesScreen2::setType(QString a) {
    animal = a;
    ui->animalTypeLabel->setText("What type of " + animal + " fits you best?");
}

void UserPreferencesScreen2::setNames() {



    //else {
        QSqlQuery q;

        q.exec("SELECT * FROM ANIMALATTRIBUTES WHERE ANIMAL = \"" + animal + "\"");

        if (q.next()) { ui->att1->setText(q.value(1).toString()); }
        else { ui->att1->setText(""); }
        if (q.next()) { ui->att2->setText(q.value(1).toString()); }
        else { ui->att2->setText(""); }
        if (q.next()) { ui->att3->setText(q.value(1).toString()); }
        else { ui->att3->setText(""); }
        if (q.next()) { ui->att4->setText(q.value(1).toString()); }
        else { ui->att4->setText(""); }
        if (q.next()) { ui->att5->setText(q.value(1).toString()); }
        else { ui->att5->setText(""); }
        if (q.next()) { ui->att6->setText(q.value(1).toString()); }
        else { ui->att6->setText(""); }
    //}
}



void UserPreferencesScreen2::on_attImport1_sliderReleased()
{
    QString a = QString::number(ui->attImport1->value());
    ui->attnum1->setText(a);
}

void UserPreferencesScreen2::on_attImport1_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum1->setText(a);
}


//


void UserPreferencesScreen2::on_attImport2_sliderReleased()
{
    QString a = QString::number(ui->attImport2->value());
    ui->attnum2->setText(a);
}

void UserPreferencesScreen2::on_attImport2_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum2->setText(a);
}


//


void UserPreferencesScreen2::on_attImport3_sliderReleased()
{
    QString a = QString::number(ui->attImport3->value());
    ui->attnum3->setText(a);
}

void UserPreferencesScreen2::on_attImport3_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum3->setText(a);
}

// 4

void UserPreferencesScreen2::on_attImport4_sliderReleased()
{
    QString a = QString::number(ui->attImport4->value());
    ui->attnum4->setText(a);
}

void UserPreferencesScreen2::on_attImport4_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum4->setText(a);
}

//

void UserPreferencesScreen2::on_attImport5_sliderReleased()
{
    QString a = QString::number(ui->attImport5->value());
    ui->attnum5->setText(a);
}

void UserPreferencesScreen2::on_attImport5_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum5->setText(a);
}

// 6

void UserPreferencesScreen2::on_attImport6_sliderReleased()
{
    QString a = QString::number(ui->attImport6->value());
    ui->attnum6->setText(a);
}

void UserPreferencesScreen2::on_attImport6_sliderMoved(int position)
{
    QString a = QString::number(position);
    ui->attnum6->setText(a);
}


