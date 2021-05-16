#include "createaccountscreen.h"
#include "ui_createaccountscreen.h"

CreateAccountScreen::CreateAccountScreen(QWidget *parent) :
    QWidget(parent),
    bnb(QString::fromStdString(BNB_SERVER_URL)),
    ui(new Ui::CreateAccountScreen)
{
    ui->setupUi(this);

    connect(&bnb, &BNBClient::postParentFailed,
            this, &CreateAccountScreen::createFailed);
    connect(&bnb, &BNBClient::postParentSucceeded,
            this, &CreateAccountScreen::createSucceeded);
    connect(&bnb, &BNBClient::postAdministratorFailed,
            this, &CreateAccountScreen::createFailed);
    connect(&bnb, &BNBClient::postAdministratorSucceeded,
            this, &CreateAccountScreen::createSucceeded);
    connect(&bnb, &BNBClient::postShelterOwnerFailed,
            this, &CreateAccountScreen::createFailed);
    connect(&bnb, &BNBClient::postShelterOwnerSucceeded,
            this, &CreateAccountScreen::createSucceeded);
}

CreateAccountScreen::~CreateAccountScreen()
{
    delete ui;
}

void CreateAccountScreen::createFailed(QString err)
{
    QMessageBox errMsg;
    errMsg.setText("Failed to create user: " + err);
    errMsg.exec();
}

void CreateAccountScreen::createSucceeded()
{
    QMessageBox msg;
    msg.setText("User was created successfully!");
    msg.exec();

    emit HomeClicked();
}

void CreateAccountScreen::on_createAccountButton_clicked()
{   
    User u;
    u.setUsername(ui->newUsernameLine->text());
    u.setPassword(ui->newPasswordLine->text());

    // TODO: "user" doesnt match our "parent" convention

    if (ui->User->isEnabled()) {
        Parent p;
        p.setUser(u);
        // TODO: set name from somewhere

        bnb.postParent(p);
    }
    else if (ui->Owner->isEnabled()) {
        ShelterOwner o;
        o.setUser(u);
        // TODO: set shelter & name from somewhere

        bnb.postShelterOwner(o);
    }
    else if (ui->Admin->isEnabled()) {
        Administrator a;
        a.setUser(u);
        // TODO: set isSuperAdmin from somewhere

        bnb.postAdministrator(a);
    }
}

void CreateAccountScreen::on_homeButton_clicked()
{
    emit HomeClicked();
}
