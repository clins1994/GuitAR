#include "Chord.hpp"
#include <cstdio>

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

int Chord::getFret(int string)
{
    return frets[string];
}
