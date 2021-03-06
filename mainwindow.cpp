#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDirIterator>
#include <QListWidget>
#include <gdcmDICOMDIR.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   // QString DICOMDIR;

//    DICOMDIR ="/media/WDC/ADC_4.3/1.2.528.1.1001.200.10.1485.3833.784206140.20160303133506367/DICOMDIR";
    ui->setupUi(this);

    createActions();
    createMenus();

    setWindowTitle(tr("DICOM browser"));
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
        openAct = new QAction(tr("&Rename Directory"), this);
        openAct->setShortcuts(QKeySequence::Open);
        openAct->setStatusTip(tr("Select a top-level DICOM directory"));
        connect(openAct, SIGNAL(triggered()), this, SLOT(openDirBrowser()));

        anonymizeAct = new QAction(tr("&Anonymize DICOM files"), this);
        anonymizeAct->setShortcuts(QKeySequence::New);
        anonymizeAct->setStatusTip(tr("Select a top-level DICOM directory"));
        connect(anonymizeAct, SIGNAL(triggered()), this, SLOT(openDirBrowser2()));

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
    fileMenu->addAction(anonymizeAct);
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

 toplevelDir=   QFileDialog::getExistingDirectory(
            this,
            tr("Select a Directory to rename"),  QDir::currentPath(),
             QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks
          );
        if( !toplevelDir.isNull() )
        {
            parseToplevelDir();
        }
}

void MainWindow::openDirBrowser2()
{

 toplevelDir=   QFileDialog::getExistingDirectory(
            this,
            tr("Select a Directory to anonymize"),  QDir::currentPath(),
             QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks
          );
        if( !toplevelDir.isNull() )
        {
                          anonymizeFiles();
        }
}


void MainWindow::parseToplevelDir(){

QStringList tmp;

    QDirIterator it(toplevelDir,  QStringList()<<"DICOMDIR",QDir::Files,QDirIterator::Subdirectories);
     tmp<<it.filePath();
            qDebug()<<it.next();
    while (it.hasNext()){

     paths<<  it.fileInfo();
     tmp<<it.filePath();

            qDebug()<<it.next();

    }
    QListWidget *display = new QListWidget();
    display->addItems(tmp);
    display->show();


    QListIterator<QFileInfo> i(paths);
     dataFile= new QFile("summary.csv");
   if(dataFile->open(QFile::WriteOnly|QFile::Truncate)){
    while (i.hasNext()){

        renameDirs(i.next());  //javastyle iterator positioned between items and returns the previous item so first item gets returned with the first call!
    }
   }
    dataFile->close();
}

void MainWindow::renameDirs(const QFileInfo& file){

   QDir rambo(file.absoluteDir());
   QFileInfo newName ;
   DCMDump dump(file.absoluteFilePath());
   QString oldDirName = file.absolutePath();
   rambo.cdUp();
   QString newDirName = rambo.path()+"/"+dump.outputPtID()+"_"+dump.outputModality()+"_"+dump.outputStudydate();

       QTextStream output(dataFile);
       output<<oldDirName<<"\tNew name: "<<newDirName<<"\n";


   qDebug()<<oldDirName<<"\n"<<newDirName;
   qDebug()<<"Dirname:"<<rambo.dirName()<<"\n"<<rambo.absolutePath();
  rambo.rename(oldDirName,newDirName);

}

void MainWindow::anonymizeFiles(){
QStringList tmp;
    QDirIterator it(toplevelDir, QStringList()<<"*.dcm",QDir::Files |QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    while (it.hasNext()){


            qDebug()<<it.next();
if(it.fileName()=="DICOMDIR"){

    qDebug()<<"\nThis is a DICOMDIR file..";


//    anon = new DCMAnonymizer(it.filePath());
//    anon->anonymizeDICOMDIR();




}
else{

 anon = new DCMAnonymizer(it.filePath());
 anon->anonymize();
}
    }


//

    }



