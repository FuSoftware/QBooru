#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <QFile>

#include "moebooru_recherche.h"
#include "fonctions.h"
#include "moebooru_fonctions.h"

int setTagsMoebooru(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex)
{
    int operationState;
    std::string urlString;
    std::replace(recherche.begin(), recherche.end(), ' ', '+');

    /*Debut de la requete de recherche*/
    urlString = "?api_version=2";
    urlString += "&limit=";
    urlString += intToString(image_count);
    urlString += ("&tags=" + recherche);
    urlString += ("&page="+page);

    operationState = rechercheTagsMoebooru(urlString, cachePath, searchIndex);

    return operationState;
}

int rechercheTagsMoebooru(std::string recherche, std::string cachePath, std::string searchIndex)
{
    searchIndex += recherche;
    cachePath += "post.json";

    /*Mise du json en cache*/
    //outputInfo("DEBUG",std::string(recherche + " " + cachePath),LEVEL_TOP_WIDGET);
    int cacheState = cachingFile(stringToCString(searchIndex), stringToCString(cachePath),true, false);

    return cacheState;
}

