#ifndef TRAINING_METAIO_H
#define TRAINING_METAIO_H

#include <QGraphicsScene>
#include <metaioSDK/IGestureHandlerCallback.h>
#include <QVarLengthArray>
#include "chordset.h"

namespace metaio
{
    class IMetaioSDKWin32;
    class GestureHandler;
}

class TrainingMetaio : public QGraphicsScene
{
    Q_OBJECT

public:
    TrainingMetaio(int x, int y, ChordSet* inputChordSet);
    ~TrainingMetaio();

private:
    int                         x;
    int                         y;

    int                         offsetX;
    int                         offsetY;
    int                         offsetZ;
    int                         offsetString;
    int                         currentChord;

    ChordSet*                   chordSet;

    QVarLengthArray<int>        fretOffsets;
	
    QList<metaio::IGeometry *> geometries;
    //metaio::BoundingBox* auxBox;

    /// true if the tutorial has been initialized
    bool						m_initialized;

    /// the mobile SDK
    metaio::IMetaioSDKWin32*	m_pMetaioSDK;

    /// Gesture handler for touch events, can optionally be used by tutorial implementation
    metaio::GestureHandler*		m_pGestureHandler;

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
};

#endif
