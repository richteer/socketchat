#-------------------------------------------------
#
# Project created by QtCreator 2013-12-06T02:26:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = socketchat
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11
LIBS += -lgmp -lmcrypt

SOURCES += main.cpp\
        mainwindow.cpp \
    crypto/number.c \
    crypto/elgamal.c \
    crypto/aes.c \
    net/packet.c \
    net/network.c \
    net/cryptnet.c

HEADERS  += mainwindow.h \
    crypto/number.h \
    crypto/elgamal.h \
    crypto/aes.h \
    net/packet.h \
    net/network.h \
    net/cryptnet.h

FORMS    += mainwindow.ui
