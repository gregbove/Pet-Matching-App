#include "enteranimalscreen.h"
#include "ui_enteranimalscreen.h"

EnterAnimalScreen::EnterAnimalScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreen)
{
    ui->setupUi(this);
}

EnterAnimalScreen::~EnterAnimalScreen()
{
    delete ui;
}

void EnterAnimalScreen::on_backButton_clicked()
{
    emit Back();
}

void EnterAnimalScreen::back()
{
    /*if (type == 1) {
        ui->stackedWidget->removeWidget(&dogScreen);
    }
    if (type == 2) {
        ui->stackedWidget->removeWidget(&catScreen);
    }*/
     ui->stackedWidget->setCurrentIndex(0);
}

void EnterAnimalScreen::done()
{
     back();
     emit Back();
}

void EnterAnimalScreen::on_enterAnimalButton_clicked() // When enter is hit (Go to next individual screen)
{
    animalType = ui->animalType->text(); // Keep track of animal type being entered
    
    bool inDB = check_db(animalType);
    
    if (inDB) { // Animal Type already exists in DB

        // Create general screen with the Animal type as a parameter

        // EnterAnimalScreenGeneral (Screen) - use DB for attributes

    }
    
    else {  // Animal Type is not in DB yet

        // Create new entry screen for the animal
        // EnterAnimalScreenNew (Screen) - Enter it in the DB
        
        // Create general screen with the animal type as a parameter
        // EnterAnimalScreenGeneral (Screen) - use DB for attributes

    }
    
    
    /*
     *
    // OLD CODE . . .
    This was for when we hard coded the Dog/Cat screens. . . keeping it
    here for help looking at structure

    if (ui->animalType->text() == "Dog") {
        type = 1;
        ui->stackedWidget->addWidget(&dogScreen);
        connect(&dogScreen, SIGNAL(Back()), this, SLOT(back()));
        connect(&dogScreen, SIGNAL(Done()), this, SLOT(done()));
    }

    else if (ui->animalType->text() == "Cat") {
        type = 2;
        ui->stackedWidget->addWidget(&catScreen);
        connect(&catScreen, SIGNAL(Back()), this, SLOT(back()));
        connect(&catScreen, SIGNAL(Done()), this, SLOT(done()));
    }

    else {
        ui->animalType->setText("Please enter a valid animal type");
        return;
    }
    
    */

    
    
    ui->stackedWidget->setCurrentIndex(1);
}

bool EnterAnimalScreen::check_db(QString animalToCheck) {

    // Check database (SQL Statement) 
    
    // Return true if animal exists in DB, false otherwise

    return true;

}



