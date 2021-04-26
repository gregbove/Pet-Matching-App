#ifndef USERPREFERENCESSCREEN_H
#define USERPREFERENCESSCREEN_H

#include <QWidget>

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

private slots:
    void on_backButton_clicked();

private:
    Ui::UserPreferencesScreen *ui;
};

#endif // USERPREFERENCESSCREEN_H
