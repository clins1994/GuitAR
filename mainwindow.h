#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <cmath>
#include <QtXml>
#include "business.h"
#include "training_metaio.h"

// Includes sharps
#define NUMBER_OF_CHORDS 12

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startTrainingButton_clicked();

    void on_consultChordButton_clicked();

    void on_listMakerButton_clicked();

    void on_backToMenuConsultChord_clicked();

    void on_backToMenuSelectList_clicked();

    void on_backToMenuCreateList_clicked();

    void on_normalChordsComboBox_activated(const QString &arg1);

    void on_chordsModificatorsComboBox_activated(const QString &arg1);

    void on_backToMenuTraining_clicked();

    void on_createNewListButton_clicked();

    void on_createListButton_clicked();

    void on_changeChordVariationUpButton_clicked();

    void on_changeChordVariationDownButton_clicked();

    void on_deleteListButton_clicked();

    void on_editListButton_clicked();

    void on_backToMenuEditList_clicked();

    void on_addChordToListButton_clicked();

    void on_removeChordFromListButton_clicked();

    void on_trainingMainChordComboBox_activated(const QString &arg1);

    void on_trainingPreviousVariation_clicked();

    void on_trainingNextVariation_clicked();

    void on_editNormalChordsComboBox_activated(const QString &arg1);

    void on_editChordsModificatorsComboBox_activated(const QString &arg1);

    void on_editListPreviousChordVariation_clicked();

    void on_editListNextChordVariation_clicked();

    void on_trainingChordModificatorComboBox_activated(const QString &arg1);

    void on_backToMenuTrainingChordSet_clicked();

    void on_trainBtn_clicked();

    void on_trainingChordSetList_currentRowChanged(int currentRow);

signals:
    void updateMetaioChord(QString chord);
    void updateMetaioChordSet(int index);

private:
    // Training
    TrainingMetaio *trainingWidget;
    void startTutorial();
    void updateTrainingChord();

    // Training ChordSet
    TrainingMetaio *trainingChordSetWidget;

    // Dictionary
    void updateGraphics();
    QList<QString> findChords(QString mainChord);
    QVarLengthArray<int> getFrets(QString mainChord, QString modifier);

    // Lists
    ChordSet editListAuxChordSet;
    void updateListsList();
    void editListUpdateGraphics();
    bool saveChordSet();
    void editUpdateFromChord(QVarLengthArray<int> frets);

    Ui::MainWindow *ui;
    Business *businessManager;
    QGraphicsScene *chordScene;
    QGraphicsScene *editListChordScene;
    const QPixmap *guitarArm;
    QList<QString> mainChords;

    struct Point {
        double X;
        double Y;
        Point(double x, double y): X(x), Y(y) {}
    };

    struct Braco {
        double trastePosition[17];
        double casaPosition[17];
        double cordaSize;
        double cordaDistance;
        double start;

        Braco(double cordaSizeIn, double cordaDistanceIn, double startIn):
            cordaSize(cordaSizeIn), cordaDistance(cordaDistanceIn), start(startIn) {
            int trastes = 17;
            int casas = 17;
            for (int i = 0; i < trastes; i++)
                trastePosition[i] = getDistanceTraste(cordaSize, i);

            for (int i = 1; i < casas; i++)
                casaPosition[i] = (trastePosition[i] + trastePosition[i - 1]) / 2;
        }

        Point * getPoint(int corda, int casa) {
            Point * point = new Point(27 + casaPosition[casa], start - (casaPosition[casa] / 75) + corda * (cordaDistance +(trastePosition[casa]*1.5 - 15) / casaPosition[casa]) + corda * (trastePosition[casa]/150));
            return point;
        }

        double getDistanceTraste(double l, int n) {
            double p = pow(2, ((double) n / 12));
            return l * (1 - (1 / p));
        }
    };
};

#endif // MAINWINDOW_H
