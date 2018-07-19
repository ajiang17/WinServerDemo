#-------------------------------------------------
#
# Project created by QtCreator 2018-06-11T17:57:33
#
#-------------------------------------------------

QT       += core gui
QT     += printsupport
QT     += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WinServerDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += HAVE_CONFIG_H
LIBS += $${PWD}/libQrencoded.a
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwinserver.cpp \
    printfeatures.cpp \
    serialport.cpp \
    scanserialportinfo.cpp

HEADERS += \
        mainwinserver.h \
    printfeatures.h \
    qrencode.h \
    serialport.h \
    scanserialportinfo.h

FORMS += \
        mainwinserver.ui
