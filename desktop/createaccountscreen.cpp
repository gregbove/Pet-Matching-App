#include "createaccountscreen.h"
#include "ui_createaccountscreen.h"

CreateAccountScreen::CreateAccountScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateAccountScreen)
{
    ui->setupUi(this);
}

CreateAccountScreen::~CreateAccountScreen()
{
    delete ui;
}

void CreateAccountScreen::on_createAccountButton_clicked()
{
    // Send message to create new database entry

    if (ui->User->isEnabled()) {
        type = "User";
    }
    else if (ui->Owner->isEnabled()) {
        type = "Owner";
    }
    else if (ui->Admin->isEnabled()) {
        type = "Admin";
    }
    user = ui->newUsernameLine->text();
    pass = ui->newPasswordLine->text();

}

void CreateAccountScreen::on_homeButton_clicked()
{
    emit HomeClicked();
}
