#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "danbooru2_recherche.h"
#include "fonctions_all.h"
#include "danbooru2_fonctions.h"

int setTagsDanbooru2(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex)
{
        int operationState;
        std::string urlString;
        std::replace(recherche.begin(), recherche.end(), ' ', '+');

        /*Debut de la requete de recherche*/
        urlString = "?limit=";
        urlString += intToString(image_count);
        urlString += ("&tags=" + recherche);
        urlString += ("&page="+page);

        operationState = rechercheTagsDanbooru2(stringToCString(urlString), stringToCString(cachePath), stringToCString(searchIndex));

        return operationState;
}

int rechercheTagsDanbooru2(char* url, char* cachePath, char* searchIndex)
{
    /*Définition des variables*/
    int cacheState;
    char *outfilename;
    QString stringUrl = "";
    QString stringOutFilename = "";
    char *completeUrl;

    /*Création des chemins*/
    stringUrl = QString(searchIndex) + QString(url);
    stringOutFilename = QString(cachePath) + QString("posts.json");

    QByteArray ba1 = stringUrl.toLocal8Bit();
    QByteArray ba2 = stringOutFilename.toLocal8Bit();

    completeUrl =  ba1.data();
    outfilename = ba2.data();

    /*Mise du json en cache*/
    cacheState = cachingFile(completeUrl, outfilename,true, false);

    return cacheState;
}

