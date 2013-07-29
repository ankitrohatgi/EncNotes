QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EncNotes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filemanager.cpp \
    encryption.cpp

HEADERS  += mainwindow.h \
    filemanager.h \
    encryption.h

RESOURCES += \
    icons.qrc

ICON = icons/icon.icns

unix {
    LIBS += -lcrypto
}

win32 {
    INCLUDEPATH += "C:\OpenSSL-Win32\include"
    DEPENDPATH += "C:\OpenSSL-Win32\include"
    LIBS += -L"C:/OpenSSL-Win32/lib/" -llibeay32 -lssleay32
}

