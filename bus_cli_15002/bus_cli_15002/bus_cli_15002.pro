#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T15:03:47
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network
TARGET = myDialog1
TEMPLATE = app


SOURCES +=\
        mywidget.cpp \
        mydialog.cpp \
        main.cpp \
        crc.cpp \
        LedUtils.cpp \
        packet.cpp \
        led_public.cpp \
        convert.c\
        c_socket.cpp\
        tts.c \
        utf8togb2312.c
HEADERS  += mywidget.h \
    mydialog.h \
    LedUtils.h \
    packet.h \
    system.h \
    uart.h \
    led_public.h \
    convert.h   \
    c_socket.h \
    tts.h

FORMS    += mywidget.ui \
    mydialog.ui
//CONFIG   += qtestlib

RESOURCES += \
    myResource.qrc
