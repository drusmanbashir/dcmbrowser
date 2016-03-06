#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dcmdump.h>
#include <QLabel>

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


};

#endif // MAINWINDOW_H
