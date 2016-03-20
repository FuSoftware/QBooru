#include "booru_search_engine.h"

BooruSearchEngine::BooruSearchEngine(QObject *parent) : QObject(parent)
{
    has_cookie = false;
    isDump = false;
    image_count = 0;
    page = 0;
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru, QObject *parent) : QObject(parent)
{
    has_cookie = false;
    isDump = false;
    image_count = 0;
    page = 0;
    setBooru(booru);
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru, std::string tags, int page, QObject *parent) : QObject(parent)
{
    has_cookie = false;
    isDump = false;
    image_count = 0;
    page = 0;
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
    tags_org = tags;

    QUrlQuery params;

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
        if(!tags.empty()){search_extension = "?q="+tags;}
        if(page>0){search_extension += ("&page=" + intToString(page));}
        search_extension += ("&key="+derpibooru_api_key);
        break;
    case GELBOORU_TYPE:
        /*Debut de la requete de recherche*/
        if(image_count>0){params.addQueryItem("limit", QString::number(image_count));}
        if(!tags.empty()){params.addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params.addQueryItem("pid", QString::number(page-1));}
        search_extension += "&";
        break;
    case MOEBOORU_TYPE:
        /*Debut de la requete de recherche*/
        params.addQueryItem("api_version", QString::number(2));
        if(image_count>0){params.addQueryItem("limit", QString::number(image_count));}
        if(!tags.empty()){params.addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params.addQueryItem("page", QString::number(page));}
        search_extension += "?";
        break;
    case DANBOORU2_TYPE:
        /*Debut de la requete de recherche*/
        if(image_count>0){params.addQueryItem("limit", QString::number(image_count));}
        if(!tags.empty()){params.addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params.addQueryItem("page", QString::number(page));}
        search_extension += "?";
        break;
    case E621_TYPE:
        /*Debut de la requete de recherche*/
        if(image_count>0){params.addQueryItem("limit", QString::number(image_count));}
        if(!tags.empty()){params.addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params.addQueryItem("page", QString::number(page));}
        search_extension += "?";
        break;
    }
    search_extension += params.toString().toStdString();
}

void BooruSearchEngine::search()
{
    search_url = booru->getSearchUrl() + search_extension;

    if(has_cookie)
    {
        if(!cookie->isEmpty())
        {
            qDebug() << "Querying search file with cookies for" << booru->getName().c_str();
            downloadFile(search_url.c_str(), booru->getSearchFilePath().c_str(),cookie,true,false,false);
        }
        else
        {
            qDebug() << "Querying search file for" << booru->getName().c_str();
            downloadFile(search_url.c_str(), booru->getSearchFilePath().c_str(),true,false,false);
        }
    }
    else
    {
        qDebug() << "Querying search file for" << booru->getName().c_str();
        downloadFile(search_url.c_str(), booru->getSearchFilePath().c_str(),true,false,false);
    }

    qDebug() << search_url.c_str();

    if(!isDump)
    {
        logSearch();
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
    if(!cookie->isEmpty()){setCookie(cookie);}
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
    case E621_TYPE:
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

void BooruSearchEngine::setDump(bool isDump)
{
    this->isDump = isDump;
}

int BooruSearchEngine::getResultSize()
{
    Json::Value root = loadJSONFile(booru->getSearchFilePath().c_str());

    int n = 0;

    switch(booru->getSiteTypeInt())
    {
    case DERPIBOORU_TYPE:
        n = root.size() + 0;
        break;
    case GELBOORU_TYPE:
        n = root.size();
        break;
    case MOEBOORU_TYPE:
        n = root["posts"].size() + 0;
        break;
    case DANBOORU2_TYPE:
        n = root.size();
        break;
    default:
        n = -1;
    }

    qDebug() << n << "posts";

    return n;
}

int BooruSearchEngine::logSearch()
{
    QThread *thread = new QThread(this);
    worker = new SearchLoggingWorker(this->tags_org,this->rating_id,this->page,this->booru);

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

    return 0;
}


int BooruSearchEngine::getPage()
{
    return this->page;
}

CookieJar *BooruSearchEngine::getCookie()
{
    if(has_cookie)
    {
        return this->cookie;
    }
    else
    {
        return 0;
    }
}

std::string BooruSearchEngine::getTags()
{
    return this->tags;
}

bool BooruSearchEngine::hasCookie()
{
    return this->has_cookie;
}
