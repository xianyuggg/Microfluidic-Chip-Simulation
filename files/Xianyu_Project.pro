#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T19:52:11
#
#-------------------------------------------------

QT       += core gui
QT += winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Xianyu_Project
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
    chip.cpp \
    advanced_dialog.cpp \
    start.cpp \
    info.cpp \
    drawarea.cpp \
    workingarea.cpp \
    change_dialog.cpp \
    mytooltip.cpp

HEADERS += \
        mainwindow.h \
    chip.h \
    advanced_dialog.h \
    start.h \
    info.h \
    drawarea.h \
    workingarea.h \
    change_dialog.h \
    mytooltip.h

FORMS += \
        mainwindow.ui \
    change_dialog.ui

RESOURCES += \
    res.qrc



