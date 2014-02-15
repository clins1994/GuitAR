#include "chord.h"
#include <QStringList>
#include <QDebug>

QDataStream &operator<<(QDataStream &out, const Chord &chord)
{
    out << chord.toString();
    return out;
}

QDataStream &operator>>(QDataStream &in, Chord &chord)
{
    QString str;
    in >> str;
    QList<QString> list1 = str.split("$");
    chord = Chord(list1.at(0));
    QList<QString> list2 = list1.at(1).split("_");
    QList<int *> variations;

    int sizeVariations = list2.size();
    for (int i = 0; i < sizeVariations; i++)
    {
        int * frets = new int[6];
        QList<QString> list3 = list2.at(i).split(" ");
        for (int j = 0; j < 6; j++)
            frets[j] = list3.at(j).toInt();

        variations.push_back(frets);
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

int* Chord::getCurrentVariation()
{
    int* aux = variations.first();
    return aux;
}

int* Chord::nextVariation()
{
    int* aux = variations.first();
    variations.pop_front();
    variations.push_back(aux);
    return aux;
}

int* Chord::previousVariation()
{
    int* aux = variations.last();
    variations.pop_back();
    variations.push_front(aux);
    return aux;
}

void Chord::addVariation(int* frets)
{
    variations.push_front(frets);
}

void Chord::deleteCurrentVariation()
{
    variations.pop_front();
}

void Chord::setVariations(QList<int *> list)
{
    variations = list;
}

QString Chord::toString() const
{
    QString str = name + "$";
    int size = variations.size();
    for (int i = 0; i < size; i++)
    {
        int* aux = variations.at(i);
        for (int j = 0; j < 6; j++)
        {
            if (j != 0)
                str += " ";
            str += QString::number(aux[j]);
        }

        if (i + 1 < size)
            str += "_";
    }

    return str;
}
