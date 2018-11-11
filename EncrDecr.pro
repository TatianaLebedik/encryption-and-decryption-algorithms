#-------------------------------------------------
#
# Project created by QtCreator 2018-10-06T16:49:03
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EncrDecr
TEMPLATE = app
LIBS += -L/usr/lib/lcryptopp.a
LIBS += -lcryptopp

SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    caesar.cpp \
    trithemius.cpp \
    vernam.cpp \
    book.cpp \
    des.cpp

HEADERS  += mainwindow.h \
    data.h \
    caesar.h \
    trithemius.h \
    vernam.h \
    book.h \
    des.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
