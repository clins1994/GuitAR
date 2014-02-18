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
    chord.cpp \
    training_metaio.cpp \
    datamanager.cpp \
    chordset.cpp \
    business.cpp \
    serialize_hash.cpp \
    mainwindow.cpp

HEADERS += \
    chord.h \
    training_metaio.h \
    datamanager.h \
    chordset.h \
    business.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    Resources.qrc
