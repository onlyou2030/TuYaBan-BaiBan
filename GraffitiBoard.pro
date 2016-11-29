#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T10:34:30
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraffitiBoard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintarea.cpp \
    donewdialog.cpp

HEADERS  += mainwindow.h \
    paintarea.h \
    donewdialog.h

FORMS    += mainwindow.ui \
    donewdialog.ui
