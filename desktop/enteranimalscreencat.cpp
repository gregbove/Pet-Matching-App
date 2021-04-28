#include "enteranimalscreencat.h"
#include "ui_enteranimalscreencat.h"

EnterAnimalScreenCat::EnterAnimalScreenCat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreenCat)
{
    ui->setupUi(this);
}

EnterAnimalScreenCat::~EnterAnimalScreenCat()
{
    delete ui;
}

void EnterAnimalScreenCat::on_backButton_clicked()
{
    emit Back();
}

void EnterAnimalScreenCat::on_doneButton_clicked()
{
    emit Done();
}
