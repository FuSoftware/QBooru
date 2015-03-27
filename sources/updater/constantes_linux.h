/*
 * constantes_linux.h
 *
 * Contains all the absolute and relative paths for the program, if compiled on Linux.
 * It eases the Debug process by allowing the executable to run directly from Qt "Run" option, by having it read the files from any folder.
 */

#ifndef CONSTANTES_LINUX
#define CONSTANTES_LINUX

#include "constantes.h"

#define OS_ID "Linux"

#if DEBUG
/**Linux Debug**/

        #define CACHE_PATH  "/usr/share/qbooru/cache/"
        #define CONFPATH     "/usr/share/qbooru/conf/"
        #define CONF_FILE    "/usr/share/qbooru/conf/configuration.json"
        #define LOG_FILE    "/usr/share/qbooru/programLog.log"
        #define ICON_PATH "/usr/share/qbooru/conf/defaultDerpibooru.png"

        #define CACHE_PATH_DERPIBOORU    "/usr/share/qbooru/cache/derpibooru/"

        #define CHANGELOG_FILE "/usr/share/qbooru/conf/changelog.txt"
        #define LAST_VERSION_FILE "/usr/share/qbooru/conf/lastVersion.json"

        #define VIEWER_MAIN_EXECUTABLE "/usr/share/qbooru/QBooru"
        #define LOADING_GIF "/usr/share/qbooru/conf/loader.gif"

#else
    /**Linux Release**/

        #define CACHE_PATH  "cache/"
        #define CONFPATH     "conf/"
        #define CONF_FILE    "conf/configuration.json"
        #define LOG_FILE    "programLog.log"
        #define ICON_PATH "conf/icon.ico"

        #define CACHE_PATH_DERPIBOORU    "cache/derpibooru/"

        #define CHANGELOG_FILE "conf/changelog.txt"
        #define LAST_VERSION_FILE "conf/lastVersion.json"

        #define VIEWER_MAIN_EXECUTABLE "QBooru"
        #define LOADING_GIF "/conf/loader.gif"
#endif

#endif // CONSTANTES_LINUX

