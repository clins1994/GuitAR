#include "business.h"
#include <QDebug>

Business::Business()
{
    //construtor
    dataManager = new DataManager();
    chordsTable = dataManager->getData<Chord>("Chords");
    chordSetsTable = dataManager->getData<ChordSet>("ChordSets");
}

Business::~Business()
{
    //destrutor
    delete dataManager;
}

QList<QString> Business::getAllChordSetsNames()
{
    QList<QString> allChordSetsNames;
    QHash<QString, ChordSet>::iterator i;
    for (i = chordSetsTable.begin(); i != chordSetsTable.end(); i++)
        allChordSetsNames.append(i.key());

    return allChordSetsNames;
}

void Business::createChordSet(QString chordSetName)
{
    ChordSet chordSet(chordSetName);
    chordSetsTable.insert(chordSetName, chordSet);
}

void Business::createChordSet(QString chordSetName, ChordSet chordSet)
{
    chordSetsTable.insert(chordSetName, chordSet);
}

ChordSet Business::getChordSet(QString chordSetName)
{
    return chordSetsTable.value(chordSetName);
}

void Business::deleteChordSet(QString chordSetName)
{
    chordSetsTable.remove(chordSetName);
}

void Business::updateChordSet(QString chordSetName, ChordSet chordSet)
{
    chordSetsTable.insert(chordSetName, chordSet);
}

Chord Business::getChord(QString chordName)
{
    return chordsTable.value(chordName);
}

QList<QString> Business::getChordsNames()
{
    QList<QString> allChordsNames;
    QHash<QString, Chord>::iterator i;
    for (i = chordsTable.begin(); i != chordsTable.end(); i++)
        allChordsNames.append(i.key());

    return allChordsNames;
}

QList<QString> Business::getMainChordsNames()
{
    QList<QString> mainChordsNames;
    QHash<QString, Chord>::iterator i;
    for (i = chordsTable.begin(); i != chordsTable.end(); i++)
        if (!mainChordsNames.contains(i.value().name.split(" ").at(0)))
            mainChordsNames.append(i.value().name.split(" ").at(0));

    qSort(mainChordsNames);
    return mainChordsNames;
}

QList<QString> Business::getChordModificators(QString mainChord)
{
    QList<QString> chordModificators;
    QList<QString> allChordsNames = getChordsNames();
    int size = allChordsNames.size();
    for (int i = 0; i < size; i++)
    {
        QList<QString> list = allChordsNames.at(i).split(" ");
        if (mainChord == list.at(0) && (list.size() > 1))
            chordModificators.append(allChordsNames.at(i).split(" ").at(1));
    }
    qSort(chordModificators);
    chordModificators.push_front("M");
    return chordModificators;
}

void Business::setChordNextVariation(QString chordName)
{
    qDebug() << "LOL";
    Chord chord = chordsTable.take(chordName);
    chord.nextVariation();
    chordsTable.insert(chord.name, chord);
    qDebug() << "LOL";
}

void Business::setChordPreviousVariation(QString chordName)
{
    Chord chord = chordsTable.take(chordName);
    chord.previousVariation();
    chordsTable.insert(chord.name, chord);
}

void Business::storeData()
{
    dataManager->refreshData<Chord>("Chords", chordsTable);
    dataManager->refreshData<ChordSet>("ChordSet", chordSetsTable);
}
