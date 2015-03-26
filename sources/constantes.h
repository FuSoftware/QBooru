#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define DEBUG 1

#define CURL_STATICLIB
#define APP_NAME "QBooru Viewer"
#define APP_VERSION "1.7.5"
#define TAG_NUMBER    512
#define MAX_BOORU_NUMBER 64
#define MAX_PICTURE_NUMBER 64
#define LAYOUT_NUMBER_OPTIONS 8

#define CONF_FILE_URL "http://www.aht.li/2475858/configuration_-_defaut.json"
#define CHANGELOG_FILE_URL "http://www.aht.li/2460180/changelog.txt"
#define LAST_VERSION_FILE_URL "http://www.aht.li/2475899/lastVersion.json"

enum InfoLevel
{
    LEVEL_CACHING = 1,
    LEVEL_SEARCH,
    LEVEL_FOLDER_MANIP,
    LEVEL_UPDATER,
    LEVEL_TOP_WIDGET
};

enum HostType
{
  DERPIBOORU_TYPE = 0,
  GELBOORU_TYPE,
  MOEBOORU_TYPE,
  DANBOORU_TYPE
};

enum Ratings
{
  RATING_ALL = 0,
  RATING_SAFE,
  RATING_QUESTIONNABLE,
  RATING_EXPLICIT
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

#endif // CONSTANTES_H_INCLUDED
