#include "adminhomescreen.h"
#include "ui_adminhomescreen.h"

AdminHomeScreen::AdminHomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminHomeScreen)
{
    ui->setupUi(this);
}

AdminHomeScreen::~AdminHomeScreen()
{
    delete ui;
}

void AdminHomeScreen::on_homeButton_clicked()
{
    emit LogOutClicked();
}


