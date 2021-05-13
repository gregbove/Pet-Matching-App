#ifndef ADMINPARENTSSCREEN_H
#define ADMINPARENTSSCREEN_H

#include <QWidget>
#include "../common/bnbclient.h"

namespace Ui {
class AdminParentsScreen;
}

class AdminParentsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AdminParentsScreen(QWidget *parent = 0);
    ~AdminParentsScreen();

signals:
    void BackClicked();

private slots:
    void on_backButton_clicked();

    void GetParentsFailed(QString s);
    void GetParentsWorked(QVector<shared_ptr<Parent>> ps);

private:
    Ui::AdminParentsScreen *ui;
};

#endif // ADMINPARENTSSCREEN_H
