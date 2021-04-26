#include "usersearchscreen.h"
#include "ui_usersearchscreen.h"

UserSearchScreen::UserSearchScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSearchScreen)
{
    ui->setupUi(this);
}

UserSearchScreen::~UserSearchScreen()
{
    delete ui;
}

void UserSearchScreen::on_backButton_clicked()
{
    emit Back();
}
