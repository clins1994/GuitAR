#include "business.h"
#include <QDebug>
#include <QStringList>

Business::Business()
{
    dataManager = DataManager();
    chordsTable = dataManager.getData<Chord>("Chords");
    chordSetsTable = dataManager.getData<ChordSet>("ChordSets");
}

Business::~Business()
{
}

void Business::refreshChordsHash()
{
    chordsTable = dataManager.getData<Chord>("Chords");
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
    chordSetsTable.take(chordSetName);
    chordSetsTable.insert(chordSetName, chordSet);
}

void Business::renameChordSet(QString oldName, QString newName)
{
    ChordSet chordSet = chordSetsTable.take(oldName);
    chordSet.name = newName;
    chordSetsTable.insert(chordSet.name, chordSet);
}

void Business::addChordToChordSet(QString chordSetName, QString chordName)
{
    ChordSet chordSet = chordSetsTable.take(chordSetName);
    chordSet.addOnEndList(chordsTable.value(chordName));
    chordSetsTable.insert(chordSet.name, chordSet);
}

QList<QString> Business::getChordSetChordsNames(QString chordSetName)
{
    QList<QString> chordSetChordsNames;
    const QList<Chord> chords = chordSetsTable.value(chordSetName).chords;
    int size = chords.size();
    for (int i = 0; i < size; i++)
        chordSetChordsNames.append(chords.at(i).name);

    return chordSetChordsNames;
}

Chord Business::getChord(QString chordName)
{
    QList<QString> list = chordName.split(" ");
    if (list.at(1) != "M")
        return chordsTable.value(chordName);
    else
        return chordsTable.value(list.at(0));
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
    Chord chord;
    QList<QString> chord_name = chordName.split(" ");
    if (chord_name.at(1) != "M")
        chord = chordsTable.take(chordName);
    else
        chord = chordsTable.take(chordName.at(0));
    chord.nextVariation();
    chordsTable.insert(chord.name, chord);
}

void Business::setChordPreviousVariation(QString chordName)
{
    Chord chord;
    QList<QString> chord_name = chordName.split(" ");
    if (chord_name.at(1) != "M")
        chord = chordsTable.take(chordName);
    else
        chord = chordsTable.take(chordName.at(0));
    chord.previousVariation();
    chordsTable.insert(chord.name, chord);
}

void Business::storeData()
{
//    dataManager.refreshData<Chord>("Chords", chordsTable);
    dataManager.refreshData<ChordSet>("ChordSets", chordSetsTable);
}

QString Business::getDataBasePath()
{
    return dataManager.basePath;
}
