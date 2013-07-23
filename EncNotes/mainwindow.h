#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *textEdit;

    FileManager *fileManager;

public:
    MainWindow();
    ~MainWindow();

private:
    void createMenus();
    void createWidgets();

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void helpAbout();
};

#endif // MAINWINDOW_H
