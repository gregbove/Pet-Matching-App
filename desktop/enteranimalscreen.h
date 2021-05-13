#ifndef ENTERANIMALSCREEN_H
#define ENTERANIMALSCREEN_H

#include <QWidget>
#include "enteranimalscreengeneral.h"
#include "enteranimalscreennew.h"

namespace Ui {
class EnterAnimalScreen;
}

class EnterAnimalScreen : public QWidget
{
    Q_OBJECT

public:
    explicit EnterAnimalScreen(QWidget *parent = 0);
    ~EnterAnimalScreen();

signals:
    void Back();

private slots:
    // back to owner page
    void on_backButton_clicked();

    // from next screen back to this one
    void back();

    void done();


    // goes to next entry part
    void on_enterAnimalButton_clicked();

    // checks if animal type exists in DB
    bool check_db(QString animal);

private:
    int type = 0;

    Ui::EnterAnimalScreen *ui;

    EnterAnimalScreenGeneral generalScreen;
    EnterAnimalScreenNew newScreen;
    
    QString animalTypeS;
};

#endif // ENTERANIMALSCREEN_H
