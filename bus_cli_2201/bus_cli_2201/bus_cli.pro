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
        convert.cpp\
        c_socket.cpp

HEADERS  += mywidget.h \
    mydialog.h \
    LedUtils.h \
    packet.h \
    system.h \
    uart.h \
    led_public.h \
    convert.h   \
    c_socket.h

FORMS    += mywidget.ui \
    mydialog.ui
//CONFIG   += qtestlib

RESOURCES += \
    myResource.qrc
