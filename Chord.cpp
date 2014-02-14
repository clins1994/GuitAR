#include "chord.h"
#include <QList>

Chord::Chord()
{
    this->name = "";
    this->frets = new int[6];
}

Chord::Chord(QString name)
{
    this->name = name;
    this->frets = new int[6];
}

void Chord::setFrets(int e, int B, int G, int D, int A, int E)
{
    frets[0] = e;
    frets[1] = B;
    frets[2] = G;
    frets[3] = D;
    frets[4] = A;
    frets[5] = E;
}

void Chord::setFrets(QList<QString> frets_list)
{
    for (int i = 0; i < frets_list.size(); i++)
        if (frets_list.at(i) == "X")
            frets[i] = -1;
        else
            frets[i] = frets_list.at(i).toInt();
}

int Chord::getFret(int string)
{
    return frets[string];
}
