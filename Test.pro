#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T11:47:14
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    traitement.cpp \
    qcustomplot.cpp \
    histogramme.cpp

HEADERS  += mainwindow.h \
    image.h \
    traitement.h \
    qcustomplot.h \
    histogramme.h

FORMS    += mainwindow.ui \
    histogramme.ui

RESOURCES += \
    Icon.qrc
