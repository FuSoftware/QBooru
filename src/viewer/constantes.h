/*
 * constantes.h
 *
 * Contains app name and app version
 *
 * Contains main URLs for updates
 *
 * Contains all the unvariable values for the program
 *
 * Contains all Enums
 * - InfoLevel for ouputting priorities
 * - HostType to list all possible host APIs
 * - Ratings to list the search ratings (Safe, Quest., Explicit)
 *
 * Contains links to Linux and Windows paths for both Debug and Release
 *
 */

#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/*
 * Set this to 0 to change to the relative paths for the program (Release)
 * Set this to 1 to change to the absolute paths for the program (Debug)
 */

#define DEBUG 0

#define CURL_STATICLIB
#define APP_NAME "QBooru Viewer"
#define APP_VERSION "1.10.5.1"
#define TAG_NUMBER    512 //Max number of tags to show in the Viewer
#define MAX_BOORU_NUMBER 64 //Max number of Boorus to load in the main widget
#define MAX_PICTURE_NUMBER 64 //Max number of pictures/page

#define CONF_FILE_URL "https://raw.githubusercontent.com/FlorentUguet/QBooru/master/builds/latest/conf/configuration.json"
#define CHANGELOG_FILE_URL "https://github.com/FlorentUguet/QBooru/raw/master/changelog.html"
#define LAST_VERSION_FILE_URL "https://github.com/FlorentUguet/QBooru/raw/master/versions.json"
#define UPDATER_URL "https://github.com/FlorentUguet/QBooru/raw/master/builds/latest/QBooruUpdater.exe"
#define BOORU_LIST_URL "https://github.com/FlorentUguet/QBooru/raw/master/boorulist.json"

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
  DANBOORU2_TYPE, //Reffered as "danbooru" in the JSON files
  DANBOORU_TYPE //Not used for now
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
