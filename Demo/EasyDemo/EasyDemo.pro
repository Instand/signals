QT += core
QT += gui
QT += widgets

CONFIG += c++11

TARGET = EasyDemo

TEMPLATE = app

SOURCES += main.cpp \
    signaldemo.cpp \
    anyclass.cpp

HEADERS += \
    signaldemo.h \
    anyclass.h \
    easysignals.h \
    ../../src/easysignals.h
