#include "enteranimalscreennew.h"
#include "ui_enteranimalscreennew.h"

EnterAnimalScreenNew::EnterAnimalScreenNew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreenNew)
{
    ui->setupUi(this);
}

EnterAnimalScreenNew::~EnterAnimalScreenNew()
{
    delete ui;
}
