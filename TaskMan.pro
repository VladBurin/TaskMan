#-------------------------------------------------
#
# Project created by QtCreator 2020-10-01T00:59:08
#
#-------------------------------------------------

CONFIG -= app_bundle
QT += core gui

QT += sql
#CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskMan
TEMPLATE = app
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11

SOURCES += \
        Core/databaseinterface.cpp \
        Core/personage.cpp \
        Core/skill.cpp \
        Core/taskunit.cpp \
        Core/engine.cpp \
        Database/dbhandler.cpp \
        GUI/mainwindow.cpp \
        GUI/personagebutton.cpp \
        GUI/personagemenu.cpp \
        GUI/personcreatedialog.cpp \
        GUI/taskcreatedialog.cpp \
        GUI/taskform.cpp \
        GUI/skillcreatedialog.cpp \
        main.cpp

HEADERS += \
        Core/databaseinterface.h \
        Core/personage.h \
        Core/skill.h \
        Core/taskunit.h \
        Core/engine.h \
        Database/dbhandler.h \
        GUI/mainwindow.h \
        GUI/personagebutton.h \
        GUI/personagemenu.h \
        GUI/personcreatedialog.h \
        GUI/taskcreatedialog.h \
        GUI/taskform.h \
        GUI/skillcreatedialog.h

FORMS += \
        GUI/mainwindow.ui \
        GUI/personagemenu.ui \
        GUI/taskform.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
