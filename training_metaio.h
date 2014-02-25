#ifndef TRAINING_METAIO_H
#define TRAINING_METAIO_H

#include <QGraphicsScene>
#include <metaioSDK/IGestureHandlerCallback.h>
#include <QVarLengthArray>
#include "business.h"

namespace metaio
{
class IMetaioSDKWin32;
class GestureHandler;
}

class TrainingMetaio : public QGraphicsScene
{
    Q_OBJECT

public:
    TrainingMetaio(int x_in, int y_in, Business * business_in);
    ~TrainingMetaio();

    void setTraining(QString chordSetName);

    void pause();
    void resume();

private:
    int width;
    int height;

    int offsetX;
    int offsetY;
    int offsetZ;
    int offsetString;
    int currentChord;

    bool is_trainingChordSet;
    QString chordSetName;

    Business * business;
    QVarLengthArray<int> fretOffsets;

    QList<metaio::IGeometry *> geometries;
    //metaio::BoundingBox* auxBox;

    /// true if the tutorial has been initialized
    bool m_initialized;

    /// the mobile SDK
    metaio::IMetaioSDKWin32* m_pMetaioSDK;

    /// Gesture handler for touch events, can optionally be used by tutorial implementation
    metaio::GestureHandler* m_pGestureHandler;

    void loadContent();

    void disableChordSetTraining();

    void drawBackground(QPainter* painter, const QRectF & rect);

    void prepareAwesomeGeometries(QString chord);
    QVarLengthArray<int> currentAwesomeChord(QString chord);

    void prepareAwesomeGeometries(int index);
    QVarLengthArray<int> currentAwesomeChord(int index);

    void prepareFretOffsets(double cordaSizeIn);

public slots:
    void update(QString chord);
    void update(int index);
};

#endif

