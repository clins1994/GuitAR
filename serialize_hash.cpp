#include <QFile>
#include <QtXml>
#include <QHash>
#include <QDebug>
#include "chord.h"

void write()
{

    QFile file(":/assets/Chords.xml");
    file.open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(&file);
    QDomNode root = doc.documentElement();

    QHash<QString, Chord> hash;

    for (QDomNode node = root.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        QString name = node.childNodes().at(0).toElement().text();
        if (name.isEmpty())
            continue;

        if (!node.childNodes().at(1).toElement().text().isEmpty())
            name += " " + node.childNodes().at(1).toElement().text();

        QList<QString> frets_list = node.childNodes().at(2).toElement().text().split(" ");
        int * frets = new int[6];
        for (int i = 0; i < frets_list.size(); i++)
            if (frets_list.at(i) == "X")
                frets[i] = -1;
            else
                frets[i] = frets_list.at(i).toInt();

        if (hash.contains(name))
        {
            Chord * chord = &hash.take(name);
            chord->addVariation(frets);
            hash.insert(name, *chord);
        }
        else
        {
            Chord * chord = new Chord(name);
            chord->addVariation(frets);
            hash.insert(name, *chord);
        }
    }

    QFile fileOut("C:/temp/hash.txt");
    fileOut.open(QIODevice::WriteOnly);
    QDataStream out(&fileOut);
    out.setVersion(QDataStream::Qt_4_8);
    out << hash;
    fileOut.flush();
    fileOut.close();
}

void read()
{

    QHash<QString, Chord> hashmucholoco;
    QFile fileIn("C:/temp/hash.txt");
    fileIn.open(QIODevice::ReadOnly);
    QDataStream in(&fileIn);
    in.setVersion(QDataStream::Qt_4_8);
    in >> hashmucholoco;
    fileIn.close();

    QHash<QString, Chord>::iterator i;
    for (i = hashmucholoco.begin(); i != hashmucholoco.end(); i++)
    {
        Chord aux = i.value();
        qDebug() << aux.toString();
    }

}
