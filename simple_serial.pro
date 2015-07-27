#-------------------------------------------------
#
# Project created by QtCreator 2015-06-16T14:40:07
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = simple_serial
TEMPLATE = app
CONFIG   += staticlib

MOC_DIR        = compile
OBJECTS_DIR    = compile
UI_DIR         = compile

SOURCES += main.cpp\
           view/mainwindow.cpp \
           model/interface.cpp \
    model/log.cpp \
    view/form_reset_kanal.cpp \
    model/table_model.cpp \
    model/setting.cpp \
    view/form_setting_port.cpp \
    controller/port_processing.cpp \
    controller/serial_processing.cpp \
    view/form_setting_kanal.cpp

HEADERS += view/mainwindow.h \
           model/interface.h \
    model/log.h \
    view/form_reset_kanal.h \
    util/core.h \
    model/table_model.h \
    model/setting.h \
    view/form_setting_port.h \
    controller/port_processing.h \
    controller/serial_processing.h \
    view/form_setting_kanal.h

FORMS   += view/mainwindow.ui \
    view/form_reset_kanal.ui \
    view/form_setting_port.ui \
    view/form_setting_kanal.ui

RESOURCES += \
    icon.qrc
