#include "enteranimalscreen.h"
#include "ui_enteranimalscreen.h"

EnterAnimalScreen::EnterAnimalScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterAnimalScreen)
{
    ui->setupUi(this);
    ui->listWidget->addItem("dog");
    ui->listWidget->addItem("cat");
    ui->listWidget->addItem("snake");
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
    if (type == 1) {
        ui->stackedWidget->removeWidget(&generalScreen);
    }
    if (type == 2) {
        ui->stackedWidget->removeWidget(&newScreen);
    }
     ui->stackedWidget->setCurrentIndex(0);
}

void EnterAnimalScreen::done()
{
     back();
     emit Back();
}

void EnterAnimalScreen::on_enterAnimalButton_clicked() // When enter is hit (Go to next individual screen)
{
    animalTypeS = ui->animalType->text(); // Keep track of animal type being entered
    
    // bool inDB = check_db(animalType);
    
    // if (inDB) { // Animal Type already exists in DB

        // Create general screen with the Animal type as a parameter

        // EnterAnimalScreenGeneral (Screen) - use DB for attributes

    // }
    
    // else {  // Animal Type is not in DB yet

        // Create new entry screen for the animal
        // EnterAnimalScreenNew (Screen) - Enter it in the DB
        
        // Create general screen with the animal type as a parameter
        // EnterAnimalScreenGeneral (Screen) - use DB for attributes

    // }
    
    
    /*
     *
    // OLD CODE . . .
    This was for when we hard coded the Dog/Cat screens. . . keeping it
    here for help looking at structure

    */

    if (ui->animalType->text() == "dog" || ui->animalType->text() == "cat" || ui->animalType->text() == "snake") {
        type = 1;
        generalScreen.setupScreen(ui->animalType->text());

        ui->stackedWidget->addWidget(&generalScreen);
        connect(&generalScreen, SIGNAL(Back()), this, SLOT(back()));
        connect(&generalScreen, SIGNAL(Done()), this, SLOT(done()));
    }
    else {
        type = 2;
        ui->stackedWidget->addWidget(&newScreen);
        connect(&newScreen, SIGNAL(Back()), this, SLOT(back()));
        connect(&newScreen, SIGNAL(Done()), this, SLOT(done()));
    }
    ui->stackedWidget->setCurrentIndex(1);
}

bool EnterAnimalScreen::check_db(QString animalToCheck) {

    // Check database (SQL Statement) 
    
    // Return true if animal exists in DB, false otherwise

    return true;

}



