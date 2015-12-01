#include "booru_search_engine.h"

BooruSearchEngine::BooruSearchEngine()
{
    has_cookie = false;
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru)
{
    has_cookie = false;
    setBooru(booru);
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru, std::string tags, int page)
{
    has_cookie = false;
    setBooru(booru);
    setTags(tags);
    setPage(page);
}

BooruSearchEngine::~BooruSearchEngine()
{

}

void BooruSearchEngine::generateUrlExtension()
{
    search_extension = "";
    size_t index = 0;

    if(rating_id != RATING_ALL)
    {
        tags += rating_extension;
    }

    std::replace(tags.begin(), tags.end(), ' ', '+');

    switch(booru->getSiteTypeInt())
    {
    case DERPIBOORU_TYPE:
        while (true){index = tags.find(",", index);if (index == string::npos) break;tags.replace(index, 1, "%2C");}
        /*Debut de la requete de recherche*/
        search_extension = "?q="+tags;
        search_extension += ("&page=" + intToString(page));
        search_extension += ("&key="+derpibooru_api_key);
        break;
    case GELBOORU_TYPE:
        /*Debut de la requete de recherche*/
        search_extension = "&limit=";
        search_extension += intToString(image_count);
        search_extension += ("&tags=" + tags);
        search_extension += ("&pid="+intToString(page-1));
        break;
    case MOEBOORU_TYPE:
        /*Debut de la requete de recherche*/
        search_extension = "?api_version=2";
        search_extension += "&limit=";
        search_extension += intToString(image_count);
        search_extension += ("&tags=" + tags);
        search_extension += ("&page=" + intToString(page));
        break;
    case DANBOORU2_TYPE:
        /*Debut de la requete de recherche*/
        search_extension = "?limit=";
        search_extension += intToString(image_count);
        search_extension += ("&tags=" + tags);
        search_extension += ("&page=" + intToString(page));
        break;
    }
}

void BooruSearchEngine::search()
{
    search_url = booru->getSearchUrl() + search_extension;

    if(!cookie->isEmpty())
    {
        qDebug() << "Querying search file with cookies";
        downloadFile(search_url.c_str(), booru->getSearchFilePath().c_str(),cookie,true,false,false);
    }
    else
    {
        downloadFile(search_url.c_str(), booru->getSearchFilePath().c_str(),true,false,false);
    }

}

void BooruSearchEngine::search(std::string tags)
{
    setTags(tags);
    generateUrlExtension();
    search();
}

void BooruSearchEngine::search(int page)
{
    setPage(page);
    generateUrlExtension();
    search();
}

void BooruSearchEngine::search(std::string tags, int page)
{
    setTags(tags);
    setPage(page);
    generateUrlExtension();
    search();
}

void BooruSearchEngine::search(std::string tags, int page, CookieJar* cookie)
{
    setCookie(cookie);
    setTags(tags);
    setPage(page);
    generateUrlExtension();
    search();
}

void BooruSearchEngine::setCookie(CookieJar *cookie)
{
    this->cookie = cookie;
    has_cookie = true;
}

void BooruSearchEngine::setRating(int rating_id)
{
    rating_extension = "";
    this->rating_id = rating_id;

    switch(booru->getSiteTypeInt())
    {
    case DERPIBOORU_TYPE:
        switch(rating_id)
        {
        case RATING_SAFE:
            rating_extension = ",safe";
            break;
        case RATING_QUESTIONNABLE:
            rating_extension = ",questionable";
            break;
        case RATING_EXPLICIT:
            rating_extension = ",explicit" ;
            break;
        }
        break;
    case GELBOORU_TYPE:
        switch(rating_id)
        {
        case RATING_SAFE:
            rating_extension = " rating:safe";
            break;
        case RATING_QUESTIONNABLE:
            rating_extension = " rating:questionable";
            break;
        case RATING_EXPLICIT:
            rating_extension = " rating:explicit" ;
            break;
        }
        break;
    case MOEBOORU_TYPE:
    case DANBOORU2_TYPE:
        switch(rating_id)
        {
        case RATING_SAFE:
            rating_extension = " rating:s";
            break;
        case RATING_QUESTIONNABLE:
            rating_extension = " rating:q";
            break;
        case RATING_EXPLICIT:
            rating_extension = " rating:e" ;
            break;
        }
    }
}

void BooruSearchEngine::setBooru(BooruSite *booru)
{
    this->booru = booru;
}

void BooruSearchEngine::setTags(std::string tags)
{
    this->tags = tags;
}

void BooruSearchEngine::setPage(int page)
{
    this->page = page;
}

void BooruSearchEngine::setImageCount(int count)
{
    this->image_count = count;
}

void BooruSearchEngine::setApiKey(std::string key)
{
    this->derpibooru_api_key = key;
}

