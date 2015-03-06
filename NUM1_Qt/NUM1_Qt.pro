#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T20:33:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = NUM1_Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../qcustomplot.cpp \
    plot.cpp \
    controller.cpp \
    funk.cpp

HEADERS  += mainwindow.h \
    ../qcustomplot.h \
    plot.h \
    controller.h \
    funk.h

FORMS    += mainwindow.ui \
    plot.ui \
    controller.ui
