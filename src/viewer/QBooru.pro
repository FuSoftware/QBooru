#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T23:57:28
#
#-------------------------------------------------

QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wno-write-strings -std=c++11

TARGET = QBooru
TEMPLATE = app
RC_FILE = myapp.rc

VERSION = 1.12.5.0
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
    config_file.cpp \
    BooruHeaders/boorutag.cpp \
    BooruHeaders/boorutaglist.cpp \
    Workers/file_downloader.cpp \
    Workers/qnamredirect.cpp \
    Workers/cookiejar.cpp \
    Widget/qstartupwidget.cpp \
    Widget/qdownloadwidget.cpp \
    Workers/imagegrabber.cpp \
    Widget/grabberwidget.cpp \
    Workers/downloadworker.cpp

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
    Widget/imageTabClass.h \
    Widget/optionTabClass.h \
    Widget/searchTabClass.h \
    Widget/viewerTabClass.h \
    Widget/clickableLabel.h \
    classBooruSite.h \
    Widget/BooruSettingsWidgetClass.h \
    Widget/booruSettingsTabClass.h \
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
    config_file.h \
    BooruHeaders/boorutag.h \
    BooruHeaders/boorutaglist.h \
    Workers/file_downloader.h \
    Workers/qnamredirect.h \
    Workers/cookiejar.h \
    Widget/qstartupwidget.h \
    Widget/qdownloadwidget.h \
    Workers/imagegrabber.h \
    Widget/grabberwidget.h \
    Workers/downloadworker.h

FORMS    +=

OTHER_FILES += \
    default.png \
    Backups_Fonctions.txt

static { # everything below takes effect with CONFIG ''= static
 CONFIG+= static
 DEFINES+= STATIC
 message("~~~ static build ~~~") # this is for information, that the static build is done
 #mac: TARGET = $$join(TARGET,,,_static) #this adds an _static in the end, so you can seperate static build from non static build
 #win32: TARGET = $$join(TARGET,,,s) #this adds an s in the end, so you can seperate static build from non static build
}

