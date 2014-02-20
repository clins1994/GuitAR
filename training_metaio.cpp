#include "training_metaio.h"
#include <QtGui>
#include <QtOpenGL>
#include <GL/gl.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#include <metaioSDK/IMetaioSDKWin32.h>
#include <metaioSDK/GestureHandler.h>

/*
 *
 _____ ____      _    _   _ _  ___     ___ _   _
|  ___|  _ \    / \  | \ | | |/ / |   |_ _| \ | |
| |_  | |_) |  / _ \ |  \| | ' /| |    | ||  \| |
|  _| |  _ <  / ___ \| |\  | . \| |___ | || |\  |_
|_|   |_| \_\/_/   \_\_| \_|_|\_\_____|___|_| \_( )
                                                |/
 ____  ____   ___   ____ _   _ ____  _____
|  _ \|  _ \ / _ \ / ___| | | |  _ \| ____|
| |_) | |_) | | | | |   | | | | |_) |  _|
|  __/|  _ <| |_| | |___| |_| |  _ <| |___
|_|   |_| \_\\___/ \____|\___/|_| \_\_____|

 _   _    _    ____  _   _ _____  _    ____ ____
| | | |  / \  / ___|| | | |_   _|/ \  / ___/ ___|
| |_| | / _ \ \___ \| |_| | | | / _ \| |  _\___ \
|  _  |/ ___ \ ___) |  _  | | |/ ___ \ |_| |___) |
|_| |_/_/   \_\____/|_| |_| |_/_/   \_\____|____/

*/

TrainingMetaio::TrainingMetaio(int goX, int goY, ChordSet* inputChordSet) :
    QGraphicsScene(),
    m_initialized(false),
    m_pGestureHandler(0),
    m_pMetaioSDK(0),
    x(goX),
    y(goY),
    offsetX(0),
    offsetY(-52),
    offsetZ(0),
    offsetString(8),
    currentChord(0),
    chordSet(inputChordSet)
{
    // ###############BUG DO CHORD#################
    /*ChordSet cs = ChordSet("CS");
    Chord c = Chord("C");
    QVarLengthArray<int> frets;
    frets.append(-1);
    frets.append(3);
    frets.append(2);
    frets.append(0);
    frets.append(1);
    frets.append(0);
    QList<QVarLengthArray<int>> list;
    list.append(frets);
    c.setVariations(list);
    cs.addOnFirstList(c);
    chordSet = &cs;*/

    // ###############CALCULAR OFFSETS E BOTAR NO fretOffsets#################
    // fretOffsets = calculos doidao da formula de física
}

TrainingMetaio::~TrainingMetaio()
{
    delete m_pMetaioSDK;
    m_pMetaioSDK = 0;

    delete m_pGestureHandler;
    m_pGestureHandler = 0;
}

void TrainingMetaio::loadContent()
{
    if(!m_pMetaioSDK->setTrackingConfiguration("ra/TrackingData_PictureMarker.xml"))
        qCritical("Failed to load tracking configuration");

    for (int i = 0; i < 6; i++)
    {
        metaio::IGeometry * geometry = m_pMetaioSDK->createGeometryFromImage("ra/string" + QString::number(i + 1).toStdString() + ".png");
        geometries.append(geometry);
        if(geometries.at(i))
        {
            geometries.at(i)->setScale(metaio::Vector3d(0.3,0.3,0.3));
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY, offsetZ));
        }
        else
            qCritical("Failed to load MD2 model file");
    }
}

void TrainingMetaio::drawBackground(QPainter* painter, const QRectF & rect)
{
    painter->save();
    if (painter->paintEngine()->type()	!= QPaintEngine::OpenGL2)
    {
        qWarning("GuitAR: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }

    if (!m_initialized)
    {
        m_pMetaioSDK = metaio::CreateMetaioSDKWin32();
        m_pMetaioSDK->initializeRenderer(this->x, this->y, metaio::ESCREEN_ROTATION_0, metaio::ERENDER_SYSTEM_OPENGL_EXTERNAL);

        // activate 1st camera
        std::vector<metaio::Camera> cameras = m_pMetaioSDK->getCameraList();
        if(cameras.size() > 0)
        {
            // set the resolution to 640x480
            qDebug() << x << " " << y;
            cameras[0].resolution = metaio::Vector2di(640, 480 * this->y / this->x);
            cameras[0].flip = metaio::Camera::FLIP_HORIZONTAL;
            m_pMetaioSDK->startCamera( cameras[0] );
        }

        m_initialized = true;

        m_pGestureHandler = new metaio::GestureHandler(m_pMetaioSDK);

        // Load content of specific tutorial implementation (abstract method)
        loadContent();
    }

    // Enable anti-aliasing
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);

    //    onDrawFrame();

    m_pMetaioSDK->render();

    glPopAttrib();

    // Trigger an update
    QTimer::singleShot(20, this, SLOT(update()));

    painter->restore();

    // This is a workaround to render the webpages correctly
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}


void TrainingMetaio::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    // mouseEvent->screenPos() and mouseEvent->pos() seem to be always return (0,0) and scenePos()
    // has its origin in the middle of the rendering pane
    const int x = mouseEvent->pos().x();
    const int y = mouseEvent->pos().y();

    // Forward event to gesture handler (needed for drag gesture, just like the mouse press/release events)
    if(m_pGestureHandler)
        m_pGestureHandler->touchesMoved(x, y);
}


void TrainingMetaio::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    // ###############DEBUGANDO#################
    /*Qt::MouseButtons mouseButtons = mouseEvent->buttons();
    if(mouseButtons == Qt::LeftButton)
    {
        offsetZ += 10;
        qDebug() << "left " << offsetZ;
    } else if(mouseButtons == Qt::RightButton)
    {
        offsetZ -= 10;
        qDebug() << "right " << offsetZ;
    }

    if(mouseButtons == Qt::LeftButton || mouseButtons == Qt::RightButton)
    {
        for (int i = 0; i < 6; i++)
        {
            if(geometries.at(i))
            {
                geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (i * offsetString), offsetZ));
            }else
                qCritical("Failed to translate");
        }
    }*/
    // ###############DEBUGANDO#################

    QGraphicsScene::mousePressEvent(mouseEvent);

    // See comment in mouseMoveEvent()
    const int x = mouseEvent->pos().x();
    const int y = mouseEvent->pos().y();

    // Forward event to gesture handler
    if(m_pGestureHandler)
        m_pGestureHandler->touchesBegan(x, y);
}


void TrainingMetaio::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    // See comment in mouseMoveEvent()
    const int x = mouseEvent->pos().x();
    const int y = mouseEvent->pos().y();

    // Forward event to gesture handler
    if(m_pGestureHandler)
        m_pGestureHandler->touchesEnded(x, y);
}

void TrainingMetaio::prepareAwesomeGeometries()
{
    QVarLengthArray<int> aux = currentAwesomeChord();
    for(int i = 0; i < aux.size(); i++)
    {
        if(aux.at(i) == -1)
        {
            geometries.at(i)->setVisible(FALSE);
        } else
        {
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX + fretOffsets.at(aux.at(i)), offsetY + (i * offsetString), offsetZ));
        }
    }
}

void TrainingMetaio::previousAwesomeChord()
{
    //mudar entre acordes (resolver o bug do Chord / include "chord.h")
}

void TrainingMetaio::nextAwesomeChord()
{
    //mudar entre acordes (resolver o bug do Chord / include "chord.h")
}

QVarLengthArray<int> TrainingMetaio::currentAwesomeChord()
{
    QVarLengthArray<int> retorno;
    retorno.append(-1);
    retorno.append(3);
    retorno.append(2);
    retorno.append(0);
    retorno.append(1);
    retorno.append(0);
    // resolver o bug do Chord
    return retorno;
}
