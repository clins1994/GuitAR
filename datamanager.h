#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QHash>
#include "chord.h"

class DataManager
{
public:
    template <class T>
    QHash<QString, T> getData(QString hashtablename);

    template <class T>
    void refreshData(QString hashtablename, QHash<QString, T> hash);
};

#endif // DATAMANAGER_H
