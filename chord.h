#ifndef CHORD_H
#define CHORD_H

#include <QList>
#include <QString>
#include <QVarLengthArray>

class Chord
{
public:
    Chord(QString name);
    Chord();
    QVarLengthArray<int> getCurrentVariation();
    QVarLengthArray<int> nextVariation();
    QVarLengthArray<int> previousVariation();
    void addVariation(QVarLengthArray<int> frets);
    void deleteCurrentVariation();
    void setVariations(QList<QVarLengthArray<int>> list);
    QString toString() const;
    QString name;

private:
    QList<QVarLengthArray<int> > variations;
};

QDataStream &operator<<(QDataStream &out,  const Chord &chord);
QDataStream &operator>>(QDataStream &in, Chord &chord);

#endif // CHORD_H
