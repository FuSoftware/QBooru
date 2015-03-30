/*
 * constantes_win.h
 *
 * Contains all the absolute and relative paths for the program, if compiled on Windows.
 * It eases the Debug process by allowing the executable to run directly from Qt "Run" option, by having it read the files from any folder.
 */

#ifndef CONSTANTES_WIN
#define CONSTANTES_WIN

#include "constantes.h"

#define OS_ID "Windows"

#if DEBUG
/**Windows Debug**/

        #define CACHE_PATH  "E:/QBooru/QBooru/cache/"
        #define CONFPATH     "E:/QBooru/QBooru/conf/"
        #define CONF_FILE    "E:/QBooru/QBooru/conf/configuration.json"
        #define LOG_FILE    "E:/QBooru/QBooru/programLog.log"
        #define ICON_PATH "E:/QBooru/QBooru/conf/defaultDerpibooru.png"

        #define CACHE_PATH_DERPIBOORU    "E:/QBooru/QBooru/cache/derpibooru/"

        #define CHANGELOG_FILE "E:/QBooru/QBooru/conf/changelog.html"
        #define LAST_VERSION_FILE "E:/QBooru/QBooru/conf/lastVersion.json"

        #define VIEWER_MAIN_EXECUTABLE "E:/QBooru/QBooru/QBooru.exe"
        #define LOADING_GIF "E:/QBooru/QBooru/conf/loader.gif"

#else
    /**Windows Release**/

        #define CACHE_PATH  "cache/"
        #define CONFPATH     "conf/"
        #define CONF_FILE    "conf/configuration.json"
        #define LOG_FILE    "programLog.log"
        #define ICON_PATH "conf/icon.ico"

        #define CACHE_PATH_DERPIBOORU    "cache/derpibooru/"

        #define CHANGELOG_FILE "conf/changelog.html"
        #define LAST_VERSION_FILE "conf/lastVersion.json"

        #define VIEWER_MAIN_EXECUTABLE "QBooru.exe"
        #define LOADING_GIF "/conf/loader.gif"
#endif
#endif // CONSTANTES_WIN

