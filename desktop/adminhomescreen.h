#ifndef ADMINHOMESCREEN_H
#define ADMINHOMESCREEN_H

#include <QWidget>

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

private:
    Ui::AdminHomeScreen *ui;
};

#endif // ADMINHOMESCREEN_H
