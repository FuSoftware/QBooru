#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <QString>
#include <QFile>

#include "derpibooru_recherche.h"
#include "fonctions_all.h"
#include "derpibooru_fonctions.h"


int setTagsDerpibooru(std::string recherche, std::string page, std::string apiKey, std::string cachePath, std::string searchIndex)
{
    int operationState;
    std::string urlString;
    std::replace(recherche.begin(), recherche.end(), ' ', '+');

    size_t index = 0;
    while (true)
    {
         index = recherche.find(",", index);
         if (index == string::npos) break;
         recherche.replace(index, 1, "%2C");
    }

    /*Debut de la requete de recherche*/
    urlString = "?q="+recherche;
    urlString += ("&page="+page);
    urlString += ("&key="+apiKey);

    operationState = rechercheTagsDerpibooru(urlString,cachePath,searchIndex);

    return operationState;

}

int rechercheTagsDerpibooru(std::string urlExtension, std::string cachePath, std::string searchIndex)
{
    cachePath += "search.json";
    searchIndex += urlExtension;

    int cacheState = cachingFile(stringToCString(searchIndex), stringToCString(cachePath),true, false);

    return cacheState;
}

