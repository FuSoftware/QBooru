#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/*
 * Set this to 0 to change to the relative paths for the program (Release)
 * Set this to 1 to change to the absolute paths for the program (Debug)
 */
#define DEBUG 0

#define CURL_STATICLIB
#define APP_NAME "QBooru Updater"
#define APP_VERSION "1.1.2.0"
#define APP_QT_VER "55"

#define CONF_FILE_URL "https://raw.githubusercontent.com/FlorentUguet/QBooru/master/builds/latest/conf/configuration.json"
#define CHANGELOG_FILE_URL "https://github.com/FlorentUguet/QBooru/raw/master/changelog.html"
#define LAST_VERSION_FILE_URL "https://github.com/FlorentUguet/QBooru/raw/master/versions1.json"
#define LAST_EXECUTABLE_FILE_URL "https://github.com/FlorentUguet/QBooru/raw/master/builds/latest/QBooru.exe"

#define VERSION_CONTROL_DIGITS 4

enum InfoLevel
{
    LEVEL_CACHING = 1,
    LEVEL_SEARCH,
    LEVEL_FOLDER_MANIP,
    LEVEL_UPDATER,
    LEVEL_TOP_WIDGET
};

#ifdef _WIN32
    #include "constantes_win.h"
#elif __linux
    #include "constantes_linux.h"
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

#endif // CONSTANTES

