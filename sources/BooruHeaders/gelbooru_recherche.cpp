#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gelbooru_recherche.h"
#include "fonctions.h"
#include "gelbooru_fonctions.h"

int setTagsGelbooru(std::string recherche, int page, int image_count, std::string searchFile, std::string fileUrl)
{    
    int operationState;
    std::string urlString;
    std::replace(recherche.begin(), recherche.end(), ' ', '+');

    /*Debut de la requete de recherche*/
    urlString = "&limit=";
    urlString += intToString(image_count);
    urlString += ("&tags=" + recherche);
    urlString += ("&pid="+intToString(page-1));

    operationState = rechercheTagsGelbooru(urlString, searchFile, fileUrl);

    return operationState;
}

int rechercheTagsGelbooru(std::string urlExtension, std::string searchFile, std::string url)
{
    /*Définition des variables*/
    int cacheState;
    std::string stringUrl = "";

    char* searchFileChar = stringToCString(searchFile);

    /*Création des chemins*/
    stringUrl = url + urlExtension;

    /*Mise du XML en cache*/
    cacheState = cachingFile(stringToCString(stringUrl), searchFileChar,true, false);

    return cacheState;
}
