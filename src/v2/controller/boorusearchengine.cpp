#include "boorusearchengine.h"

BooruSearchEngine::BooruSearchEngine(BooruSite *parent)
{
    this->page = 0;
    this->limit = 15;
    this->tags = "";
    this->parent = parent;
}

QString BooruSearchEngine::generateRequest(QString tags, int page, int limit)
{
    return QString::fromStdString(this->parent->getSearchUrl()).arg(tags, QString::number(page), QString::number(limit));
}

vector<BooruPicture*> BooruSearchEngine::search(QString tags)
{
    set(tags);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(int page)
{
    set(page);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(QString tags, int page)
{
    set(tags,page);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search(QString tags, int page, int limit)
{
    set(tags,page,limit);
    return search();
}

vector<BooruPicture*> BooruSearchEngine::search()
{
    //Builds the URL from the locally stored elements
    QString url = generateRequest(tags, page, limit);
    outputInfo(L_DEBUG,"Querying " + url.toStdString());

    //Queries the remote file and parses it
    QNetworkReply *reply = ConnectionManager::execGetRequest(QUrl(url));
    QString json = QString(reply->readAll());

    //Deletes the replie's pointer to prevent memory leaks
    delete reply;

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

void BooruSearchEngine::set(QString tags)
{
    this->tags = tags;
}

void BooruSearchEngine::set(int page)
{
    this->page = page;
}

void BooruSearchEngine::set(QString tags, int page)
{
    this->tags = tags;
    this->page = page;
}

void BooruSearchEngine::set(QString tags, int page, int limit)
{
    this->tags = tags;
    this->page = page;
    this->limit = limit;
}
