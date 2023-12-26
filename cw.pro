#-------------------------------------------------
#
# Project created by QtCreator 2023-12-12T21:50:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cw
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
    addrecord.cpp \
    editrecord.cpp \
    helpinformation.cpp \
    database.cpp \
    tickets.cpp

HEADERS += \
        mainwindow.h \
    addrecord.h \
    editrecord.h \
    helpinformation.h \
    database.h \
    tickets.h

FORMS += \
        mainwindow.ui \
    addrecord.ui \
    editrecord.ui \
    helpinformation.ui \
    tickets.ui

RESOURCES += \
    resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
