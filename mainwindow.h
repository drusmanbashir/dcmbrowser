#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dcmdump.h>
#include <dcmanonymizer.h>
#include <QLabel>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public slots:
    void openDirBrowser();
    void openDirBrowser2();
    void about();
    void parseToplevelDir();
    void anonymizeFiles();
    void renameDirs(const QFileInfo& file);

private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *anonymizeAct;
    QAction *exitAct;
    QAction *aboutAct;
    QLabel *infoLabel;
    QString toplevelDir;
    DCMAnonymizer *anon;
    QFile* dataFile;
    QString outfileName;
    QList<QFileInfo> paths;

};

#endif // MAINWINDOW_H
