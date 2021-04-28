#include "userhomescreen.h"
#include "ui_userhomescreen.h"

UserHomeScreen::UserHomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserHomeScreen)
{
    ui->setupUi(this);
}

UserHomeScreen::~UserHomeScreen()
{
    delete ui;
}

void UserHomeScreen::on_homeButton_clicked()
{
    emit LogOutClicked();
}

void UserHomeScreen::on_setPreferencesButton_clicked()
{
    type = 1;
    ui->stackedWidget->addWidget(&uPreferencesScreen);
    connect(&uPreferencesScreen, SIGNAL(Back()), this, SLOT(back()));

    ui->stackedWidget->setCurrentIndex(1);
}

void UserHomeScreen::back()
{
    if (type == 1) {
            ui->stackedWidget->removeWidget(&uPreferencesScreen);
        }
    else if (type == 2) {
            ui->stackedWidget->removeWidget(&uSearchScreen);
        }
    ui->stackedWidget->setCurrentIndex(0);
}

void UserHomeScreen::on_searchButton_clicked()
{
    type = 2;
    ui->stackedWidget->addWidget(&uSearchScreen);
    connect(&uSearchScreen, SIGNAL(Back()), this, SLOT(back()));

    ui->stackedWidget->setCurrentIndex(1);
}
