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

void AdminHomeScreen::on_parentsButton_clicked()
{
    ui->stackedWidget->addWidget(&aParentsScreen);
    connect(&aParentsScreen, SIGNAL(BackClicked()), this, SLOT(goToAdminHomeScreen()));
    ui->stackedWidget->setCurrentIndex(1);
}

// Returning from a page to the home screen
void AdminHomeScreen::goToAdminHomeScreen()
{
    ui->stackedWidget->removeWidget(&aParentsScreen);

    ui->stackedWidget->setCurrentIndex(0);
}
