#ifndef CREATEACCOUNTSCREEN_H
#define CREATEACCOUNTSCREEN_H

#include <QWidget>
#include <string.h>
#include <iostream>

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

private slots:
    void on_createAccountButton_clicked();

    void on_homeButton_clicked();

private:
    Ui::CreateAccountScreen *ui;
    QString pass;
    QString user;
    std::string type;
};

#endif // CREATEACCOUNTSCREEN_H
