#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->chordScene = new QGraphicsScene();
    ui->chordGraphicsView->setScene(this->chordScene);
    chordScene->addPixmap(*guitarArm);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::updateGraphics()
{
    chordScene->addPixmap(*guitarArm);
    ui->chordGraphicsView->setTransform(QTransform());
}

void MainMenu::on_normalChordsComboBox_currentIndexChanged(const QString &arg1)
{
    updateGraphics();
}

void MainMenu::on_chordsModificatorsComboBox_currentIndexChanged(const QString &arg1)
{
    updateGraphics();
}

void MainMenu::on_splitChordsComboBox_currentIndexChanged(const QString &arg1)
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
}

void MainMenu::on_listMakerButton_clicked()
{
    ui->pages->setCurrentWidget(ui->selectList);
}

void MainMenu::on_beatMakerButton_clicked()
{
    ui->pages->setCurrentWidget(ui->selectBeat);
}

void MainMenu::on_backToMenuConsultChord_clicked()
{
    ui->pages->setCurrentWidget(ui->mainMenu);
}

void MainMenu::on_backToMenuSelectBeat_clicked()
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

void MainMenu::on_backToMenuCreateBeat_clicked()
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
