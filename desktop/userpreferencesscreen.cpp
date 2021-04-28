#include "userpreferencesscreen.h"
#include "ui_userpreferencesscreen.h"

UserPreferencesScreen::UserPreferencesScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPreferencesScreen)
{
    ui->setupUi(this);
}

UserPreferencesScreen::~UserPreferencesScreen()
{
    delete ui;
}

void UserPreferencesScreen::on_backButton_clicked()
{
    emit Back();
}
