#ifndef USERPREFERENCESSCREENTWO_H
#define USERPREFERENCESSCREENTWO_H

#include <QWidget>
#include <QGroupBox>

namespace Ui {
class UserPreferencesScreenTwo;
}

class UserPreferencesScreenTwo : public QWidget
{
    Q_OBJECT

public:
    explicit UserPreferencesScreenTwo(QWidget *parent = 0);
    ~UserPreferencesScreenTwo();

private:
    Ui::UserPreferencesScreenTwo *ui;

    QGroupBox *createSecondExclusiveGroup();
};

#endif // USERPREFERENCESSCREENTWO_H
