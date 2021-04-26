#ifndef ENTERANIMALSCREENCAT_H
#define ENTERANIMALSCREENCAT_H

#include <QWidget>

namespace Ui {
class EnterAnimalScreenCat;
}

class EnterAnimalScreenCat : public QWidget
{
    Q_OBJECT

public:
    explicit EnterAnimalScreenCat(QWidget *parent = 0);
    ~EnterAnimalScreenCat();

signals:
    void Back();
    void Done();

private slots:
    void on_backButton_clicked();

    void on_doneButton_clicked();

private:
    Ui::EnterAnimalScreenCat *ui;
};

#endif // ENTERANIMALSCREENCAT_H
