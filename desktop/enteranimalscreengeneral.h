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

    QString theAnimal;

    void setupScreen(QString a);

signals:
    void Back();

    void Done();

private slots:
    void on_backButton_clicked();

    void on_enterButton_clicked();

private:
    Ui::EnterAnimalScreenGeneral *ui;
};

#endif // ENTERANIMALSCREENGENERAL_H
