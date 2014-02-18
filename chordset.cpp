#include "chordset.h"
#include <QStringList>

QDataStream &operator<<(QDataStream &out, const ChordSet &chordset)
{
    out << chordset.toString();
    return out;
}

QDataStream &operator>>(QDataStream &in, ChordSet &chordset)
{
    QString str;
    in >> str;
    QList<QString> info = str.split("#");
    chordset = ChordSet(info.at(0));
    QList<QString> chords_str_list = info.at(1).split("|");
    QList<Chord> chords_list;

    int size_chords_str_list = chords_str_list.size();
    for (int i = 0; i < size_chords_str_list; i++)
    {
        QList<QString> infochord = chords_str_list.at(i).split("$");
        Chord * mychord = new Chord(infochord.at(0));
        QList<QString> variationslist = infochord.at(1).split("_");
        QList<int *> variations;
        int sizevariations = variationslist.size();
        for (int j = 0; j < sizevariations; j++)
        {
            int * frets = new int[6];
            QList<QString> thisvariation = variationslist.at(j).split(" ");
            for (int k = 0; k < 6; k++)
                frets[k] = thisvariation.at(k).toInt();
            variations.append(frets);
        }
        mychord->setVariations(variations);
        chords_list.append(*mychord);
    }

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
