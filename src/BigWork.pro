#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T21:00:32
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigWork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    pipe.cpp \
    board.cpp \
    calculate.cpp \
    node.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    pipe.h \
    board.h \
    node.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    image.qrc

DISTFILES +=
