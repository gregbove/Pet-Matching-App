#ifndef ENTERANIMALSCREENGENERAL_H
#define ENTERANIMALSCREENGENERAL_H

#include <QWidget>

namespace Ui {
class EnterAnimalScreenGeneral;
}

class EnterAnimalScreenGeneral : public QWidget
{
    Q_OBJECT

public:
    explicit EnterAnimalScreenGeneral(QWidget *parent = 0);
    ~EnterAnimalScreenGeneral();

private:
    Ui::EnterAnimalScreenGeneral *ui;
};

#endif // ENTERANIMALSCREENGENERAL_H
