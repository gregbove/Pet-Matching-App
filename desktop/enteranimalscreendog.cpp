#include "enteranimalscreendog.h"
#include "ui_enteranimalscreendog.h"

EnterAnimalScreenDog::EnterAnimalScreenDog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreenDog)
{
    ui->setupUi(this);
}

EnterAnimalScreenDog::~EnterAnimalScreenDog()
{
    delete ui;
}

// GO FROM THIS PAGE TO PREVIOUS PAGE
void EnterAnimalScreenDog::on_backButton_clicked()
{
    emit Back();
}

// GO FROM THIS PAGE TO TWO PAGES PRIOR
void EnterAnimalScreenDog::on_doneButton_clicked()
{
    // Enter in the SQL Database what you have from the entry
    emit Done();
}
