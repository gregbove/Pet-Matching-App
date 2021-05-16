#ifndef CREATEACCOUNTSCREEN_H
#define CREATEACCOUNTSCREEN_H

#include "constants.h"

#include <QWidget>
#include <QMessageBox>
#include <string.h>
#include <iostream>

#include "../common/bnbclient.h"

namespace Ui {
class CreateAccountScreen;
}

class CreateAccountScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAccountScreen(QWidget *parent = 0);
    ~CreateAccountScreen();

signals:
    void HomeClicked();

public slots:
    void createFailed(QString err);
    void createSucceeded();

private slots:
    void on_createAccountButton_clicked();

    void on_homeButton_clicked();

private:
    Ui::CreateAccountScreen *ui;
    BNBClient bnb;

    QString pass;
    QString user;
    std::string type;
};

#endif // CREATEACCOUNTSCREEN_H
