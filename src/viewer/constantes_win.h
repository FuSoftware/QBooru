/*
 * constantes_win.h
 *
 * Contains all the absolute and relative paths for the program, if compiled on Windows.
 * It eases the Debug process by allowing the executable to run directly from Qt "Run" option, by having it read the files from any folder.
 *
 * To debug easily, just replace the paths in the "Windows Debug" section with your absolute paths to the file
 */

#ifndef CONSTANTES_WIN
#define CONSTANTES_WIN

#include "constantes.h"

#if DEBUG
/**Windows Debug**/

        #define OS_ID "Windows Debug"

        #define CACHE_PATH  "F:/My Programs/Builds/QBooru/cache/"
        #define CONF_PATH     "F:/My Programs/Builds/QBooru/conf/"
        #define CONF_FILE    "F:/My Programs/Builds/QBooru/conf/configuration.json"
        #define LOG_FILE    "F:/My Programs/Builds/QBooru/programLog.log"
        #define ICON_PATH "F:/My Programs/Builds/QBooru/conf/defaultDerpibooru.png"

        #define CACHE_PATH_DERPIBOORU    "F:/My Programs/Builds/QBooru/cache/derpibooru/"

        #define CHANGELOG_FILE "F:/My Programs/Builds/QBooru/conf/changelog.txt"
        #define LAST_VERSION_FILE "F:/My Programs/Builds/QBooru/conf/lastVersion.json"

        #define UPDATER_MAIN_EXECUTABLE "F:/My Programs/Builds/QBooru/QBooruUpdater.exe"
        #define LOADING_GIF "F:/My Programs/Builds/QBooru/conf/loader.gif"

        #define BOORU_LIST "F:/My Programs/Builds/QBooru/conf/boorulist.json"

#else
    /**Windows Release**/
        #define OS_ID "Windows"

        #define CACHE_PATH  "cache/"
        #define CONF_PATH     "conf/"
        #define CONF_FILE    "conf/configuration.json"
        #define LOG_FILE    "programLog.log"
        #define ICON_PATH "conf/icon.ico"

        #define CACHE_PATH_DERPIBOORU    "cache/derpibooru/"

        #define CHANGELOG_FILE "conf/changelog.txt"
        #define LAST_VERSION_FILE "conf/lastVersion.json"

        #define UPDATER_MAIN_EXECUTABLE "QBooruUpdater.exe"
        #define LOADING_GIF "/conf/loader.gif"

        #define BOORU_LIST "conf/boorulist.json"
#endif
#endif // CONSTANTES_WIN

