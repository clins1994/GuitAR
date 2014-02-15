#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QtXml>
#include <QGLWidget>
#include "training_metaio.h"

class Chord;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    // Dictionary
    this->chordScene = new QGraphicsScene();
    ui->chordGraphicsView->setScene(this->chordScene);
    guitarArm = new QPixmap(":/assets/guitar_arm.png");
    chordScene->addPixmap(*guitarArm);
    mainChords << "C" << "C#" << "D" << "D#" << "E" <<  "F" << "F#" << "G" << "G#" << "A" << "A#" << "B";
    ui->normalChordsComboBox->addItems(mainChords);
    file = new QFile(":/assets/Chords.xml");
    file->open(QIODevice::ReadOnly);
    document.setContent(file);
    rootElement = document.documentElement();
    ui->chordsModificatorsComboBox->addItems(findChords(ui->normalChordsComboBox->currentText()));

    // Training
    QGLWidget *glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    ui->trainigGraphicsView->setViewport(glWidget);
    ui->trainigGraphicsView->setFrameShape(QFrame::NoFrame);
    ui->trainigGraphicsView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->trainigGraphicsView->setScene(new TrainingMetaio(ui->trainigGraphicsView->size().width(), ui->trainigGraphicsView->size().height()));
}

MainMenu::~MainMenu()
{
    delete ui;
    delete chordScene;
    delete guitarArm;
}

QList<QString> MainMenu::findChords(QString mainChord)
{
    QDomElement chord;
    QList<QString> list;
    list << "M";

    for (QDomNode node = rootElement.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        chord = node.childNodes().at(0).toElement();
        if (chord.text() == mainChord)
        {
            chord = node.childNodes().at(1).toElement();
            if (chord.text() != "" && chord.text() != list.at(list.size() - 1))
                list << chord.text();
        }
    }

    return list;
}

QList<QString> MainMenu::getFrets(QString mainChord, QString modifier)
{
    QDomElement chord, chordModifier;
    QList<QString> frets;
    for (QDomNode node = rootElement.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        chord = node.childNodes().at(0).toElement();
        if (chord.text() == mainChord)
        {
            chordModifier = node.childNodes().at(1).toElement();
            if (chordModifier.text() == modifier || (modifier == "M" && chordModifier.text() == ""))
            {
                frets = node.childNodes().at(2).toElement().text().split(" ");
                break;
            }
        }
    }

    return frets;
}

void MainMenu::updateGraphics()
{
    chordScene->clear();
    chordScene->addPixmap(*guitarArm);
    ui->chordGraphicsView->setTransform(QTransform());

    if (ui->normalChordsRadioButton->isEnabled())
    {
        QString mainChord = ui->normalChordsComboBox->currentText();
        QString modifier = ui->chordsModificatorsComboBox->currentText();
        QList<QString> frets = getFrets(mainChord, modifier);

        Braco * braco = new Braco(475, 10);
        Point * point = NULL;
        qDebug() << mainChord << " " << modifier << " " << frets;
        for (int i = 0; i < frets.size(); i++)
        {
            if (frets.at(i) != "0" && frets.at(i) != "X")
            {
                point = braco->getPoint(i, frets.at(i).toInt());
                chordScene->addEllipse(point->X, point->Y, 9, 9, QPen(Qt::NoPen), QBrush(QColor(255, 153, 0)));
            }
        }
        delete point;
        delete braco;
    }
}

void MainMenu::on_normalChordsComboBox_activated(const QString &arg1)
{
    QList<QString> chordsFound = findChords(ui->normalChordsComboBox->currentText());
    ui->chordsModificatorsComboBox->clear();
    ui->chordsModificatorsComboBox->addItems(chordsFound);
    updateGraphics();
}

void MainMenu::on_chordsModificatorsComboBox_activated(const QString &arg1)
{
    updateGraphics();
}

void MainMenu::on_splitChordsComboBox_activated(const QString &arg1)
{
    updateGraphics();
}

void MainMenu::on_startTrainingButton_clicked()
{
    ui->pages->setCurrentWidget(ui->training);
}

void MainMenu::on_consultChordButton_clicked()
{
    ui->pages->setCurrentWidget(ui->consultChord);
    updateGraphics();
}

void MainMenu::on_listMakerButton_clicked()
{
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainMenu::on_backToMenuConsultChord_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainMenu::on_backToMenuSelectList_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainMenu::on_backToMenuCreateList_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainMenu::on_backToMenuTraining_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainMenu::on_normalChordsRadioButton_clicked()
{
    ui->normalChordsComboBox->setEnabled(true);
    ui->chordsModificatorsComboBox->setEnabled(true);
    ui->splitChordsComboBox->setEnabled(false);
}

void MainMenu::on_splitChordsRadioButton_clicked()
{
    ui->splitChordsComboBox->setEnabled(true);
    ui->normalChordsComboBox->setEnabled(false);
    ui->chordsModificatorsComboBox->setEnabled(false);
}
