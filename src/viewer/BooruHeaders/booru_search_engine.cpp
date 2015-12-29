#include "booru_search_engine.h"

BooruSearchEngine::BooruSearchEngine()
{
    has_cookie = false;
    isDump = false;
    image_count = 0;
    page = 0;
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru)
{
    has_cookie = false;
    isDump = false;
    image_count = 0;
    page = 0;
    setBooru(booru);
}

BooruSearchEngine::BooruSearchEngine(BooruSite* booru, std::string tags, int page)
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
    //Sends the tags to be logged on a remote DB
    //Only function to need Qt specific classes

    QString user_agent = "QBooru";

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    QUrl url(URL_RECORDS); //Main URL
    QUrlQuery params;

    if(has_cookie)
    {
        user_agent += " - UserID : ";
        user_agent += cookie->getCookieData(0); //Should return the UserID, for testing purposes only
    }

    request.setUrl(url.toString());
    request.setRawHeader("User-Agent", user_agent.toLatin1());
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

    params.addQueryItem("tag_req", "1");
    params.addQueryItem("page", QString::number(page));

    params.addQueryItem("tags", QString(tags_org.c_str()));
    params.addQueryItem("rating", QString::number(rating_id));
    params.addQueryItem("booru_name", QString(booru->getName().c_str()));
    params.addQueryItem("booru_url", QString(booru->getBaseUrl().c_str()));

    QByteArray data;
    data.append(params.toString()); //POST params

    QNetworkReply* m_pReply = manager->post(request,data);
    QTimer timer(0);
    timer.setInterval(1000); //1s timeout

    QObject::connect(&timer, SIGNAL(timeout()),m_pReply, SLOT(abort()));
    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    //qDebug() <<  m_pReply->readAll();

    if(m_pReply->error() != QNetworkReply::NoError)
    {
        outputInfo(L_ERROR,std::string("Error when sending tags : ") + m_pReply->errorString().toStdString());
        outputInfo(L_ERROR,std::string("Full reply : ") +  m_pReply->readAll().toStdString());
        return m_pReply->error();
    }

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
