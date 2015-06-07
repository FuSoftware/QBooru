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

        #define CACHE_PATH  "E:/My Programs/Builds/QBooru/cache/"
        #define CONFPATH     "E:/My Programs/Builds/QBooru/conf/"
        #define CONF_FILE    "E:/My Programs/Builds/QBooru/conf/configuration.json"
        #define LOG_FILE    "E:/My Programs/Builds/QBooru/programLog.log"
        #define ICON_PATH "E:/My Programs/Builds/QBooru/conf/defaultDerpibooru.png"

        #define CACHE_PATH_DERPIBOORU    "E:/My Programs/Builds/QBooru/cache/derpibooru/"

        #define CHANGELOG_FILE "E:/My Programs/Builds/QBooru/conf/changelog.html"
        #define LAST_VERSION_FILE "E:/My Programs/Builds/QBooru/conf/lastVersion.json"

        #define VIEWER_MAIN_EXECUTABLE "E:/My Programs/Builds/QBooru/QBooru.exe"
        #define LOADING_GIF "E:/My Programs/Builds/QBooru/conf/loader.gif"

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

