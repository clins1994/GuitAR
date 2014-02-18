#include "datamanager.h"
#include "chord.h"
#include "chordset.h"
#include <QStringList>

template <class T>
QHash<QString, T> DataManager::getData(QString hashtablename)
{
    QFile file("C:/temp/" + hashtablename + ".txt");
    QHash<QString, T> hashmucholoco;
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_8);
        in >> hashmucholoco;
        file.close();
    }
    else
        qDebug() << "File " + file.fileName() + " not found";

    return hashmucholoco;
}

template <class T>
void DataManager::refreshData(QString hashtablename, QHash<QString, T> hash)
{
    QFile file("C:/temp/" + hashtablename + ".txt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);
    out << hash;
    file.flush();
    file.close();
}
