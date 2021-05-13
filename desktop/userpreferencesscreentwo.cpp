#include "userpreferencesscreentwo.h"
#include "ui_userpreferencesscreentwo.h"

UserPreferencesScreenTwo::UserPreferencesScreenTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPreferencesScreenTwo)
{
    ui->setupUi(this);
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createFirstExclusiveGroup(), 0, 0);
    grid->addWidget(createSecondExclusiveGroup(), 1, 0);
}

UserPreferencesScreenTwo::~UserPreferencesScreenTwo()
{
    delete ui;
}
