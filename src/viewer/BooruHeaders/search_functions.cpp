#include "search_functions.h"

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
