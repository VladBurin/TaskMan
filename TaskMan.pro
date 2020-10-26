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

#configuring modules to bild
DEFINES += TASK_MAN_GUI

#include CORE & DBHandler
HEADERS += \
        Core/character.h \
        Core/databaseinterface.h \
        Core/skill.h \
        Core/engine.h \
        Core/task.h \
        \
        Database/dbhandler.h

SOURCES += \
        main.cpp \
        Core/character.cpp \
        Core/databaseinterface.cpp \
        Core/skill.cpp \
        Core/engine.cpp \
        Core/task.cpp \
        \
        Database/dbhandler.cpp

#include GUI
contains(DEFINES,TASK_MAN_GUI) {
    HEADERS += \
            GUI/mainwindow.h \
            GUI/taskform.h \
            GUI/characterbutton.h \
            GUI/charactermenu.h \
            \
            GUI/dialogs/delchardialog.h \
            GUI/dialogs/editchardialog.h \
            GUI/dialogs/charactercreatedialog.h \
            GUI/dialogs/taskcreatedialog.h \
            GUI/dialogs/skillcreatedialog.h


    SOURCES += \
            GUI/characterbutton.cpp \
            GUI/charactermenu.cpp \
            GUI/mainwindow.cpp \
            GUI/taskform.cpp \
            \
            GUI/dialogs/delchardialog.cpp \
            GUI/dialogs/editchardialog.cpp \
            GUI/dialogs/charactercreatedialog.cpp \
            GUI/dialogs/taskcreatedialog.cpp \
            GUI/dialogs/skillcreatedialog.cpp

    FORMS += \
            GUI/charactermenu.ui \
            GUI/mainwindow.ui \
            GUI/taskform.ui \
            GUI/dialogs/taskcreatedialog.ui
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

