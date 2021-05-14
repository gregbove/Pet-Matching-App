#include "appstartwidget.h"
#include "ui_appstartwidget.h"

AppStartWidget::AppStartWidget(QWidget *parent) :
    QWidget(parent),
    bnb(QString::fromStdString("http://localhost:1312")),
    ui(new Ui::AppStartWidget)
{
    ui->setupUi(this);

    connect(&bnb, &BNBClient::postLoginFailed, this, &AppStartWidget::loginFailed);
    connect(&bnb, &BNBClient::postLoginSucceeded, this, &AppStartWidget::loginSucceeded);
}

AppStartWidget::~AppStartWidget()
{
    delete ui;
}

void AppStartWidget::loginFailed(QString err)
{
    QMessageBox errMsg;
    errMsg.setText("Failed to log in: " + err);
    errMsg.exec();
}

void AppStartWidget::loginSucceeded(shared_ptr<BNBModel> user, UserType uType)
{
    switch (uType)
    {
    case PARENT:
        type = 1;
        ui->stackedWidget->addWidget(&uHomeScreen);
        connect(&uHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
        break;
    case SHELTER_OWNER:
        type = 2;
        ui->stackedWidget->addWidget(&oHomeScreen);
//        oHomeScreen.num = num;
        connect(&oHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
        break;
    case ADMINISTRATOR:
        type = 3;
        ui->stackedWidget->addWidget(&aHomeScreen);
        connect(&aHomeScreen, SIGNAL(LogOutClicked()), this, SLOT(goToHomeScreen()));
        break;
    }

    ui->stackedWidget->setCurrentIndex(1);
}

// Logging in as a User/Owner/Admin
void AppStartWidget::on_loginButton_clicked()
{
    User uLogin;
    uLogin.setUsername(ui->usernameLine->text());
    uLogin.setPassword(ui->passwordLine->text());

    bnb.postLogin(uLogin);
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
