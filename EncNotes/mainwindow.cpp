#include "mainwindow.h"

#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>
#include <QInputDialog>

MainWindow::MainWindow()
{
    createMenus();
    createWidgets();

    fileManager = NULL;
    encryption = NULL;
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
    if(fileName.isEmpty()) return;

    if(fileManager == NULL) fileManager = new FileManager();

    fileManager->setFileName(fileName.toStdString());
    if(!fileManager->open()) return;

    bool ok;
    QString passwdQString = QInputDialog::getText(this, tr("Password"), tr("Enter a password: "), QLineEdit::Password, tr(""), &ok);

    if(!ok) return;

    if(encryption == NULL)
    {
        encryption = new Encryption();
    }

    encryption->setPassword(passwdQString.toStdString());

    int len;

    unsigned char *encryptedText = fileManager->getContent(&len);

    unsigned char *decryptedText = encryption->decryptString(encryptedText, &len);

    QString contents = QString::fromUtf8((const char*)decryptedText, len);
    textEdit->setText(contents);

}

void MainWindow::fileSave()
{
    if(fileManager == NULL)
        fileManager = new FileManager();

    if(!fileManager->hasFileName())
    {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save File"),
                                                        QString(),
                                                        tr("All Files (*);;Text Files (*.txt)"));
        if(fileName.isEmpty()) return;

        fileManager->setFileName(fileName.toStdString());
    }

    if(encryption == NULL)
    {
        bool ok;
        QString passwdQString = QInputDialog::getText(this, tr("Password"), tr("Enter a password: "), QLineEdit::Password, tr(""), &ok);
        if(!ok) return;

        encryption = new Encryption();
        encryption->setPassword(passwdQString.toStdString());
    }

    unsigned char *text = (unsigned char*)textEdit->toPlainText().toStdString().c_str();
    int len = std::strlen((const char*)text);

    unsigned char *encryptedText = encryption->encryptString(text, &len);

    fileManager->setContent(encryptedText, len);
    fileManager->save();
}

void MainWindow::fileSaveAs()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    QString(),
                                                    tr("All Files (*);;Text Files (*.txt)"));
    if(fileName.isEmpty()) return;

    bool ok;
    QString passwdQString = QInputDialog::getText(this, tr("Password"), tr("Enter a password: "), QLineEdit::Password, tr(""), &ok);

    if(!ok) return;

    if(encryption == NULL)
    {
        encryption = new Encryption();
    }
    encryption->setPassword(passwdQString.toStdString());

    unsigned char *text = (unsigned char*)textEdit->toPlainText().toStdString().c_str();
    int len = std::strlen((const char*)text);

    unsigned char *encryptedText = encryption->encryptString(text, &len);

    if(fileManager == NULL)
        fileManager = new FileManager();

    fileManager->setContent(encryptedText, len);
    fileManager->saveAs(fileName.toStdString());
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
    if(fileManager != NULL) delete fileManager;
    if(encryption != NULL) delete encryption;
}
