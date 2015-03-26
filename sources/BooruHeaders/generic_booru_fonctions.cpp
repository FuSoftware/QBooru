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

QString cacheImageGeneric(BooruImage imageCache, std::string cachePath, SearchTab *parent, int i)
{
    std::stringstream out;
    out << imageCache.id;
    /** */
    std::string fileName;
    std::string format;

    /*Récupération de l'URL*/
    std::string string_url = imageCache.preview_url;

    /*Récupération de l'extension*/
    fileName = imageCache.preview_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    std::string string_file_name = cachePath + out.str()+ "." + format;

    /*Si le fichier existe, on ne cache pas, s'il est inexistant, on cache*/
    std::cerr << "File " << string_file_name << " at " << string_url << std::endl;

    cachingFile(stringToCString(string_url),stringToCString(string_file_name),false,true);

    return QString(string_file_name.c_str());
}

QString cacheImageMediumGeneric(BooruImage imageCache, std::string cachePath, bool keepCache)
{
    std::stringstream out;
    out << imageCache.id;
    /** */
    std::string fileName;
    std::string format;

    /*Récupération de l'URL*/
    std::string string_url = imageCache.sample_url;

    /*Récupération de l'extension*/
    fileName = imageCache.sample_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    std::string string_file_name;

    /*Si le fichier existe, on ne cache pas, s'il est inexistant, on cache*/
    std::cerr << "File " << string_file_name << " at " << string_url << std::endl;

    /** */

    if(keepCache)
    {
        string_file_name = cachePath + out.str()+ "." + "_medium" + format;
    }
    else
    {
        string_file_name = cachePath + "medium" + "." + format;
    }

    cachingFile(stringToCString(string_url),stringToCString(string_file_name),true,false);

    return QString(string_file_name.c_str());
}

QString saveImageFullGeneric(BooruImage imageCache, std::string downloadPath)
{
    char *cacheUrlChar;
    char *fichierSortieChar;
    char *formatChar;
    std::string format;
    QString fichierSortieString = "";
    std::string fileName;

    QDir dir2(downloadPath.c_str());
    if (!dir2.exists()) {
        dir2.mkpath(".");
    }

    /*Récupération de l'extension*/
    cacheUrlChar = stringToCString(imageCache.file_url.c_str());
    fileName     = imageCache.file_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    formatChar = strdup(format.data());


    fichierSortieString = QString(downloadPath.c_str()) + QString::number(imageCache.id) + QString("_full.") + formatChar;
    QByteArray ba2 = fichierSortieString.toLocal8Bit();
    fichierSortieChar = ba2.data();

    cachingFile(cacheUrlChar, fichierSortieChar,false, true);

    return fichierSortieString;
}
