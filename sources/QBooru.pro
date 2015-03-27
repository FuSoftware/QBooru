#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T23:57:28
#
#-------------------------------------------------

QT       += core gui webkitwidgets network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBooru
TEMPLATE = app
RC_FILE = myapp.rc

target.path = $$[QT_INSTALL_EXAMPLES]/qtconcurrent/runfunction
INSTALLS += target


SOURCES += main.cpp\
        widget.cpp \
    fonctions.cpp \
    fileutils.cpp \
    fonctionsSDL.cpp \
    sdlglutils.cpp \
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
    Widget/loadingWidget.cpp \
    BooruHeaders/danbooru_fonctions.cpp \
    BooruHeaders/danbooru_recherche.cpp \
    BooruHeaders/derpibooru_fonctions.cpp \
    BooruHeaders/derpibooru_recherche.cpp \
    BooruHeaders/gelbooru_fonctions.cpp \
    BooruHeaders/gelbooru_recherche.cpp \
    BooruHeaders/moebooru_fonctions.cpp \
    BooruHeaders/moebooru_recherche.cpp \
    Workers/caching_thread.cpp \
    Workers/image_loading_thread.cpp \
    Workers/viewer_loading_thread.cpp \
    tinyxml2/tinyxml2.cpp \
    BooruHeaders/generic_booru_image.cpp \
    BooruHeaders/generic_booru_fonctions.cpp

HEADERS  += widget.h \
    fonctions.h \
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
    fonctionsSDL.h \
    sdlglutils.h \
    Widget/clickableLabel.h \
    classBooruSite.h \
    Widget/BooruSettingsWidgetClass.h \
    Widget/booruSettingsTabClass.h \
    Widget/loadingWidget.h \
    Danbooru/fonctionsDanbooru.h \
    Danbooru/imagesDanbooru.h \
    Danbooru/rechercheDanbooru.h \
    BooruHeaders/danbooru_fonctions.h \
    BooruHeaders/danbooru_recherche.h \
    BooruHeaders/derpibooru_fonctions.h \
    BooruHeaders/derpibooru_recherche.h \
    BooruHeaders/gelbooru_fonctions.h \
    BooruHeaders/gelbooru_recherche.h \
    BooruHeaders/moebooru_fonctions.h \
    BooruHeaders/moebooru_recherche.h \
    Workers/caching_thread.h \
    Workers/image_loading_thread.h \
    Workers/viewer_loading_thread.h \
    tinyxml2/tinyxml2.h \
    BooruHeaders/generic_booru_image.h \
    BooruHeaders/generic_booru_fonctions.h \
    constantes_win.h \
    constantes_linux.h \
    BooruHeaders/headers.h

FORMS    +=

win32:{
LIBS += "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurl.a" "E:/Qt/Qt5.4.1/5.4/mingw491_32/lib/libcurldll.a"
#SDL
INCLUDEPATH+=E:\lib\SDL-devel-1.2.15-mingw32\SDL-1.2.15\include
LIBS += -LE:\lib\SDL-devel-1.2.15-mingw32\SDL-1.2.15\lib -llibSDL
#SDL_Image
INCLUDEPATH+=E:\lib\SDL_image-devel-1.2.12-VC\SDL_image-1.2.12\include
LIBS += -LE:\lib\SDL_image-devel-1.2.12-VC/SDL_image-1.2.12/lib/x86 -lSDL_image
#SDL_GFX
INCLUDEPATH+=E:\lib\SDL_gfx\SDL_gfx\include
LIBS += -LE:\lib\SDL_gfx\SDL_gfx\lib -lsdlgfx
}

linux:{

LIBS += -L/lib -lcurl
LIBS += -L/lib -lSDL
LIBS += -L/lib -lSDL_image
LIBS += -L/lib -lSDL_gfx
LIBS += -L/lib -lGLU
}

OTHER_FILES += \
    default.png \
    Backups_Fonctions.txt

