#ifndef BUSINESS_H
#define BUSINESS_H

#include <QList>
#include <QHash>
#include <QString>
#include "chord.h"
#include "chordset.h"
#include "datamanager.h"
#include "datamanager.cpp"

using namespace std;


class Business
{
    public:
        Business();
        ~Business();

        // ChordSets
        QList<QString> getAllChordSetsNames();
        void createChordSet(QString chordSetName);
        void createChordSet(QString chordSetName, ChordSet chordSet);
        ChordSet getChordSet(QString chordSetName);
        void deleteChordSet(QString chordSetName);
        void updateChordSet(QString chordSetName, ChordSet chordsNames);
        void renameChordSet(QString oldName, QString newName);
        void addChordToChordSet(QString chordSetName, QString chordName);
        QList<QString> getChordSetChordsNames(QString chordSetName);

        // Chords
        void refreshChordsHash();
        Chord getChord (QString chordName);
        QList<QString> getChordsNames();
        QList<QString> getMainChordsNames();
        QList<QString> getChordModificators(QString mainChord);
        void setChordNextVariation(QString chordName);
        void setChordPreviousVariation(QString chordName);
        void storeData();

        QString getDataBasePath();

        ChordSet editListAuxChordSet;
        QVarLengthArray<int> getFretsFromAuxChord(int index);

    private:
        QHash<QString, Chord> chordsTable;
        QHash<QString, ChordSet> chordSetsTable;
        DataManager dataManager;
};

#endif // BUSINES_H
