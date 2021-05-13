#ifndef OWNERANIMALSSCREEN_H
#define OWNERANIMALSSCREEN_H

#include <QWidget>

namespace Ui {
class OwnerAnimalsScreen;
}

class OwnerAnimalsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit OwnerAnimalsScreen(QWidget *parent = 0);
    ~OwnerAnimalsScreen();

    int num = 0;

    void set();

signals:
    void Back();

private slots:
    void on_deleteButton_clicked();

    void on_backButton_clicked();

private:
    Ui::OwnerAnimalsScreen *ui;
};

#endif // OWNERANIMALSSCREEN_H
