#include "chord.h"
#include <QStringList>

QDataStream &operator<<(QDataStream &out, const Chord &chord)
{
    out << chord.toString();
    return out;
}

QDataStream &operator>>(QDataStream &in, Chord &chord)
{
    QString str;
    in >> str;
    QList<QString> firstSplit = str.split("$");
    chord = Chord(firstSplit.at(0));
    QList<QString> variationsSplit = firstSplit.at(1).split("_");
    QList<QVarLengthArray<int>> variations;

    int sizeVariations = variationsSplit.size();
    for (int i = 0; i < sizeVariations; i++)
    {
        QVarLengthArray<int> frets;
        QList<QString> fretsSplit = variationsSplit.at(i).split(" ");
        for (int j = 0; j < 6; j++)
            frets.append(fretsSplit.at(j).toInt());

        variations.push_front(frets);
    }

    chord.setVariations(variations);
    return in;
}

Chord::Chord(QString name)
{
    this->name = name;
}

Chord::Chord()
{
    this->name = "undefined";
}

QVarLengthArray<int> Chord::getCurrentVariation()
{
    return variations.first();
}

QVarLengthArray<int> Chord::nextVariation()
{
    QVarLengthArray<int> aux = variations.first();
    variations.pop_front();
    variations.push_back(aux);
    return aux;
}

QVarLengthArray<int> Chord::previousVariation()
{
    QVarLengthArray<int> aux = variations.last();
    variations.pop_back();
    variations.push_front(aux);
    return aux;
}

void Chord::addVariation(QVarLengthArray<int> frets)
{
    variations.push_front(frets);
}

void Chord::deleteCurrentVariation()
{
    variations.pop_front();
}

void Chord::setVariations(QList<QVarLengthArray<int>> list)
{
    variations = list;
}

QString Chord::toString() const
{
    QString str = name + "$";
    int size = variations.size();
    for (int i = 0; i < size; i++)
    {
        QVarLengthArray<int> aux = variations.at(i);
        for (int j = 0; j < aux.size(); j++)
        {
            if (j != 0)
                str += " ";
            str += QString::number(aux.at(j));
        }

        if (i + 1 < size)
            str += "_";
    }

    return str;
}
