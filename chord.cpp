#include "chord.h"

Chord::Chord(QString name)
{
    this->name = name;
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
