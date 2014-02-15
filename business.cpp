#include "business.h"

Business::Business()
{
    //construtor
    dataManagerChords = new DataManager();
    dataManagerChordSets = new DataManager();
    //chordsTable = dataManagerChords->getData();
    //chordSetsTable = dataManagerChordSets->getData;
}

Business::~Business()
{
    //destrutor
    delete dataManagerChords;
    delete dataManagerChordSets;
}

//QList<QString> Business::getAllChordSetsName()
//{
//    return NULL;
//}

void Business::createChordSet (QString chordSetName)
{
}

ChordSet Business::getChordSet (QString chordSetName)
{
    return NULL;
}

void Business::deleteChordSet (QString chordSetName)
{
}

void Business::updateChordSet (QString chordSetName, ChordSet chordSet)
{
}

Chord Business::getChord (QString chordName)
{
    return NULL;
}

//QList<QString> Business::getChordsName()
//{
//    return NULL;
//}
