#ifndef TRAINING_METAIO_H
#define TRAINING_METAIO_H

#include <QGraphicsScene>
#include <metaioSDK/IGestureHandlerCallback.h>
#include <QVarLengthArray>
#include "business.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

namespace metaio
{
class IMetaioSDKWin32;
class GestureHandler;
}

class TrainingMetaio : public QGraphicsScene
{
    Q_OBJECT

public:
    TrainingMetaio(int x_in, int y_in, Business * business_in, Ui::MainWindow * ui_in);
    ~TrainingMetaio();

private:
    int                         width;
    int                         height;

    int                         offsetX;
    int                         offsetY;
    int                         offsetZ;
    int                         offsetString;
    int                         currentChord;

    Business * business;

    Ui::MainWindow * ui;

    QVarLengthArray<double>        fretOffsets;

    QVarLengthArray<int>        currentChordArray;

    QList<metaio::IGeometry *> geometries;
    //metaio::BoundingBox* auxBox;

    /// true if the tutorial has been initialized
    bool                                                m_initialized;

    /// the mobile SDK
    metaio::IMetaioSDKWin32*    m_pMetaioSDK;

    /// Gesture handler for touch events, can optionally be used by tutorial implementation
    metaio::GestureHandler*             m_pGestureHandler;

    /**
    * Load demo content, like tracking configuration (different depending on tutorial number)
    */
    void loadContent();

    /**
    * QGraphicsScene inherited drawBackground function
    *
    * \param painter pointer to the QPainter object
    * \param rect the exposed rectangle
    */
    void drawBackground(QPainter* painter, const QRectF & rect);

    /**
    * Inherited method for handling mouse move event
    *
    * \param mouseEvent the QGraphicsSceneMouseEvent mouse event
    */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    /**
    * Inherited method for handling mouse press event
    *
    * \param mouseEvent the QGraphicsSceneMouseEvent mouse event
    */
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

    /**
    * Inherited method for handling mouse release event
    *
    * \param mouseEvent the QGraphicsSceneMouseEvent mouse event
    */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    void prepareAwesomeGeometries();

    void previousAwesomeChord();

    void nextAwesomeChord();

    QVarLengthArray<int> currentAwesomeChord();

    void prepareFretOffsets(double cordaSizeIn);
};

//    struct BracoRA {
//        double trastePosition[17];
//        double casaPosition[17];
//        double cordaSize;
//        double cordaDistance;
//        double start;

//        BracoRA(double cordaSizeIn, double cordaDistanceIn, double startIn):
//            cordaSize(cordaSizeIn), cordaDistance(cordaDistanceIn), start(startIn) {
//            int trastes = 17;
//            int casas = 17;
//            for (int i = 0; i < trastes; i++)
//                trastePosition[i] = getDistanceTraste(cordaSize, i);

//            for (int i = 1; i < casas; i++)
//                casaPosition[i] = (trastePosition[i] + trastePosition[i - 1]) / 2;
//        }

//        PointRA * getPoint(int corda, int casa) {
//            PointRA * point = new PointRA(27 + casaPosition[casa], start - (casaPosition[casa] / 75) + corda * (cordaDistance +(trastePosition[casa]*1.5 - 15) / casaPosition[casa]) + corda * (trastePosition[casa]/150));
//            return point;
//        }

//        double getDistanceTraste(double l, int n) {
//            double p = pow(2, ((double) n / 12));
//            return l * (1 - (1 / p));
//        }
//    };

#endif

