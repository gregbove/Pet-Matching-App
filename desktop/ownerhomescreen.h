#ifndef OWNERHOMESCREEN_H
#define OWNERHOMESCREEN_H

#include <QWidget>
#include <enteranimalscreen.h>

namespace Ui {
class OwnerHomeScreen;
}

class OwnerHomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OwnerHomeScreen(QWidget *parent = 0);
    ~OwnerHomeScreen();

signals:
    void LogOutClicked();
    // void AnimalEntryClicked();

private slots:
    // back to signin page
    void on_homeButton_clicked();

    // from next screen back to this one
    void back();

    // goes to Entry screen
    void on_animalEntryButton_clicked();

    void on_viewAllAnimals_clicked();

private:
    int type = 0;
    Ui::OwnerHomeScreen *ui;

    EnterAnimalScreen eAnimalScreen;
};

#endif // OWNERHOMESCREEN_H
