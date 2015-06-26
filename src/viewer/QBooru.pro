#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T23:57:28
#
#-------------------------------------------------

QT       += core gui webkitwidgets network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wno-write-strings

TARGET = QBooru
TEMPLATE = app
RC_FILE = myapp.rc

VERSION = 1.10.0.0
QMAKE_TARGET_COMPANY = Florent Uguet
QMAKE_TARGET_PRODUCT = QBooru

target.path = $$[QT_INSTALL_EXAMPLES]/qtconcurrent/runfunction
INSTALLS += target


SOURCES += main.cpp\
        widget.cpp \
    fileutils.cpp \
    classBooruSite.cpp \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_writer.cpp \
    Widget/imageTabClass.cpp \
    Widget/optionTabClass.cpp \
    Widget/searchTabClass.cpp \
    Widget/viewerTabClass.cpp \
    Widget/clickableLabel.cpp \
    Widget/BooruSettingsWidgetClass.cpp \
    Widget/booruSettingsTabClass.cpp \
    Workers/caching_thread.cpp \
    Workers/image_loading_thread.cpp \
    Workers/viewer_loading_thread.cpp \
    BooruHeaders/generic_booru_image.cpp \
    fonctions/fonctions.cpp \
    fonctions/fonctions_conversion.cpp \
    fonctions/fonctions_json.cpp \
    fonctions/fonctions_qt.cpp \
    BooruHeaders/booru_search_engine.cpp \
    config_file.cpp

HEADERS  += widget.h \
    fonctions_all.h \
    constantes.h \
    fileutils.h \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    Derpibooru/fonctionsDerpibooru.h \
    Derpibooru/imagesDerpibooru.h \
    Derpibooru/rechercheDerpibooru.h \
    Gelbooru/fonctionsGelbooru.h \
    Gelbooru/imagesGelbooru.h \
    Gelbooru/rechercheGelbooru.h \
    Moebooru/fonctionsMoebooru.h \
    Moebooru/rechercheMoebooru.h \
    Moebooru/imagesMoebooru.h \
    Widget/imageTabClass.h \
    Widget/optionTabClass.h \
    Widget/searchTabClass.h \
    Widget/viewerTabClass.h \
    Widget/clickableLabel.h \
    classBooruSite.h \
    Widget/BooruSettingsWidgetClass.h \
    Widget/booruSettingsTabClass.h \
    Danbooru/fonctionsDanbooru.h \
    Danbooru/imagesDanbooru.h \
    Danbooru/rechercheDanbooru.h \
    Workers/caching_thread.h \
    Workers/image_loading_thread.h \
    Workers/viewer_loading_thread.h \
    BooruHeaders/generic_booru_image.h \
    constantes_win.h \
    constantes_linux.h \
    BooruHeaders/headers.h \
    fonctions/fonctions.h \
    fonctions/fonctions_conversion.h \
    fonctions/fonctions_json.h \
    fonctions/fonctions_qt.h \
    BooruHeaders/booru_search_engine.h \
    config_file.h

FORMS    +=

win32:{
LIBS += "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurl.a" "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurldll.a"
}

linux:{

LIBS += -L/lib -lcurl
}

OTHER_FILES += \
    default.png \
    Backups_Fonctions.txt

