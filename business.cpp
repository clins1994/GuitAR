#include "business.h"
#include <QDebug>

Business::Business()
{
    //construtor
    dataManager = new DataManager();
    chordsTable = dataManagerChords->getData("Chords");
    chordSetsTable = dataManagerChordSets->getData("ChordSets");
}

Business::~Business()
{
    //destrutor
    delete dataManager;
}

//QList<QString> Business::getAllChordSetsName()
//{
//    return NULL;
//}

void Business::createChordSet(QString chordSetName)
{
}

ChordSet Business::getChordSet(QString chordSetName)
{
    return NULL;
}

void Business::deleteChordSet(QString chordSetName)
{
}

void Business::updateChordSet(QString chordSetName, ChordSet chordSet)
{
}

Chord Business::getChord(QString chordName)
{
    return NULL;
}

//QList<QString> Business::getChordsName()
//{
//    return NULL;
//}
