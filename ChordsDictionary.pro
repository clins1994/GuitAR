#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T09:01:06
#
#-------------------------------------------------

QT       += core gui xml

TARGET = ChordsDictionary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Chord.cpp \
    include/pugixml/src/pugixml.cpp

HEADERS  += mainwindow.h \
    Chord.hpp \
    include/pugixml/src/pugixml.hpp \
    include/pugixml/src/pugiconfig.hpp

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
