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

QList<QString> Business::getAllChordSetsName()
{

}

void Business::createChordSet (QString chordSetName)
{

}

ChordSet Business::getChordSet (QString chordSetName)
{

}

void Business::deleteChordSet (QString chordSetName)
{

}

void Business::updateChordSet (QString chordSetName, ChordSet chordSet)
{

}

Chord Business::getChord (QString chordName)
{

}

QList<QString> Business::getChordsName()
{

}
