#ifndef ADMINHOMESCREEN_H
#define ADMINHOMESCREEN_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include "adminparentsscreen.h"

namespace Ui {
class AdminHomeScreen;
}

class AdminHomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AdminHomeScreen(QWidget *parent = 0);
    ~AdminHomeScreen();

signals:
    void LogOutClicked();

private slots:
    void on_homeButton_clicked();

    void goToAdminHomeScreen();

    void on_parentsButton_clicked();

private:
    Ui::AdminHomeScreen *ui;

    AdminParentsScreen aParentsScreen;
};

#endif // ADMINHOMESCREEN_H
