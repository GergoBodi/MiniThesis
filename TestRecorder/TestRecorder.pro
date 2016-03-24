#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T14:58:15
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestRecorder
TEMPLATE = app


SOURCES += main.cpp \
    dialog.cpp \
    Parameter.cpp \
    voiceprocessor.cpp \
    globalvars.cpp \
    fft.cpp \
    melfilter.cpp

HEADERS  += \
    dialog.h \
    Parameter.h \
    voiceprocessor.h \
    globalvars.h \
    fft.h \
    melfilter.h

FORMS    += \
    dialog.ui
