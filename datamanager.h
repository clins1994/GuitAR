#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QHash>
#include "chord.h"

template <class T>
class DataManager
{
public:
    DataManager();
    QHash<QString, T> getData(QString hashtablename);
    void refreshData(QString hashtablename, QHash<QString, T> hash);
};

#endif // DATAMANAGER_H
