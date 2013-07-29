#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"
#include "encryption.h"

class QTextEdit;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *textEdit;
    Encryption *encryption;
    FileManager *fileManager;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *quitAction;
    QAction *aboutAction;

public:
    MainWindow();
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void createWidgets();

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void helpAbout();
};

#endif // MAINWINDOW_H
