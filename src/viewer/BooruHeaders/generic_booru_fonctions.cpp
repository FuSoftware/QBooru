#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <sstream>
#include "widget.h"

#include <QString>
#include <QDir>

#include "../json/json.h"

#include "constantes.h"
#include "fonctions.h"
#include "generic_booru_fonctions.h"

QString cacheImageGeneric(BooruImage imageCache, std::string cachePath)
{
    std::stringstream out;
    out << imageCache.id;
    /** */
    std::string fileName;
    std::string format;

    /*Gets the URL*/
    std::string string_url = imageCache.preview_url;

    /*Get the file's extension*/
    fileName = imageCache.preview_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    std::string string_file_name = cachePath + out.str()+ "." + format;

    /*Downloads file if it doesn't exist already*/
    cachingFile(stringToCString(string_url),stringToCString(string_file_name),false,true);

    return QString(string_file_name.c_str());// returns file path
}

QString cacheImageMediumGeneric(BooruImage imageCache, std::string cachePath, bool keepCache)
{
    std::stringstream out;
    out << imageCache.id;
    /** */
    std::string fileName;
    std::string format;

    /*Gets the URL*/
    std::string string_url = imageCache.sample_url;

    /*Get the file's extension*/
    fileName = imageCache.sample_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    std::string string_file_name;

    if(keepCache)
    {
        /*Changes name to "id_medium.ext" if requested in the settings*/
        string_file_name = cachePath + out.str()+ "." + "_medium" + format;
    }
    else
    {
        /*Keeps "medium.ext" and overrides any previous file with the same name*/
        string_file_name = cachePath + "medium" + "." + format;
    }

    cachingFile(stringToCString(string_url),stringToCString(string_file_name),true,false);

    return QString(string_file_name.c_str());// returns file path
}

QString saveImageFullGeneric(BooruImage imageCache, std::string downloadPath)
{
    char *cacheUrlChar;
    char *fichierSortieChar;
    char *formatChar;
    std::string format;
    QString fichierSortieString = "";
    std::string fileName;

    /*Checks if the download folder exists*/
    checkFolder(downloadPath);

    /*Sets remote file URL*/
    cacheUrlChar = stringToCString(imageCache.file_url.c_str());

    /*Gets extension*/
    fileName     = imageCache.file_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    formatChar = strdup(format.data());

    /*Sets local file path*/
    fichierSortieString = QString(downloadPath.c_str()) + QString::number(imageCache.id) + QString("_full.") + formatChar;
    QByteArray ba2 = fichierSortieString.toLocal8Bit();
    fichierSortieChar = ba2.data();

    cachingFile(cacheUrlChar, fichierSortieChar,false, true);

    return fichierSortieString;// returns file path
}
