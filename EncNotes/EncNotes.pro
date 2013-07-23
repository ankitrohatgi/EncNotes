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

ICON = icons/test.icns

LIBS += -lcrypto
