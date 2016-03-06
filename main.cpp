#include "mainwindow.h"
#include <QApplication>
#include <gdcmAnonymizer.h>
#include <gdcmDICOMDIRGenerator.h>
#include <gdcmDirectory.h>
#include <gdcmWriter.h>
#include <gdcmTrace.h>
#include <string>
#include <QDir>
#include <QDebug>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
