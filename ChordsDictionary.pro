#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T09:01:06
#
#-------------------------------------------------

QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChordsDictionary
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	Chord.cpp

HEADERS  += mainwindow.h \
	Chord.hpp

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
	Resources.qrc
