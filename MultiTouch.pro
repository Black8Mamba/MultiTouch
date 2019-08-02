#-------------------------------------------------
#
# Project created by QtCreator 2019-07-31T08:59:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiTouch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pathelement.cpp \
    slide.cpp \
    widget.cpp \
    device_node_identify.cpp \
    mythread.cpp \
    touch_data_receive.c \
    rawtouchevent.cpp

HEADERS += \
        mainwindow.h \
    kmp.h \
    pathelement.h \
    slide.h \
    widget.h \
    device_node_identify.h \
    mythread.h \
    touch_data_receive.h \
    rawtouchevent.h

FORMS += \
        mainwindow.ui \
    widget.ui
