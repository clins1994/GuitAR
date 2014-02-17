#ifndef BUSINESS_H
#define BUSINESS_H

#include <QList>
#include <QHash>
#include <QString>
#include "chord.h"
#include "chordset.h"
#include "datamanager.h"

using namespace std;


class Business
{
    public:
        Business();
        virtual ~Business();
        QList<QString> getAllChordSetsName();
        void createChordSet (QString chordSetName);
        ChordSet getChordSet (QString chordSetName);
        void deleteChordSet (QString chordSetName);
        void updateChordSet (QString chordSetName, ChordSet chordSet);
        Chord getChord (QString chordName);
        QList<QString> getChordsName();

    private:
        QHash<QString, Chord> chordsTable;
        QHash<QString, ChordSet> chordSetsTable;
        DataManager * dataManagerChords;
        DataManager * dataManagerChordSets;
};

#endif // BUSINES_H