#ifndef CHORD_H
#define CHORD_H

#include <QString>

class Chord
{
public:
    Chord(QString name);
    Chord();
    QString name;
    int * frets;

    void setFrets(int e, int B, int G, int D, int A, int E);
    void setFrets(QList<QString> frets);
    int getFret(int string);
};

#endif // CHORD_H
