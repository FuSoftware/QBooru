#ifndef BOORUSITE_H
#define BOORUSITE_H

/* This class holds the data that will identify different websites
 *
 * It generates, from the main URL and the API all the required URLs
 *
 *
 */

#include <iostream>
#include "api.h"
#include "../json/json.h"

class BooruSite
{
public:
    BooruSite();
    BooruSite(Json::Value obj);
    BooruSite(std::string name, std::string url, int type_id);
    BooruSite(std::string name, std::string url, API *api);
    BooruSite(std::string name, API *api, std::string url_main, std::string url_search, std::string url_show, std::string url_login, bool login_required);

    std::string getName();
    std::string getMainUrl();
    std::string getSearchUrl();
    std::string getShowUrl();
    std::string getLoginUrl();
    int getStartPage();
    bool needsLogin();
    API *getAPI();

private:
    void init(std::string name, std::string url, API *api);
    void init(std::string name, API *api, std::string url_main, std::string url_search, std::string url_show, std::string url_login, bool login_required);

    std::string name;
    API *api;

    std::string url_main;
    std::string url_search;
    std::string url_show;
    std::string url_login;

    bool login_required;

};

#endif // BOORUSITE_H
