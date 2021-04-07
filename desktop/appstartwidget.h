#ifndef APPSTARTWIDGET_H
#define APPSTARTWIDGET_H

#include <QWidget>

namespace Ui {
class AppStartWidget;
}

class AppStartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AppStartWidget(QWidget *parent = 0);
    ~AppStartWidget();

private:
    Ui::AppStartWidget *ui;
};

#endif // APPSTARTWIDGET_H
