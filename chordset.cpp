#include "chordset.h"
#include <QStringList>
#include <QDebug>
#include <QVarLengthArray>

QDataStream &operator<<(QDataStream &out, const ChordSet &chordSet)
{
    out << chordSet.toString();
    return out;
}

QDataStream &operator>>(QDataStream &in, ChordSet &chordSet)
{
    QString str;
    in >> str;
    QList<QString> firstSplit = str.split("#");
    chordSet = ChordSet(firstSplit.at(0));
    QList<QString> chordsStrSplit = firstSplit.at(1).split("|");
    QList<Chord> chordsList;

    int size_chords_str_list = chordsStrSplit.size();
    for (int i = 0; i < size_chords_str_list; i++)
    {
        QList<QString> chordSplit = chordsStrSplit.at(i).split("$");
        Chord * mychord = new Chord(chordSplit.at(0));
        QList<QString> variationsSplit = chordSplit.at(1).split("_");
        QList<QVarLengthArray<int>> variations;
        int size_variations = variationsSplit.size();
        for (int j = 0; j < size_variations; j++)
        {
            QVarLengthArray<int> frets;
            QList<QString> variationSplit = variationsSplit.at(j).split(" ");
            for (int k = 0; k < 6; k++)
                frets.append(variationSplit.at(k).toInt());
            variations.append(frets);
        }
        mychord->setVariations(variations);
        chordsList.append(*mychord);
    }

    chordSet.chords = chordsList;

    return in;
}

ChordSet::ChordSet(QString name)
{
    this->name = name;
}

ChordSet::ChordSet()
{
    this->name = "undefined";
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

Chord ChordSet::previousChord()
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

QString ChordSet::toString() const
{
    QString str = name + "#";
    int size = chords.size();
    for (int i = 0; i < size; i++)
    {
        str += chords.at(i).toString();

        if (i + 1 < size)
            str += "|";
    }

    return str;
}
