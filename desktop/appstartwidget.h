#ifndef APPSTARTWIDGET_H
#define APPSTARTWIDGET_H

#include <QWidget>
#include <QMessageBox>

#include "../common/bnbclient.h"
#include "../common/user.h"
#include "userhomescreen.h"
#include "ownerhomescreen.h"
#include "adminhomescreen.h"
#include "createaccountscreen.h"

namespace Ui {
class AppStartWidget;
}

class AppStartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AppStartWidget(QWidget *parent = 0);
    ~AppStartWidget();

public slots:
    void loginFailed(QString err);
    void loginSucceeded(shared_ptr<BNBModel> user, UserType uType);

private slots:
    // From this screen to a different screen
    void on_loginButton_clicked();

    // From different screen back to this one
    void goToHomeScreen();

    // From this screen to a different screen
    void on_createAccountButton_clicked();

private:
    Ui::AppStartWidget *ui;
    BNBClient bnb;

    // Home Screens
    int type = 0;
    UserHomeScreen uHomeScreen;
    OwnerHomeScreen oHomeScreen;
    AdminHomeScreen aHomeScreen;
    CreateAccountScreen cAccountScreen;
};

#endif // APPSTARTWIDGET_H
