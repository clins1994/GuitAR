#include "training_metaio.h"
#include <QtGui>
#include <QtOpenGL>
#include <GL/gl.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#include <metaioSDK/IMetaioSDKWin32.h>
#include <metaioSDK/GestureHandler.h>

TrainingMetaio::TrainingMetaio(int goX, int goY) :
    QGraphicsScene(),
    m_initialized(false),
    m_pGestureHandler(0),
    m_pMetaioSDK(0),
    x(goX),
    y(goY)
{
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
    if(!m_pMetaioSDK->setTrackingConfiguration("ra/TrackingData_MarkerlessFast.xml"))
		qCritical("Failed to load tracking configuration");


    metaio::IGeometry* geometryPoint1= m_pMetaioSDK->createGeometryFromImage("ra/string1.png");
    if(geometryPoint1)
    {
        geometryPoint1->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint1->setTranslation(metaio::Vector3d(-100.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
    metaio::IGeometry* geometryPoint2 = m_pMetaioSDK->createGeometryFromImage("ra/string2.png");
    if(geometryPoint2)
    {
        geometryPoint2->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint2->setTranslation(metaio::Vector3d(-200.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
    metaio::IGeometry* geometryPoint3 = m_pMetaioSDK->createGeometryFromImage("ra/string3.png");
    if(geometryPoint3)
    {
        geometryPoint3->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint3->setTranslation(metaio::Vector3d(-300.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
    metaio::IGeometry* geometryPoint4 = m_pMetaioSDK->createGeometryFromImage("ra/string4.png");
    if(geometryPoint4)
    {
        geometryPoint4->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint4->setTranslation(metaio::Vector3d(-400.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
    metaio::IGeometry* geometryPoint5 = m_pMetaioSDK->createGeometryFromImage("ra/string5.png");
    if(geometryPoint5)
    {
        geometryPoint5->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint5->setTranslation(metaio::Vector3d(-500.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
    metaio::IGeometry* geometryPoint6 = m_pMetaioSDK->createGeometryFromImage("ra/string6.png");
    if(geometryPoint6)
    {
        geometryPoint6->setScale(metaio::Vector3d(0.2, 0.2, 0.2));
        geometryPoint6->setTranslation(metaio::Vector3d(-600.0, 0.0, 0.0));
    }
    else
        qCritical("Failed to load MD2 model file");
}

void TrainingMetaio::drawBackground(QPainter* painter, const QRectF & rect)
{
    painter->save();
    if (painter->paintEngine()->type()	!= QPaintEngine::OpenGL2)
    {
        qWarning("TutorialHelloWorld: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }

    if (!m_initialized)
    {
        m_pMetaioSDK = metaio::CreateMetaioSDKWin32();
        m_pMetaioSDK->initializeRenderer(800, 800 * this->y / this->x, metaio::ESCREEN_ROTATION_0, metaio::ERENDER_SYSTEM_OPENGL_EXTERNAL);

        // activate 1st camera
        std::vector<metaio::Camera> cameras = m_pMetaioSDK->getCameraList();
        if(cameras.size() > 0)
        {
            // set the resolution to 640x480
            qDebug() << x << " " << y;
            cameras[0].resolution = metaio::Vector2di(this->x, this->y);
            cameras[0].flip = metaio::Camera::FLIP_HORIZONTAL;
            m_pMetaioSDK->startCamera( cameras[0] );
        }

        //if(!m_pMetaioSDK->loadEnvironmentMap("assets/TutorialContentTypes/Assets/env_map.zip"));
        //    qCritical("Failed to load environment map");

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
    const int x = mouseEvent->scenePos().x() + 800/2;
    const int y = mouseEvent->scenePos().y() + 600/2;

    // Forward event to gesture handler (needed for drag gesture, just like the mouse press/release events)
    if(m_pGestureHandler)
        m_pGestureHandler->touchesMoved(x, y);
}


void TrainingMetaio::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    // See comment in mouseMoveEvent()
    const int x = mouseEvent->scenePos().x() + 800/2;
    const int y = mouseEvent->scenePos().y() + 600/2;

    qDebug() << x << " " << y;

    // Forward event to gesture handler
    if(m_pGestureHandler)
        m_pGestureHandler->touchesBegan(x, y);
}


void TrainingMetaio::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    // See comment in mouseMoveEvent()
    const int x = mouseEvent->scenePos().x() + 800/2;
    const int y = mouseEvent->scenePos().y() + 600/2        ;

    // Forward event to gesture handler
    if(m_pGestureHandler)
        m_pGestureHandler->touchesEnded(x, y);
}
