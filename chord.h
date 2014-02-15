#ifndef CHORD_H
#define CHORD_H

#include <QList>
#include <QString>
class Chord
{
public:
    Chord(QString name);
    Chord();
    int* getCurrentVariation();
    int* nextVariation();
    int* previousVariation();
    void addVariation(int* frets);
    void deleteCurrentVariation();
    void setVariations(QList<int *> list);
    QString toString() const;
    QString name;
private:
    QList<int*> variations;
};

QDataStream &operator<<(QDataStream &out,  const Chord &chord);
QDataStream &operator>>(QDataStream &in, Chord &chord);

#endif // CHORD_H
