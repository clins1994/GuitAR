#include <QString>

#ifndef CHORD_HPP
#define CHORD_HPP

class Chord
{
    public:
        Chord(QString name);
        QString name;
        int * frets;

        void setFrets(int e, int B, int G, int D, int A, int E);
        int getFret(int string);
};

#endif
