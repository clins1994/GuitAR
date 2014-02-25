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
    offsetX(-600),
    offsetY(-197),
    offsetZ(0),
    offsetString(27),
    currentChord(0),
    is_trainingChordSet(false),
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
    if(!m_pMetaioSDK->setTrackingConfiguration(business->getDataBasePath().toStdString() + "ra\\TrackingData_PictureMarker.xml"))
        qCritical("Failed to load tracking configuration");

    for (int i = 0; i < 6; i++)
    {
        metaio::IGeometry * geometry = m_pMetaioSDK->createGeometryFromImage(business->getDataBasePath().toStdString() + "ra\\string" + QString::number(i + 1).toStdString() + ".png");
        //metaio::IGeometry * geometry = m_pMetaioSDK->createGeometryFromImage(business->getDataBasePath().toStdString() + "ra\\string1.png");
        geometries.append(geometry);
        if(geometries.at(i))
        {
            geometries.at(i)->setScale(metaio::Vector3d(0.15,0.15,0.15));
            geometries.at(i)->setVisible(FALSE);
        }
        else
            qCritical("Failed to load MD2 model file");
    }

    prepareFretOffsets(2400);
    update("A M");
}

void TrainingMetaio::pause()
{
    m_pMetaioSDK->pause();
    m_pMetaioSDK->stopCamera();
}

void TrainingMetaio::resume()
{
    std::vector<metaio::Camera> cameras = m_pMetaioSDK->getCameraList();
    if(cameras.size() > 0)
    {
        // set the resolution to 640x480
        cameras[0].resolution = metaio::Vector2di(640, 480 * this->height / this->width);
        cameras[0].flip = metaio::Camera::FLIP_HORIZONTAL;
        m_pMetaioSDK->startCamera( cameras[0] );
    }

    m_pMetaioSDK->resume();
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

void TrainingMetaio::disableChordSetTraining()
{
    is_trainingChordSet = false;
}

void TrainingMetaio::setTraining(QString chordSetName)
{
    is_trainingChordSet = true;
    this->chordSetName = chordSetName;
}

void TrainingMetaio::update(QString chord)
{
    for (int i = 0; i < 6; i++)
    {
        if (geometries.at(i))
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (i * offsetString), offsetZ));
        else
            qCritical("Failed to translate");
    }

    prepareAwesomeGeometries(chord);
}

void TrainingMetaio::update(int index)
{
    for (int i = 0; i < 6; i++)
    {
        if (geometries.at(i))
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (i * offsetString), offsetZ));
        else
            qCritical("Failed to translate");
    }

    prepareAwesomeGeometries(index);
}

void TrainingMetaio::prepareAwesomeGeometries(int index)
{
    QVarLengthArray<int> aux = currentAwesomeChord(index);
    for (int i = 0; i < aux.size(); i++)
    {
        if(aux.at(i) == -1 || aux.at(i) == 0)
        {
            geometries.at(i)->setVisible(FALSE);
        }
        else if(aux.at(i) == 1)
        {
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (-i * offsetString), offsetZ));
        }
        else
        {
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX + fretOffsets.at(aux.at(i) - 1), offsetY + (-i * offsetString), offsetZ));
        }
    }
}

void TrainingMetaio::prepareAwesomeGeometries(QString chord)
{
    QVarLengthArray<int> aux = currentAwesomeChord(chord);
    for (int i = 0; i < aux.size(); i++)
    {
        if(aux.at(i) == -1 || aux.at(i) == 0)
        {
            geometries.at(i)->setVisible(FALSE);
        }
        else if(aux.at(i) == 1)
        {
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX, offsetY + (-i * offsetString), offsetZ));
        }
        else
        {
            geometries.at(i)->setVisible(TRUE);
            geometries.at(i)->setTranslation(metaio::Vector3d(offsetX + fretOffsets.at(aux.at(i) - 1), offsetY + (-i * offsetString), offsetZ));
        }
    }
}

QVarLengthArray<int> TrainingMetaio::currentAwesomeChord(QString chord)
{
    return business->getChord(chord).getCurrentVariation();
}

QVarLengthArray<int> TrainingMetaio::currentAwesomeChord(int index)
{
    return business->getChordSet("lol").getChord(index)->getCurrentVariation();
}

void TrainingMetaio::prepareFretOffsets(double cordaSizeIn)
{
    for (int i = 0; i < 17; i++)
    {
        // get distance between fret
        double p = pow(2, ((double) i / 12));
        fretOffsets.append(cordaSizeIn * (1 - (1 / p)));
//        qDebug() << fretOffsets.at(i);
    }
}

