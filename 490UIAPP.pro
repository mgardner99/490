#-------------------------------------------------
#
# Project created by QtCreator 2013-01-04T13:40:58
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets #Make sure all your major functionalities are here

TARGET = 490UIAPP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DataPoint.cpp \
    heatmap.cpp \
    Communications.cpp \
    KneeVec.cpp

HEADERS  += mainwindow.h \
    DataPoint.h \
    heatmap.h \
    Communication.h \
    KneeVec.h

<<<<<<< HEAD
INCLUDEPATH += "C:\boost_1_52_0" #Change this to wherever your boost directory resides

LIBS += "C:\boost_1_52_0\stage\lib\libboost_system-mgw48-mt-1_52.a" #Make sure this boost library matches above - change the number of mgw to be whatever version of MinGW you have (I have 4.8) - this can also be checked in the folder
LIBS += "C:\MinGW\lib\libws2_32.a" #Should match your MinGW location - DO NOT change file name
=======
INCLUDEPATH += "C:/boost_1_52_0" #Change this to wherever your boost directory resides

LIBS += "C:\boost_1_52_0\stage\lib\libboost_system-mgw48-mt-1_52.a" #Make sure this boost library matches above
LIBS += "C:\MinGW\lib\libws2_32.a"
>>>>>>> upstream/master

FORMS    += mainwindow.ui
