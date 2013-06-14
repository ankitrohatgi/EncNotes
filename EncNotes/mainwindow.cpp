#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>

MainWindow::MainWindow()
{
    createMenus();
    createWidgets();
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *newAction = fileMenu->addAction(tr("&New"));
    newAction->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    connect(newAction, SIGNAL(triggered()), this, SLOT(fileNew()));

    QAction *openAction = fileMenu->addAction(tr("&Open"));
    openAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart));
    connect(openAction, SIGNAL(triggered()), this, SLOT(fileOpen()));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()));
}

void MainWindow::createWidgets()
{
    textEdit = new QTextEdit(this);
    textEdit->setMinimumSize(400, 400);
    textEdit->setText("Hello");
    setCentralWidget(textEdit);
}

void MainWindow::fileNew()
{
    textEdit->clear();
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    QString(),
                                                    tr("All Files (*);;Text Files (*.txt)"));
    if(!fileName.isEmpty())
    {
        textEdit->setText(fileName);
    }
}

void MainWindow::helpAbout()
{
    QMessageBox *aboutMessage = new QMessageBox(this);
    aboutMessage->setWindowTitle(tr("About EncryptedNotepad"));
    aboutMessage->setText(tr("<p>EncryptedNotepad is a small tool written to learn QT</p><p>Author: Ankit Rohatgi &lt;ankitrohatgi@hotmail.com&gt;</p>"));
    aboutMessage->show();
}
