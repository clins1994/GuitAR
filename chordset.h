#ifndef CHORDSET_H
#define CHORDSET_

#include <QString>
#include "chord.h"

class ChordSet
{

public:
    ChordSet(QString name);
    QString name;
    QList<Chord> chords;

    Chord nextChord();
    Chord previdousChord();
    Chord currentChord();
    int size();
    void addBeforeCurrent(Chord chord);
    void addOnEndList(Chord chord);
    void addOnFirstList(Chord chord);
    void deleteCurrentChord();

private:
    int current;
};

#endif // CHORDSET_H
