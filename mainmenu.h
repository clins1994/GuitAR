#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <cmath>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:

    void on_startTrainingButton_clicked();

    void on_consultChordButton_clicked();

    void on_listMakerButton_clicked();

    void on_beatMakerButton_clicked();

    void on_backToMenuConsultChord_clicked();

    void on_backToMenuSelectBeat_clicked();

    void on_backToMenuSelectList_clicked();

    void on_backToMenuCreateList_clicked();

    void on_backToMenuCreateBeat_clicked();

    void on_normalChordsRadioButton_clicked();

    void on_splitChordsRadioButton_clicked();

    void on_normalChordsComboBox_currentIndexChanged(const QString &arg1);

    void on_chordsModificatorsComboBox_currentIndexChanged(const QString &arg1);

    void on_splitChordsComboBox_currentIndexChanged(const QString &arg1);

private:
    void updateGraphics();

    Ui::MainMenu *ui;
    QGraphicsScene * chordScene;
    const QPixmap * guitarArm = new QPixmap(":/assets/guitar_arm.png");

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

        Braco(double cordaSizeIn, double cordaDistanceIn):
            cordaSize(cordaSizeIn), cordaDistance(cordaDistanceIn) {

            int trastes = 17;
            int casas = 17;
            for (int i = 0; i < trastes; i++)
                trastePosition[i] = getDistanceTraste(cordaSize, i);

            for (int i = 1; i < casas; i++)
                casaPosition[i] = (trastePosition[i] + trastePosition[i - 1]) / 2;
        }

        Point * getPoint(int corda, int casa) {
            Point * point;
            if (corda != 0)
                point = new Point(15 + casaPosition[casa], 50 + corda * (cordaDistance + 1 - trastePosition[casa] / casaPosition[casa]));
            else
                point = new Point(15 + casaPosition[casa], 55 - 1 - trastePosition[casa] / casaPosition[casa]);
            return point;
        }

        double getDistanceTraste(double l, int n) {
            double p = pow(2, ((double) n / 12));
            return l * (1 - (1 / p));
        }
    };
};

#endif // MAINMENU_H
