#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dcmdump.h>
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



private slots:
    void openDirBrowser();
    void about();
    void parseToplevelDir();
    void renameDirs(const QFileInfo& file);

private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *exitAct;
    QAction *aboutAct;
    QLabel *infoLabel;
    QString toplevelDir;

    QList<QFileInfo> paths;

};

#endif // MAINWINDOW_H
