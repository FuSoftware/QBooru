#include "boorusdatabase.h"

BoorusDatabase::BoorusDatabase()
{
    settings = new QSettings(QString(DB_FILE),QSettings::IniFormat);
}

void BoorusDatabase::addBooru(BooruSite* booru)
{
    settings->beginGroup(booru->getName().c_str());
    settings->setValue("url_main",booru->getMainUrl().c_str());
    settings->setValue("url_login",booru->getLoginUrl().c_str());
    settings->setValue("url_search",booru->getSearchUrl().c_str());
    settings->setValue("url_show",booru->getShowUrl().c_str());
    settings->setValue("api_id",booru->getAPI()->getID());
    settings->setValue("login_required",booru->needsLogin());
    settings->endGroup();
}

BooruSite* BoorusDatabase::loadFromSettings(QString name)
{
    //qDebug() << "Loading booru" << name;

    QString url_main = settings->value(name + "/url_main").toString();
    QString url_login = settings->value(name + "/url_login").toString();
    QString url_search = settings->value(name + "/url_search").toString();
    QString url_show = settings->value(name + "/url_show").toString();
    int api_id = settings->value(name + "/api_id").toInt();
    bool needsLogin = settings->value(name + "/login_required").toBool();

    return new BooruSite(name.toStdString(),
                         API::getAPIFromID(api_id),
                         url_main.toStdString(),
                         url_search.toStdString(),
                         url_show.toStdString(),
                         url_login.toStdString(),
                         needsLogin);
}

BooruSite* BoorusDatabase::loadBooru(int i)
{
    return loadBoorus().at(i);
}

std::vector<BooruSite*> BoorusDatabase::loadBoorus()
{
    //qDebug() << settings->allKeys();

    QStringList booru_names = settings->childGroups();
    std::vector<BooruSite*> sites;

    for(int i=0;i<booru_names.size();i++)
    {
        sites.push_back(loadFromSettings(booru_names.at(i)));
    }

    return sites;
}
