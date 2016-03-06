#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // QString DICOMDIR;

//    DICOMDIR ="/media/WDC/ADC_4.3/1.2.528.1.1001.200.10.1485.3833.784206140.20160303133506367/DICOMDIR";
    ui->setupUi(this);

    createActions();
    createMenus();

    setWindowTitle(tr("Menus"));
    setMinimumSize(160,160);
    resize(480,320);


   // DCMDump dump(DICOMDIR);
//    ui->pt_id->setText(dump.outputPtID());
//    ui->study_date->setText(dump.outputStudydate());
//    ui->modality->setText(dump.outputModality());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
        openAct = new QAction(tr("&Select Directory"), this);
        openAct->setShortcuts(QKeySequence::Open);
        openAct->setStatusTip(tr("Select a top-level DICOM directory"));
        connect(openAct, SIGNAL(triggered()), this, SLOT(openDirBrowser()));


        exitAct = new QAction(tr("E&xit"), this);
            exitAct->setShortcuts(QKeySequence::Quit);
            exitAct->setStatusTip(tr("Exit the application"));
            connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

            aboutAct = new QAction(tr("&About"), this);
            aboutAct->setStatusTip(tr("Show the application's About box"));
            connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}


void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void MainWindow::openDirBrowser()
{
//QFileDialog dialog(this);

//dialog.setFileMode(QFileDialog::Directory);

//if(dialog.exec()){
//    toplevelDir=dialog.getExistingDirectory();
    //}

 toplevelDir=   QFileDialog::getExistingDirectory(
            this,
            tr("Select a Directory"),  QDir::currentPath()
             QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks,
          );
        if( !toplevelDir.isNull() )
        {
            parseToplevelDir();
          qDebug()<<toplevelDir;
        }
}


void MainWindow::parseToplevelDir(){


    QDirIterator it(toplevelDir, QStringList() << "DICOMDIR", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();


}
