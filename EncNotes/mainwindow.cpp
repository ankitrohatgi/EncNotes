#include "mainwindow.h"
#include "filemanager.h"
#include "encryption.h"

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

    fileManager = new FileManager();
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

    QAction *saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(fileSave()));

    QAction *saveAsAction = fileMenu->addAction(tr("Save &As"));
    saveAsAction->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));


    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()));
}

void MainWindow::createWidgets()
{
    textEdit = new QTextEdit(this);
    textEdit->setMinimumSize(400, 400);
    setCentralWidget(textEdit);

    Encryption *encryption = new Encryption();
    unsigned char message[] = "This is a test";
    unsigned char passwd[] = "ankitrohatgi";
    int len = 15;
    unsigned char* encryptedString = encryption->encryptString(passwd, message, &len);
    unsigned char* decryptedString = encryption->decryptString(passwd, encryptedString, &len);
    textEdit->setText(QString::fromUtf8((const char*)decryptedString, len));
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
        fileManager->openFile(fileName.toStdString());
        QString contents = QString::fromStdString(fileManager->getContent());
        textEdit->setText(contents);
    }
}

void MainWindow::fileSave()
{
    fileManager->setContent(textEdit->toPlainText().toStdString());
    fileManager->save();
}

void MainWindow::fileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    QString(),
                                                    tr("All Files (*);;Text Files (*.txt)"));
    if(!fileName.isEmpty())
    {
        fileManager->setContent(textEdit->toPlainText().toStdString());
        fileManager->saveas(fileName.toStdString());
    }

}

void MainWindow::helpAbout()
{
    QMessageBox *aboutMessage = new QMessageBox(this);
    aboutMessage->setWindowTitle(tr("About EncryptedNotepad"));
    aboutMessage->setText(tr("<p>EncryptedNotepad is a small tool written to learn QT</p><p>Author: Ankit Rohatgi &lt;ankitrohatgi@hotmail.com&gt;</p>"));
    aboutMessage->show();
}

MainWindow::~MainWindow()
{
    delete fileManager;
}
