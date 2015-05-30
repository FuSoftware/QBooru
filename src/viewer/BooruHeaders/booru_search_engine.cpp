#include "booru_search_engine.h"

BooruSearchEngine::BooruSearchEngine()
{

}

BooruSearchEngine::BooruSearchEngine(BooruSite booru)
{
    setBooru(booru);
}

BooruSearchEngine::BooruSearchEngine(BooruSite booru, std::string tags, int page)
{
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

    std::replace(tags.begin(), tags.end(), ' ', '+');

    switch(booru.getSiteTypeInt())
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
    search_url = booru.getSearchUrl() + search_extension;
    cachingFile(strdup(search_url.c_str()), strdup(booru.getSearchFilePath().c_str()),true,false);
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

void BooruSearchEngine::setRating(int rating_id)
{
    rating_extension = "";

    switch(booru.getSiteTypeInt())
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

void BooruSearchEngine::setBooru(BooruSite booru)
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

