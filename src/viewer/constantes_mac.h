/*
 * constantes_mac.h
 *
 * Contains all the absolute and relative paths for the program, if compiled on Mac OS.
 * It eases the Debug process by allowing the executable to run directly from Qt "Run" option, by having it read the files from any folder.
 */

#ifndef CONSTANTES_MAC
#define CONSTANTES_MAC

#include "constantes.h"

#define OS_ID "Mac OS"

#if DEBUG
/**Mac OS Debug**/

        #define CACHE_PATH  "/usr/share/qbooru/cache/"
        #define DOWNLOAD_PATH  "/usr/share/qbooru/downloads/"
        #define CONF_PATH     "/usr/share/qbooru/conf/"
        #define CONF_FILE    "/usr/share/qbooru/conf/configuration.json"
        #define LOG_FILE    "/usr/share/qbooru/programLog.log"
        #define ICON_PATH "/usr/share/qbooru/conf/defaultDerpibooru.png"

        #define CACHE_PATH_DERPIBOORU    "/usr/share/qbooru/cache/derpibooru/"

        #define CHANGELOG_FILE "/usr/share/qbooru/conf/changelog.txt"
        #define LAST_VERSION_FILE "/usr/share/qbooru/conf/lastVersion.json"

        #define UPDATER_MAIN_EXECUTABLE "/usr/share/qbooru/QBooruUpdater"
        #define LOADING_GIF "/usr/share/qbooru/conf/loader.gif"

        #define BOORU_LIST "/usr/share/qbooru/conf/boorulist.json"

        #define EXECUTABLE "/usr/share/qbooru/QBooru"
        #define EXECUTABLE_DL "/usr/share/qbooru/QBooru.dl"

#else
    /**Mac OS Release**/

        #define CACHE_PATH  "cache/"
        #define DOWNLOAD_PATH  "downloads/"
        #define CONF_PATH     "conf/"
        #define CONF_FILE    "conf/configuration.json"
        #define LOG_FILE    "programLog.log"
        #define ICON_PATH "conf/icon.ico"

        #define CACHE_PATH_DERPIBOORU    "cache/derpibooru/"

        #define CHANGELOG_FILE "conf/changelog.txt"
        #define LAST_VERSION_FILE "conf/lastVersion.json"

        #define UPDATER_MAIN_EXECUTABLE "QBooruUpdater"
        #define LOADING_GIF "/conf/loader.gif"

        #define BOORU_LIST "conf/boorulist.json"

        #define EXECUTABLE "QBooru"
        #define EXECUTABLE_DL "QBooru.dl"
#endif

#endif // CONSTANTES_MAC

