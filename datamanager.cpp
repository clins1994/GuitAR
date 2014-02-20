#include "datamanager.h"
#include "chord.h"
#include "chordset.h"
#include <QStringList>
#include <QDesktopServices>
#include <QDir>
#include <QDebug>

inline DataManager::DataManager()
{
    basePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "\\guitAR";
    QDir dir(basePath);
    if (!dir.exists())
        dir.mkpath(".");
    basePath += "\\";

    QFile chords(":/assets/Chords.guitAR");
    chords.copy(basePath + "Chords.guitAR");
    QDir ra(basePath + "ra");
    if (!ra.exists())
    {
        ra.mkdir(".");
        QDir ra_assets(":/assets/ra");
        QFileInfoList list = ra_assets.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            QFile::copy(fileInfo.filePath(), basePath + "ra\\" + fileInfo.fileName());
        }
    }
}

template <class T>
QHash<QString, T> DataManager::getData(QString hashtablename)
{
    QFile file(basePath + hashtablename + ".guitAR");
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
    QFile file(basePath + hashtablename + ".guitAR");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_8);
    out << hash;
    file.flush();
    file.close();
}
