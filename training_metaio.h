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

private:
    int width;
    int height;

    int offsetX;
    int offsetY;
    int offsetZ;
    int offsetString;
    int currentChord;

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

    void drawBackground(QPainter* painter, const QRectF & rect);

public slots:
    void update(QString chord);
};

#endif

