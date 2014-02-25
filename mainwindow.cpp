#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGLWidget>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include "training_metaio.h"

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
    updateGraphics();

    // Training
    QGLWidget *glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    ui->trainigGraphicsView->setViewport(glWidget);
    ui->trainigGraphicsView->setFrameShape(QFrame::NoFrame);
    ui->trainigGraphicsView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->trainingMainChordComboBox->addItems(businessManager->getMainChordsNames());
    updateTrainingChord();
    trainingWidget = new TrainingMetaio(ui->trainigGraphicsView->width(), ui->trainigGraphicsView->height(), businessManager);
    ui->trainigGraphicsView->setScene(trainingWidget);
    connect(this, SIGNAL(updateMetaioChord(QString)), trainingWidget, SLOT(update(QString)));

    // Training ChordSet
    QGLWidget *glWidgetChordSet = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    ui->trainigChordSetGraphicsView->setViewport(glWidgetChordSet);
    ui->trainigChordSetGraphicsView->setFrameShape(QFrame::NoFrame);
    ui->trainigChordSetGraphicsView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->trainigChordSetGraphicsView->setScene(trainingWidget);
    connect(this, SIGNAL(updateMetaioChordSet(int)), trainingWidget, SLOT(update(int)));

    // Lists
    this->editListChordScene = new QGraphicsScene();
    ui->editChordGraphicsView->setScene(this->editListChordScene);
    guitarArm = new QPixmap(":/assets/guitar_arm.png");
    editListChordScene->addPixmap(*guitarArm);
    ui->editNormalChordsComboBox->addItems(businessManager->getMainChordsNames());
    ui->editChordsModificatorsComboBox->addItems(findChords(ui->editNormalChordsComboBox->currentText()));
    updateListsList();
    editListUpdateGraphics();
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
    return businessManager->getChord(mainChord + " " + modifier).getCurrentVariation();
}

void MainWindow::updateGraphics()
{
    chordScene->clear();
    chordScene->addPixmap(*guitarArm);
    ui->chordGraphicsView->setTransform(QTransform());

    QString mainChord = ui->normalChordsComboBox->currentText();
    QString modifier = ui->chordsModificatorsComboBox->currentText();
    QVarLengthArray<int> frets = getFrets(mainChord, modifier);

    Braco * braco = new Braco(648, 6, 144);
    Point * point = NULL;

    for (int i = 0; i < frets.size(); i++)
        if (frets.at(i) != 0 && frets.at(i) != -1)
        {
            point = braco->getPoint(i, frets.at(i));
            chordScene->addEllipse(point->X, point->Y, 9, 9, QPen(Qt::NoPen), QBrush(QColor(255, 153, 0)));
        }

    delete point;
    delete braco;
}

void MainWindow::editListUpdateGraphics()
{
    editListChordScene->clear();
    editListChordScene->addPixmap(*guitarArm);
    ui->editChordGraphicsView->setTransform(QTransform());

    QString mainChord = ui->editNormalChordsComboBox->currentText();
    QString modifier = ui->editChordsModificatorsComboBox->currentText();
    QVarLengthArray<int> frets = getFrets(mainChord, modifier);

    Braco * braco = new Braco(648, 6, 144);
    Point * point = NULL;

    for (int i = 0; i < frets.size(); i++)
        if (frets.at(i) != 0 && frets.at(i) != -1)
        {
            point = braco->getPoint(i, frets.at(i));
            editListChordScene->addEllipse(point->X, point->Y, 9, 9, QPen(Qt::NoPen), QBrush(QColor(255, 153, 0)));
        }

    delete point;
    delete braco;
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

void MainWindow::on_changeChordVariationUpButton_clicked()
{
    businessManager->setChordPreviousVariation(ui->normalChordsComboBox->currentText() + " " + ui->chordsModificatorsComboBox->currentText());
    updateGraphics();
}

void MainWindow::on_changeChordVariationDownButton_clicked()
{
    businessManager->setChordNextVariation(ui->normalChordsComboBox->currentText() + " " + ui->chordsModificatorsComboBox->currentText());
    updateGraphics();
}

void MainWindow::updateListsList()
{
    ui->listsList->clear();
    ui->listsList->addItems(businessManager->getAllChordSetsNames());
}

void MainWindow::updateTrainingChord()
{
    ui->trainingChordModificatorComboBox->addItems(businessManager->getChordModificators(ui->trainingMainChordComboBox->currentText()));
}

void MainWindow::on_startTrainingButton_clicked()
{
    ui->pages->setCurrentWidget(ui->training);
    if (!trainingWidget->isActive())
        trainingWidget->resume();
}

void MainWindow::on_consultChordButton_clicked()
{
    businessManager->refreshChordsHash();
    ui->pages->setCurrentWidget(ui->consultChord);
    updateGraphics();
}

void MainWindow::on_listMakerButton_clicked()
{
    businessManager->refreshChordsHash();
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
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainWindow::on_backToMenuTraining_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
    trainingWidget->pause();
}

void MainWindow::on_backToMenuEditList_clicked()
{
    saveChordSet();
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainWindow::on_createNewListButton_clicked()
{
    ui->pages->setCurrentWidget(ui->creatList);
    ui->newListText->clear();
    ui->newListText->setFocus();
}

void MainWindow::on_createListButton_clicked()
{
    if (ui->newListText->text().isEmpty())
        QMessageBox::warning(this, "Warning", "Nome nao pode ser em branco!");
    else if (businessManager->findChordSet(ui->newListText->text()))
        QMessageBox::warning(this, "Warning", "Ja existe uma lista com esse nome!");
    else
    {
        businessManager->createChordSet(ui->newListText->text());
        updateListsList();
        ui->pages->setCurrentWidget(ui->selectList);
    }
}

void MainWindow::on_deleteListButton_clicked()
{
    businessManager->deleteChordSet(ui->listsList->currentItem()->text());
    updateListsList();
}

void MainWindow::on_editListButton_clicked()
{
    if (ui->listsList->count() > 0 && ui->listsList->currentRow() >= 0)
    {
        QString chordSetName = ui->listsList->currentItem()->text();
        ui->pages->setCurrentWidget(ui->editList);

        editListAuxChordSet = businessManager->getChordSet(chordSetName);

        ui->listNameLabel->setText(chordSetName);
        ui->editListsList->clear();

        for (int i = 0; i < editListAuxChordSet.chords.size(); i++)
        {
            if (editListAuxChordSet.chords.at(i).name.size() == 1)
                ui->editListsList->addItem(editListAuxChordSet.chords.at(i).name + " M");
            else
                ui->editListsList->addItem(editListAuxChordSet.chords.at(i).name);
        }
    }
}

void MainWindow::on_trainBtn_clicked()
{
//    if (trainingWidget->isActive())
//        trainingWidget->pause();
//    if (!trainingChordSetWidget->isActive())
//        trainingChordSetWidget->resume();

    if (saveChordSet())
    {
        businessManager->refreshChordsHash();
        ui->pages->setCurrentWidget(ui->trainingChordSet);
        QString chordSetName = ui->listNameLabel->text();
        trainingWidget->setTraining(chordSetName);

        ui->trainingChordSetList->clear();
        QList<QString> chordsNames = businessManager->getChordSetChordsNames(chordSetName);
        for (int i = 0; i < chordsNames.size(); i++)
        {
            ui->trainingChordSetList->addItem(chordsNames.at(i));
        }

        ui->trainingChordSetLabel->setText(chordSetName);
        ui->trainingChordSetList->setCurrentRow(0);
        ui->trainingChordSetList->setFocus();
    }
}

void MainWindow::on_addChordToListButton_clicked()
{
    QString chordName = ui->editNormalChordsComboBox->currentText() + " " + ui->editChordsModificatorsComboBox->currentText();
    editListAuxChordSet.addOnEndList(businessManager->getChord(chordName));
    ui->editListsList->addItem(chordName);
    ui->editListsList->setCurrentRow(ui->editListsList->count() - 1);
}

void MainWindow::on_removeChordFromListButton_clicked()
{
    editListAuxChordSet.chords.takeAt(ui->editListsList->currentRow());
    ui->editListsList->takeItem(ui->editListsList->currentRow());
}

bool MainWindow::saveChordSet()
{
    if (ui->editListsList->count() > 0)
    {
        businessManager->updateChordSet(editListAuxChordSet.name, editListAuxChordSet);
        updateListsList();
        businessManager->storeData();
        return true;
    }
    return false;
}

void MainWindow::on_trainingMainChordComboBox_activated(const QString &arg1)
{
    updateTrainingChord();
    emit updateMetaioChord(ui->trainingMainChordComboBox->currentText() + " " + ui->trainingChordModificatorComboBox->currentText());
}

void MainWindow::on_trainingChordModificatorComboBox_activated(const QString &arg1)
{
    emit updateMetaioChord(ui->trainingMainChordComboBox->currentText() + " " + ui->trainingChordModificatorComboBox->currentText());
}

void MainWindow::on_trainingPreviousVariation_clicked()
{
    businessManager->setChordPreviousVariation(ui->trainingMainChordComboBox->currentText() + " " + ui->trainingChordModificatorComboBox->currentText());
}

void MainWindow::on_trainingNextVariation_clicked()
{
    businessManager->setChordNextVariation(ui->trainingMainChordComboBox->currentText() + " " + ui->trainingChordModificatorComboBox->currentText());
}

void MainWindow::on_editNormalChordsComboBox_activated(const QString &arg1)
{
    ui->editChordsModificatorsComboBox->clear();
    ui->editChordsModificatorsComboBox->addItems(businessManager->getChordModificators(ui->editNormalChordsComboBox->currentText()));
    editListUpdateGraphics();
}

void MainWindow::on_editChordsModificatorsComboBox_activated(const QString &arg1)
{
    editListUpdateGraphics();
}

void MainWindow::on_editListPreviousChordVariation_clicked()
{
    businessManager->setChordPreviousVariation(ui->editNormalChordsComboBox->currentText() + " " + ui->editChordsModificatorsComboBox->currentText());
    editListUpdateGraphics();
}

void MainWindow::on_editListNextChordVariation_clicked()
{
    businessManager->setChordNextVariation(ui->editNormalChordsComboBox->currentText() + " " + ui->editChordsModificatorsComboBox->currentText());
    editListUpdateGraphics();
}

void MainWindow::editUpdateFromChord(QVarLengthArray<int> frets)
{
    editListChordScene->clear();
    editListChordScene->addPixmap(*guitarArm);
    ui->editChordGraphicsView->setTransform(QTransform());

    Braco * braco = new Braco(648, 6, 144);
    Point * point = NULL;

    for (int i = 0; i < frets.size(); i++)
        if (frets.at(i) != 0 && frets.at(i) != -1)
        {
            point = braco->getPoint(i, frets.at(i));
            editListChordScene->addEllipse(point->X, point->Y, 9, 9, QPen(Qt::NoPen), QBrush(QColor(255, 153, 0)));
        }

    delete point;
    delete braco;

}

void MainWindow::on_backToMenuTrainingChordSet_clicked()
{
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainWindow::on_trainingChordSetList_currentRowChanged(int currentRow)
{
    emit updateMetaioChordSet(currentRow);
}
