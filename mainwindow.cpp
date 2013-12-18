#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QtXml>
#include "Chord.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/images/guitar-arm.jpg"));
    ui->graphicsView->setTransform(QTransform());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

struct Point {
    double X;
    double Y;
    Point(double x, double y):X(x), Y(y) {}
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

void MainWindow::on_lineEdit_textEdited(const QString &chord_str)
{
    scene->addPixmap(QPixmap(":/images/guitar-arm.jpg"));
    ui->graphicsView->setTransform(QTransform());

    ui->statusBar->showMessage("");
    if (chord_str.isEmpty())
        return;

    QString path = ":/db/";
    path.append(chord_str.at(0));
    path.append(".xml");
    QFile file(path);

    if (!file.exists() )
    {
        ui->statusBar->showMessage("Acorde não encontrado");
        return;
    }

    QDomDocument document;
    if (!file.open(QIODevice::ReadOnly))
        return;

    if (!document.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNode rootElement = document.documentElement();

    QDomElement chord;
    for(QDomNode node = rootElement.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        chord = node.toElement();
        if (chord.text().indexOf(chord_str) != -1)
        {
            //qDebug() << chord.text();
            QDomNamedNodeMap map = chord.firstChildElement().attributes();

            int e, A, D, G, B, E;
            for (int i = 0; i < map.count(); i++)
            {
                //qDebug() << map.item(i).toAttr().name() << " " << map.item(i).toAttr().value();
                switch (map.item(i).toAttr().name().toStdString().at(0))
                {
                case 'E':
                    E = map.item(i).toAttr().value().toInt();
                    break;
                case 'A':
                    A = map.item(i).toAttr().value().toInt();
                    break;
                case 'D':
                    D = map.item(i).toAttr().value().toInt();
                    break;
                case 'G':
                    G = map.item(i).toAttr().value().toInt();
                    break;
                case 'B':
                    B = map.item(i).toAttr().value().toInt();
                    break;
                case 'e':
                    e = map.item(i).toAttr().value().toInt();
                    break;
                }
            }

            Chord * chord_new = new Chord(chord.text());
            chord_new->setFrets(e, B, G, D, A, E);
            chordsFound.push_back(chord_new);
        }
    }


    if (chordsFound.empty())
        ui->statusBar->showMessage("Acorde não encontrado.");
    else
    {
        Braco * braco = new Braco(1320, 17);
        Chord * mychord = chordsFound.front();
        Point * point;
        for (int i = 0; i < 6; i++)
        {
            if (mychord->getFret(i) != 0 && mychord->getFret(i) != -1)
            {
                point = braco->getPoint(5 - i, mychord->getFret(i));
                qDebug() << mychord->name << " " << mychord->getFret(i);
                scene->addEllipse(point->X - 8, point->Y - 8, 16, 16, QPen(Qt::red), QBrush(Qt::red));
            }
        }
        delete point;
        delete mychord;
        delete braco;
    }

}

void MainWindow::on_btnNextChord_clicked()
{

}

void MainWindow::on_btnPrevChord_clicked()
{

}
