#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T11:44:15
#
#-------------------------------------------------

QT += core gui xml opengl webkit network phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guitAR
TEMPLATE = app

CONFIG += release

INCLUDEPATH += $$_PRO_FILE_PWD_/metaioSDK/include

LIBS += \
    -L"$$_PRO_FILE_PWD_/metaioSDK/bin" \
    -lmetaioSDK \
    -lwinmm

SOURCES += \
    main.cpp \
    mainmenu.cpp \
    chord.cpp \
    training_metaio.cpp \
    datamanager.cpp \
    chordset.cpp \
    business.cpp

HEADERS += \
    mainmenu.h \
    chord.h \
    training_metaio.h \
    datamanager.h \
    chordset.h \
    business.h

FORMS += \
    mainmenu.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    assets/TutorialHelloWorld/arelConfig.xml \
    assets/TutorialHelloWorld/arelTutorial.html \
    assets/TutorialHelloWorld/Assets/arelGlue.js \
    assets/TutorialHelloWorld/Assets/metaioman.md2 \
    assets/TutorialHelloWorld/Assets/TrackingData_MarkerlessFast.xml \
    assets/TutorialHelloWorld/Assets/metaioman.png \
    assets/TutorialHelloWorld/Assets/metaioman_target.png \
    assets/TutorialHelloWorld/Assets/metaioman_target_original.png \
    assets/TutorialHelloWorld/Assets/TrackingData_PictureMarker.xml
