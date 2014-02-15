#ifndef CHORD_H
#define CHORD_H

#include <QList>
#include <QString>
class Chord
{
public:
    Chord(QString);
    int* getCurrentVariation();
    int* nextVariation();
    int* previousVariation();
    void addVariation(int* frets);
    void deleteCurrentVariation();
    QString name;
private:
    QList<int*> variations;
};

#endif // CHORD_H
