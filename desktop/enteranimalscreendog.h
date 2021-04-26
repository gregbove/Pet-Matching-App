#ifndef ENTERANIMALSCREENDOG_H
#define ENTERANIMALSCREENDOG_H

#include <QWidget>

namespace Ui {
class EnterAnimalScreenDog;
}

class EnterAnimalScreenDog : public QWidget
{
    Q_OBJECT

public:
    explicit EnterAnimalScreenDog(QWidget *parent = 0);
    ~EnterAnimalScreenDog();

signals:
    void Back();
    void Done();

private slots:
    // back to owner page
    void on_backButton_clicked();


    void on_doneButton_clicked();

private:
    Ui::EnterAnimalScreenDog *ui;
};

#endif // ENTERANIMALSCREENDOG_H
