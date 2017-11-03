#include "boorusite.h"

BooruSite::BooruSite()
{

}

BooruSite::BooruSite(Json::Value obj)
{
    init(obj["name"].asString(), API::getAPIFromID(obj["api"].asInt()), obj["url_main"].asString(), obj["url_search"].asString(), obj["url_show"].asString(), obj["url_login"].asString(), obj["login_required"].asBool());
}

BooruSite::BooruSite(std::string name, std::string url, int type_id)
{
    init(name,url,API::getAPIFromID(type_id));
}

BooruSite::BooruSite(std::string name, std::string url, API *api)
{
    init(name,url,api);
}

BooruSite::BooruSite(std::string name, API *api, std::string url_main, std::string url_search, std::string url_show, std::string url_login, bool login_required)
{
    init(name, api, url_main, url_search, url_show, url_login, login_required);
}

void BooruSite::init(std::string name, std::string url, API *api){
    std::string url_main = url;
    std::string url_search = url + api->getSearchUrl();
    std::string url_show = url + api->getPostsUrl();
    std::string url_login = url + api->getLoginUrl();

    init(name, api, url_main, url_search, url_show, url_login, login_required);
}

void BooruSite::init(std::string name, API *api, std::string url_main, std::string url_search, std::string url_show, std::string url_login, bool login_required){
    this->name = name;
    this->api = api;
    this->url_main = url_main;
    this->url_search = url_search;
    this->url_show = url_show;
    this->url_login = url_login;
    this->login_required = login_required;
}

std::string BooruSite::getName(){
    return this->name;
}

std::string BooruSite::getMainUrl(){
    return this->url_main;
}

std::string BooruSite::getSearchUrl(){
    return this->url_search;
}

std::string BooruSite::getShowUrl(){
    return this->url_show;
}

std::string BooruSite::getLoginUrl(){
    return this->url_login;
}

bool BooruSite::needsLogin(){
    return this->login_required;
}

API* BooruSite::getAPI(){
    return this->api;
}

