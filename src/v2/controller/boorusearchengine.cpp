#include "boorusearchengine.h"

BooruSearchEngine::BooruSearchEngine(BooruSite *parent)
{
    this->page = 0;
    this->limit = 15;
    this->tags = "";
    this->parent = parent;
}

QUrlQuery* BooruSearchEngine::generateRequest(string tags, int page, int limit)
{
    QUrlQuery *params = new QUrlQuery;

    switch(parent->getAPI()->getID()){
    case ID_GELBOORU:
        if(limit>0){params->addQueryItem("limit", QString::number(limit));}
        if(!tags.empty()){params->addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params->addQueryItem("pid", QString::number(page-1));}
        break;
    case ID_DANBOORU:
        if(limit>0){params->addQueryItem("limit", QString::number(limit));}
        if(!tags.empty()){params->addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params->addQueryItem("page", QString::number(page));}
        break;
    case ID_MOEBOORU:
        params->addQueryItem("api_version", QString::number(2));
        if(limit>0){params->addQueryItem("limit", QString::number(limit));}
        if(!tags.empty()){params->addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params->addQueryItem("page", QString::number(page));}
        break;
    case ID_E621:
        if(limit>0){params->addQueryItem("limit", QString::number(limit));}
        if(!tags.empty()){params->addQueryItem("tags", QString(tags.c_str()));}
        if(page>0){params->addQueryItem("page", QString::number(page));}
        break;
    }

    return params;
}

vector<BooruPicture*> BooruSearchEngine::search(string tags)
{
    set(tags);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(int page)
{
    set(page);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(string tags, int page)
{
    set(tags,page);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(string tags, int page, int limit)
{
    set(tags,page,limit);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search()
{
    QUrlQuery *params = generateRequest(tags, page, limit);

    QString url = QString(parent->getSearchUrl().c_str());

    if(parent->getAPI()->getID() == ID_GELBOORU){url += "&";}
    else{url += "?";}

    outputInfo(L_DEBUG,"Querying " + parent->getSearchUrl() + " with params " + params->toString().toStdString());
    QNetworkReply *reply = ConnectionManager().execGetRequest(QUrl(url),params);
    QString json = QString(reply->readAll());

    return parse(json);
}

vector<BooruPicture*> BooruSearchEngine::parse(QString data)
{
    outputInfo(L_DEBUG,"Parsing JSON");
    Json::Value root = loadJSONString(data.toStdString());
    vector<BooruPicture*> pictures;

    int size = 0;

    switch(parent->getAPI()->getID()){
    case ID_MOEBOORU:
        size = root["posts"].size();
        for(int i=0;i<size;i++){
            Json::Value child = root["posts"][i];
            pictures.push_back(new BooruPicture(child,parent));
        }
        break;
    case ID_GELBOORU:
    case ID_DANBOORU:
    case ID_E621:
        size = root.size();
        for(int i=0;i<size;i++){
            Json::Value child = root[i];
            pictures.push_back(new BooruPicture(child,parent));
        }
        break;
    }

    outputInfo(L_DEBUG,"JSON parsed, " + QString(QString::number(size)).toStdString() + " pictures loaded");

    return pictures;
}

void BooruSearchEngine::set(string tags)
{
    this->tags = tags;
}

void BooruSearchEngine::set(int page)
{
    this->page = page;
}

void BooruSearchEngine::set(string tags, int page)
{
    this->tags = tags;
    this->page = page;
}

void BooruSearchEngine::set(string tags, int page, int limit)
{
    this->tags = tags;
    this->page = page;
    this->limit = limit;
}
