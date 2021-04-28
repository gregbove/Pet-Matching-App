#include "enteranimalscreengeneral.h"
#include "ui_enteranimalscreengeneral.h"

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
