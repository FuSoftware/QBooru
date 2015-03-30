#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T09:10:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBooruUpdater
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    fonctions.cpp \
    fonctions_json.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp

HEADERS  += widget.h \
    fonctions.h \
    constantes.h \
    fonctions_json.h \
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
    constantes_linux.h \
    constantes_win.h

DISTFILES += \
    json/sconscript

win32:{
    LIBS += "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurl.a" "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurldll.a"
}

linux:{

    LIBS += -L/lib -lcurl
}
