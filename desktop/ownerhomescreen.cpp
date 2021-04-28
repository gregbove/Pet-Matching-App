#include "ownerhomescreen.h"
#include "ui_ownerhomescreen.h"

OwnerHomeScreen::OwnerHomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OwnerHomeScreen)
{
    ui->setupUi(this);
}

OwnerHomeScreen::~OwnerHomeScreen()
{
    delete ui;
}

void OwnerHomeScreen::on_homeButton_clicked()
{
    emit LogOutClicked();
}

void OwnerHomeScreen::back()
{
    if (type == 1) {
        ui->stackedWidget->removeWidget(&eAnimalScreen);
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void OwnerHomeScreen::on_animalEntryButton_clicked()
{
    type = 1;
    ui->stackedWidget->addWidget(&eAnimalScreen);
    connect(&eAnimalScreen, SIGNAL(Back()), this, SLOT(back()));

    ui->stackedWidget->setCurrentIndex(1);
}

void OwnerHomeScreen::on_viewAllAnimals_clicked()
{

}
