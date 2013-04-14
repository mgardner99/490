#-------------------------------------------------
#
# Project created by QtCreator 2013-01-04T13:40:58
#
#-------------------------------------------------

QT       += core gui phonon

TARGET = 490UIAPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DataPoint.cpp \
    heatmap.cpp \
    Communications.cpp

HEADERS  += mainwindow.h \
    DataPoint.h \
    heatmap.h \
    Communication.h

INCLUDEPATH += "C:/boost_1_53_0"



LIBS += "c:\boost_1_53_0\stage\lib\libboost_system-mgw46-mt-1_53.a"
LIBS += "C:\MinGW\lib\libws2_32.a"

FORMS    += mainwindow.ui
