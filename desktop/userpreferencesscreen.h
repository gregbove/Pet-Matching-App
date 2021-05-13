#ifndef USERPREFERENCESSCREEN_H
#define USERPREFERENCESSCREEN_H

#include <QWidget>
#include "userpreferencesscreen2.h"

namespace Ui {
class UserPreferencesScreen;
}

class UserPreferencesScreen : public QWidget
{
    Q_OBJECT

public:
    explicit UserPreferencesScreen(QWidget *parent = 0);
    ~UserPreferencesScreen();

signals:
    void Back();

    void Done();

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

    void back();

    void done();

    void on_animalList_clicked(const QModelIndex &index);

private:
    Ui::UserPreferencesScreen *ui;

    UserPreferencesScreen2 uPreferencesScreen2;
};

#endif // USERPREFERENCESSCREEN_H
