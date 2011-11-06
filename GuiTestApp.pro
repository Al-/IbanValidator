#-----------------------------------------------------------
#
# Project created by NecessitasQtCreator 2011-11-05T16:38:19
#
#-----------------------------------------------------------

QT       += core gui

TARGET = GuiTestApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        ../kmymoney/kmymoney/wizards/newaccountwizard/ibanvalidator.cpp

HEADERS  += mainwindow.h \
        ../kmymoney/kmymoney/wizards/newaccountwizard/ibanvalidator.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
