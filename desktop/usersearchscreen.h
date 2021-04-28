#ifndef USERSEARCHSCREEN_H
#define USERSEARCHSCREEN_H

#include <QWidget>

namespace Ui {
class UserSearchScreen;
}

class UserSearchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit UserSearchScreen(QWidget *parent = 0);
    ~UserSearchScreen();

signals:
    void Back();
private slots:
    void on_backButton_clicked();

private:
    Ui::UserSearchScreen *ui;
};

#endif // USERSEARCHSCREEN_H
