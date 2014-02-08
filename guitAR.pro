#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T11:44:15
#
#-------------------------------------------------

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guitAR
TEMPLATE = app


SOURCES += main.cpp \
	mainmenu.cpp \
	Chord.cpp

HEADERS  += \
	mainmenu.h \
	Chord.hpp

FORMS    += \
	mainmenu.ui

RESOURCES += \
	Resources.qrc
