#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QtXml>

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

    Point* getPoint(int corda, int casa) {
       Point* point = new Point(corda * cordaDistance, casaPosition[casa]);
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
        ui->statusBar->showMessage("Arquivo não encontrado");
        return;
    }

    QDomDocument document;
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    if (!document.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNode root = document.firstChild();
    QDomElement rootElement = document.firstChild().toElement();
//    if (rootElement.isProcessingInstruction())
        rootElement = root.nextSibling().toElement();

    QDomElement chord;
    for(QDomNode node = rootElement.firstChild(); !node.isNull(); node = node.nextSibling())
    {
        chord = node.toElement();
        if (chord.text() == chord_str)
        {
            break;
        }
        else
        {
            unsigned found = chord.text().indexOf(" or ");
            if (found != -1)
            {
                if (chord_str == chord.text().section(" or ", 0, 0))
                    break;

                if (chord_str == chord.text().section(" or ", 1, 1))
                    break;
            }
        }
    }

    Braco * braco = new Braco(1320, 15);

    if (!chord.isNull())
    {
        qDebug() << chord.text();
        QDomNamedNodeMap map = chord.firstChildElement().attributes();

        for (int i = 0; i < map.count(); i++)
        {
            qDebug() << map.item(i).toAttr().name() << " " << map.item(i).toAttr().value();

            if (map.item(i).toAttr().value() != "0")
            {
                int y;
                switch (map.item(i).toAttr().name().toStdString().at(0))
                {
                case 'E':
                    y = 0;
                    break;
                case 'A':
                    y = 1;
                    break;
                case 'D':
                    y = 2;
                    break;
                case 'G':
                    y = 3;
                    break;
                case 'B':
                    y = 4;
                    break;
                case 'e':
                    y = 5;
                    break;
                }
                Point * point = braco->getPoint(y, map.item(i).toAttr().value().toDouble());
                qDebug() << point->X << " " << point->Y;
                scene->addEllipse(point->X, point->Y, 15, 15, QPen(Qt::red), QBrush(Qt::red));
            }
        }

//        for (pugi::xml_attribute attr = chord.child("Strings").first_attribute(); attr; attr = attr.next_attribute())
//        {
//            cout << attr.name() << " |---";
//            if (strcmp(attr.value(), "-1") == 0)
//                cout << "-";
//            else
//                cout << attr.value();
//            cout << "---|" << endl;
//        }
    }
}
