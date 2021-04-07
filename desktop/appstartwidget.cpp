#include "appstartwidget.h"
#include "ui_appstartwidget.h"

AppStartWidget::AppStartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppStartWidget)
{
    ui->setupUi(this);
}

AppStartWidget::~AppStartWidget()
{
    delete ui;
}
