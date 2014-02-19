#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QGLWidget>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include "training_metaio.h"

class Chord;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    businessManager = new Business();

    // Dictionary
    this->chordScene = new QGraphicsScene();
    ui->chordGraphicsView->setScene(this->chordScene);
    guitarArm = new QPixmap(":/assets/guitar_arm.png");
    chordScene->addPixmap(*guitarArm);
    mainChords.append(businessManager->getMainChordsNames());
    ui->normalChordsComboBox->addItems(mainChords);
    ui->chordsModificatorsComboBox->addItems(findChords(ui->normalChordsComboBox->currentText()));

    // Training
    QGLWidget *glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    ui->trainigGraphicsView->setViewport(glWidget);
    ui->trainigGraphicsView->setFrameShape(QFrame::NoFrame);
    ui->trainigGraphicsView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->trainigGraphicsView->setScene(new TrainingMetaio(ui->trainigGraphicsView->width(), ui->trainigGraphicsView->height()));

    // Lists
    updateListsList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete businessManager;
    delete chordScene;
    delete guitarArm;
}

QList<QString> MainWindow::findChords(QString mainChord)
{
    return businessManager->getChordModificators(mainChord);
}

QVarLengthArray<int> MainWindow::getFrets(QString mainChord, QString modifier)
{
    QString chord_name = mainChord;
    if (modifier != "M")
        chord_name += " " + modifier;

    return businessManager->getChord(chord_name).getCurrentVariation();
}

void MainWindow::updateGraphics()
{
    chordScene->clear();
    chordScene->addPixmap(*guitarArm);
    ui->chordGraphicsView->setTransform(QTransform());

    if (ui->normalChordsRadioButton->isEnabled())
    {
        QString mainChord = ui->normalChordsComboBox->currentText();
        QString modifier = ui->chordsModificatorsComboBox->currentText();
        QVarLengthArray<int> frets = getFrets(mainChord, modifier);

        Braco * braco = new Braco(475, 10);
        Point * point = NULL;

        for (int i = 0; i < frets.size(); i++)
        {
            std::cout << frets.at(i) << " ";
            if (frets.at(i) != 0 && frets.at(i) != -1)
            {
                point = braco->getPoint(i, frets.at(i));
                chordScene->addEllipse(point->X, point->Y, 9, 9, QPen(Qt::NoPen), QBrush(QColor(255, 153, 0)));
            }
        }
        std::cout << std::endl;
        delete point;
        delete braco;
    }
}

void MainWindow::on_normalChordsComboBox_activated(const QString &arg1)
{
    QList<QString> chordsFound = findChords(ui->normalChordsComboBox->currentText());
    ui->chordsModificatorsComboBox->clear();
    ui->chordsModificatorsComboBox->addItems(chordsFound);
    updateGraphics();
}

void MainWindow::on_chordsModificatorsComboBox_activated(const QString &arg1)
{
    updateGraphics();
}

void MainWindow::on_splitChordsComboBox_activated(const QString &arg1)
{
    updateGraphics();
}

void MainWindow::on_changeChordVariationUpButton_clicked()
{
    QString chord_name = ui->normalChordsComboBox->currentText();
    QString modificator = ui->chordsModificatorsComboBox->currentText();
    if (modificator != "M")
        chord_name += " " + modificator;
    businessManager->setChordPreviousVariation(chord_name);
    updateGraphics();
}

void MainWindow::on_changeChordVariationDownButton_clicked()
{
    QString chord_name = ui->normalChordsComboBox->currentText();
    QString modificator = ui->chordsModificatorsComboBox->currentText();
    if (modificator != "M")
        chord_name += " " + modificator;
    businessManager->setChordNextVariation(chord_name);
    updateGraphics();
}

void MainWindow::updateListsList()
{
//    ui->listsList->clear();
    ui->listsList->addItems(businessManager->getAllChordSetsNames());
}

void MainWindow::on_startTrainingButton_clicked()
{
    ui->pages->setCurrentWidget(ui->training);
}

void MainWindow::on_consultChordButton_clicked()
{
    ui->pages->setCurrentWidget(ui->consultChord);
    updateGraphics();
}

void MainWindow::on_listMakerButton_clicked()
{
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainWindow::on_backToMenuConsultChord_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainWindow::on_backToMenuSelectList_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainWindow::on_backToMenuCreateList_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainWindow::on_backToMenuTraining_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainWindow::on_normalChordsRadioButton_clicked()
{
    ui->normalChordsComboBox->setEnabled(true);
    ui->chordsModificatorsComboBox->setEnabled(true);
    ui->splitChordsComboBox->setEnabled(false);
}

void MainWindow::on_splitChordsRadioButton_clicked()
{
    ui->splitChordsComboBox->setEnabled(true);
    ui->normalChordsComboBox->setEnabled(false);
    ui->chordsModificatorsComboBox->setEnabled(false);
}

void MainWindow::on_createNewListButton_clicked()
{
    ui->pages->setCurrentWidget(ui->creatList);
}

void MainWindow::on_createListButton_clicked()
{
    if (ui->newListText->text().isEmpty())
        QMessageBox::warning(this, "Warning", "Nome nao pode ser em branco!");
    else
        businessManager->createChordSet(ui->newListText->text());
    updateListsList();
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainWindow::on_deleteListButton_clicked()
{
    businessManager->deleteChordSet(ui->listsList->currentItem()->text());
    updateListsList();
}
