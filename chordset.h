#ifndef CHORDSET_H
#define CHORDSET_H

#include <QString>
#include "chord.h"

class ChordSet
{

public:
    ChordSet();
    ChordSet(QString name);
    QString name;
    QList<Chord> chords;

    Chord nextChord();
    Chord previdousChord();
    Chord currentChord();
    QString toString() const;
    int size();
    void addBeforeCurrent(Chord chord);
    void addOnEndList(Chord chord);
    void addOnFirstList(Chord chord);
    void deleteCurrentChord();

private:
    int current;
};

QDataStream &operator<<(QDataStream &out,  const ChordSet &chordset);
QDataStream &operator>>(QDataStream &in, ChordSet &chordset);

#endif // CHORDSET_H
