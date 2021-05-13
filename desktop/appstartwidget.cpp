#include "appstartwidget.h"
#include "ui_appstartwidget.h"

AppStartWidget::AppStartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppStartWidget)
{
    ui->setupUi(this);
}

AppStartWidget::~AppStartWidget()
{
    delete ui;
}

// Logging in as a User/Owner/Admin
void AppStartWidget::on_loginButton_clicked()
{
    if (ui->usernameLine->text() == "User") {
        type = 1;
        ui->stackedWidget->addWidget(&uHomeScreen);
        connect(&uHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
    }

    else if (ui->usernameLine->text() == "Owner") {
        QString s = ui->passwordLine->text();
        bool ok;
        int num = s.toInt(&ok);
        if (!ok) {
            // conversion failed
        } else {
            type = 2;
            ui->stackedWidget->addWidget(&oHomeScreen);
            oHomeScreen.num = num;
            connect(&oHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
        }
    }

    else if (ui->usernameLine->text() == "Admin") {
        type = 3;
        ui->stackedWidget->addWidget(&aHomeScreen);
        connect(&aHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
    }

    ui->stackedWidget->setCurrentIndex(1);

}

// Returning from a page to the home screen
void AppStartWidget::goToHomeScreen()
{
    if (type == 1) {
         ui->stackedWidget->removeWidget(&uHomeScreen);
    }
    else if (type == 2) {
         ui->stackedWidget->removeWidget(&oHomeScreen);
    }
    else if (type == 3) {
         ui->stackedWidget->removeWidget(&aHomeScreen);
    }
    else if (type == 4) {
         ui->stackedWidget->removeWidget(&cAccountScreen);
    }

    ui->stackedWidget->setCurrentIndex(0);
}

// Going to the "Create an Account" Screen
void AppStartWidget::on_createAccountButton_clicked()
{
    type = 4;
    ui->stackedWidget->addWidget(&cAccountScreen);
    connect(&cAccountScreen, SIGNAL(HomeClicked()), this, SLOT(goToHomeScreen()));
    ui->stackedWidget->setCurrentIndex(1);
}
