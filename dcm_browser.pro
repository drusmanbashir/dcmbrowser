#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T17:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dcm_browser
TEMPLATE = app
INCLUDEPATH += /usr/local/include/gdcm-2.6

LIBS +=  -L/home/usman/programs/gdcm-2.6.3/build/bin
LIBS +=  -lgdcmMSFF -lgdcmCommon -lgdcmDICT -lgdcmDSED -lgdcmexpat -lgdcmIOD -lgdcmjpeg8 -lgdcmjpeg12 -lgdcmjpeg16 -lgdcmopenjpeg -lgdcmzlib -lgdcmcharls

SOURCES += main.cpp\
        mainwindow.cpp \
    dcmdump.cpp \
    dicomdirgenerator.cpp

HEADERS  += mainwindow.h \
    dcmdump.h \
    dicomdirgenerator

FORMS    += mainwindow.ui
