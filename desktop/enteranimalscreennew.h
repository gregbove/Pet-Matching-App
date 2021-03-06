#ifndef ENTERANIMALSCREENNEW_H
#define ENTERANIMALSCREENNEW_H

#include <QWidget>

namespace Ui {
class EnterAnimalScreenNew;
}

class EnterAnimalScreenNew : public QWidget
{
    Q_OBJECT

public:
    explicit EnterAnimalScreenNew(QWidget *parent = 0);
    ~EnterAnimalScreenNew();

signals:
    void Back();

    void Done();

private slots:
    void on_backButton_clicked();

    void on_enterButton_clicked();

private:
    Ui::EnterAnimalScreenNew *ui;
};

#endif // ENTERANIMALSCREENNEW_H
