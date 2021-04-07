#include "appstartwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppStartWidget w;
    w.show();

    return a.exec();
}
