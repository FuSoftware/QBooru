#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T21:57:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBooru
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    model/boorupicture.cpp \
    controller/boorusearchengine.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp \
    model/api.cpp \
    model/boorusite.cpp \
    utils/json.cpp \
    utils/output.cpp \
    utils/file.cpp \
    model/jsonobject.cpp \
    controller/connectionmanager.cpp \
    tests.cpp \
    controller/boorusdatabase.cpp

HEADERS  += mainwidget.h \
    model/boorupicture.h \
    controller/boorusearchengine.h \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/json_tool.h \
    json/reader.h \
    json/value.h \
    json/version.h.in \
    json/writer.h \
    model/api.h \
    model/boorusite.h \
    utils/json.h \
    utils/output.h \
    utils/file.h \
    model/jsonobject.h \
    controller/connectionmanager.h \
    tests.h \
    controller/boorusdatabase.h

DISTFILES += \
    json/sconscript
