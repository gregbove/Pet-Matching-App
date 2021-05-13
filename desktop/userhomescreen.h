#ifndef USERHOMESCREEN_H
#define USERHOMESCREEN_H

#include <QWidget>
#include <userpreferencesscreen.h>
#include <usersearchscreen.h>

namespace Ui {
class UserHomeScreen;
}

class UserHomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit UserHomeScreen(QWidget *parent = 0);
    ~UserHomeScreen();

signals:
    void LogOutClicked();

private slots:
    void on_homeButton_clicked();

    void on_setPreferencesButton_clicked();

    void back();

    void on_searchButton_clicked();

private:
    int type = 0;
    Ui::UserHomeScreen *ui;
    UserPreferencesScreen uPreferencesScreen;
    UserSearchScreen uSearchScreen;
};

#endif // USERHOMESCREEN_H
