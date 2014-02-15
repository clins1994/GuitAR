#include "chordset.h"

ChordSet::ChordSet(QString name)
{
    this->name = name;
}

int ChordSet::size()
{
    return chords.size();
}

Chord ChordSet::nextChord()
{
    current++;
    if (current == chords.size())
        current = 0;
    return currentChord();
}

Chord ChordSet::previdousChord()
{
    current--;
    if (current == -1)
        current = chords.size() - 1;
    return currentChord();
}

Chord ChordSet::currentChord()
{
    return chords.at(current);
}

void ChordSet::addBeforeCurrent(Chord chord)
{
    chords.insert(current, chord);
}

void ChordSet::addOnEndList(Chord chord)
{
    chords.append(chord);
}

void ChordSet::addOnFirstList(Chord chord)
{
    chords.insert(0, chord);
}

void ChordSet::deleteCurrentChord()
{
    chords.removeAt(current);
}
