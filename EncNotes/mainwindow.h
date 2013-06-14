#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *textEdit;

public:
    MainWindow();

private:
    void createMenus();
    void createWidgets();

private slots:
    void fileNew();
    void fileOpen();
    void helpAbout();
};

#endif // MAINWINDOW_H
