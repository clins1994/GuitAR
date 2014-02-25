#include "training_metaio.h"
#include <QtGui>
#include <QtOpenGL>
#include <GL/gl.h>
#include "business.h"
#include <iostream>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#include <metaioSDK/IMetaioSDKWin32.h>
#include <metaioSDK/GestureHandler.h>

using namespace std;

TrainingMetaio::TrainingMetaio(int width_in, int height_in, Business * business_in) :
    QGraphicsScene(),
    m_initialized(false),
    m_pGestureHandler(0),
    m_pMetaioSDK(0),
    offsetX(0),
    offsetY(0),
    offsetZ(0),
    offsetString(0),
    currentChord(0),
    width(width_in),
    height(height_in),
    business(business_in)
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
    if(!m_pMetaioSDK->setTrackingConfiguration(business->getDataBasePath().toStdString() + "ra\\TrackingData_MarkerlessFast.xml"))
        qCritical("Failed to load tracking configuration");

    for (int i = 0; i < 6; i++)
    {
        metaio::IGeometry * geometry = m_pMetaioSDK->createGeometryFromImage(business->getDataBasePath().toStdString() + "ra\\string" + QString::number(i + 1).toStdString() + "2.png");
        geometries.append(geometry);
        if(geometries.at(i))
        {
            geometries.at(i)->setScale(metaio::Vector3d(0.3,0.3,0.3));
            geometries.at(i)->setVisible(FALSE);
        }
        else
            qCritical("Failed to load MD2 model file");
    }
}

void TrainingMetaio::drawBackground(QPainter* painter, const QRectF & rect)
{
    painter->save();
    if (painter->paintEngine()->type()  != QPaintEngine::OpenGL2)
    {
        qWarning("GuitAR: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }

    if (!m_initialized)
    {
        m_pMetaioSDK = metaio::CreateMetaioSDKWin32();
        m_pMetaioSDK->initializeRenderer(this->width, this->height, metaio::ESCREEN_ROTATION_0, metaio::ERENDER_SYSTEM_OPENGL_EXTERNAL);

        // activate 1st camera
        std::vector<metaio::Camera> cameras = m_pMetaioSDK->getCameraList();
        if(cameras.size() > 0)
        {
            // set the resolution to 640x480
            cameras[0].resolution = metaio::Vector2di(640, 480 * this->height / this->width);
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

void TrainingMetaio::setTraining(QString chordSetName)
{
}

void TrainingMetaio::update(QString chord)
{
    fretOffsets = business->getChord(chord).getCurrentVariation();

    for (int i = 0; i < 6; i++)
    {
        if (geometries.at(i))
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (i * offsetString), offsetZ));
        else
            qCritical("Failed to translate");
    }

    for (int i = 0; i < 6; i++)
        cout << fretOffsets.at(i) << " ";
    cout << endl;
}

//void TrainingMetaio::prepareAwesomeGeometries()
//{
//    QVarLengthArray<int> aux = currentAwesomeChord();
//    for (int i = 0; i < aux.size(); i++)
//    {
//        if (aux.at(i) == -1)
//            geometries.at(i)->setVisible(FALSE);
//        else
//        {
//            geometries.at(i)->setVisible(TRUE);
//            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX + fretOffsets.at(aux.at(i)), offsetY + (i * offsetString), offsetZ));
//        }
//    }
//}
