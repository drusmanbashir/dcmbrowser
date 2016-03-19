#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T17:34:56
#
#-------------------------------------------------


# in WINDOWS SELECT 'BUILD -> RUNQMAKE
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dcm_browser
TEMPLATE = app
unix:{
INCLUDEPATH += /usr/local/include/gdcm-2.6
LIBS +=  -L/home/usman/programs/gdcm-2.6.3/build/bin
}


INCLUDEPATH += "D:\programs\gdcm-2.6.2\Source\DataStructureAndEncodingDefinition" \
    "D:\programs\gdcm-2.6.2\Source\Common" \
    "D:\programs\gdcm-2.6.2\msvc_build\Source\Common" \
  D:\programs\gdcm-2.6.2\Source\MediaStorageAndFileFormat \


LIBS+= -L"D:\programs\gdcm-2.6.2\qt-build\bin"

LIBS += \
-lgdcmDSED \
-lgdcmMSFF \
#-lgdcmCommon \
#-lgdcmDICT \

#-lgdcmexpat \
#-lgdcmIOD \
#-lgdcmjpeg8 \
#-lgdcmjpeg12 \
#-lgdcmjpeg16 \
#-lgdcmopenjpeg

SOURCES += main.cpp\
        mainwindow.cpp \
    dcmdump.cpp \
    dcmanonymizer.cpp

HEADERS  += mainwindow.h \
    dcmdump.h \
    dcmanonymizer.h \

FORMS    += mainwindow.ui

