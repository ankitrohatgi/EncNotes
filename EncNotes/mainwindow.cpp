#include "mainwindow.h"

#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>
#include <QInputDialog>
#include <QToolBar>
#include <cstring>
#include <QSettings>

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createWidgets();
    createToolbar();

    fileManager = NULL;
    encryption = NULL;
}

void MainWindow::createActions()
{
    newAction = new QAction(style()->standardIcon(QStyle::SP_FileIcon), tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("New file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(fileNew()));

    openAction = new QAction(style()->standardIcon(QStyle::SP_FileDialogStart), tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(fileOpen()));

    saveAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(fileSave()));

    saveAsAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), tr("Save &As"), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save file as"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    aboutAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()));

    quitAction = new QAction(style()->standardIcon(QStyle::SP_BrowserStop), tr("&Quit"), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolbar()
{
    QToolBar *fileToolbar = addToolBar(tr("File"));
    fileToolbar->setIconSize(QSize(16,16));
    fileToolbar->addAction(newAction);
    fileToolbar->addAction(openAction);
    fileToolbar->addAction(saveAction);
    fileToolbar->addAction(quitAction);
}

void MainWindow::createWidgets()
{
    textEdit = new QTextEdit(this);
    textEdit->setMinimumSize(400, 400);
    setCentralWidget(textEdit);

    this->setWindowTitle(QString("EncNotes - Ankit Rohatgi (2013)"));
}

void MainWindow::fileNew()
{
    textEdit->clear();
    if(fileManager != NULL) delete fileManager;
    if(encryption != NULL) delete encryption;
}

void MainWindow::fileOpen()
{
    const QString DEFAULT_DIR_KEY("default_dir");
    QSettings mySettings;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    mySettings.value(DEFAULT_DIR_KEY).toString(),
                                                    tr("All Files (*);;Text Files (*.txt)"));
    if(fileName.isEmpty()) return;

    QDir CurrentDir;
    mySettings.setValue(DEFAULT_DIR_KEY, CurrentDir.absoluteFilePath(fileName));

    openFile(fileName.toStdString());
}

void MainWindow::openFile(std::string filename)
{
    if(filename.length() == 0) return;

    if(fileManager == NULL) fileManager = new FileManager();

    fileManager->setFileName(filename);
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
    delete[] decryptedText;
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


    std::string textString = textEdit->toPlainText().toStdString();
    int len = textString.length();
    unsigned char *text = new unsigned char[len];
    std::memcpy(text, textString.c_str(), len);

    unsigned char *encryptedText = encryption->encryptString(text, &len);

    fileManager->setContent(encryptedText, len);
    fileManager->save();

    delete[] text;
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

    std::string textString = textEdit->toPlainText().toStdString();
    int len = textString.length();
    unsigned char *text = new unsigned char[len];
    std::memcpy(text, textString.c_str(), len);

    unsigned char *encryptedText = encryption->encryptString(text, &len);

    if(fileManager == NULL)
        fileManager = new FileManager();

    fileManager->setContent(encryptedText, len);
    fileManager->saveAs(fileName.toStdString());
    delete[] text;
}

void MainWindow::helpAbout()
{
    QMessageBox *aboutMessage = new QMessageBox(this);
    aboutMessage->setWindowTitle(tr("About EncryptedNotepad"));
    aboutMessage->setText(tr("<p>EncNotes is a small text encryption tool written to learn QT</p><p>Author: Ankit Rohatgi &lt;ankitrohatgi@hotmail.com&gt;</p>"));
    aboutMessage->show();
}

MainWindow::~MainWindow()
{
    if(fileManager != NULL) delete fileManager;
    if(encryption != NULL) delete encryption;
}
