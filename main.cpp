#include "mainmenu.h"
#include <QApplication>
#include <QtXml>
#include <QHash>
#include <QDebug>
#include "chord.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu mm;
    mm.show();

    return a.exec();
}
