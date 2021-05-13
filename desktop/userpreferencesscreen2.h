#ifndef USERPREFERENCESSCREEN2_H
#define USERPREFERENCESSCREEN2_H

#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>

namespace Ui {
class UserPreferencesScreen2;
}

class UserPreferencesScreen2 : public QWidget
{
    Q_OBJECT

public:
    explicit UserPreferencesScreen2(QWidget *parent = 0);
    ~UserPreferencesScreen2();
    
    QString animal;

    void setType(QString a);

    void setNames();

signals:
    void Back();

    void Done();

private slots:
    void on_backButton_clicked();

    void on_doneButton_clicked();

    void on_attImport1_sliderReleased();

    void on_attImport1_sliderMoved(int position);

    void on_attImport2_sliderReleased();

    void on_attImport2_sliderMoved(int position);

    void on_attImport3_sliderReleased();

    void on_attImport3_sliderMoved(int position);

    void on_attImport4_sliderReleased();

    void on_attImport4_sliderMoved(int position);

    void on_attImport5_sliderReleased();

    void on_attImport5_sliderMoved(int position);

    void on_attImport6_sliderReleased();

    void on_attImport6_sliderMoved(int position);

private:
    Ui::UserPreferencesScreen2 *ui;
};

#endif // USERPREFERENCESSCREEN2_H
