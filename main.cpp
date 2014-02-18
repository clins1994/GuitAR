#include "mainmenu.h"
#include <QApplication>
#include "business.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu mm;
    mm.show();

    return a.exec();
}
