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
    BooruSite(string name, string url, int type_id);
    BooruSite(string name, string url, API *api);
    BooruSite(string name, API *api, string url_main, string url_search, string url_show, string url_login, bool login_required);

    string getName();
    string getMainUrl();
    string getSearchUrl();
    string getShowUrl();
    string getLoginUrl();
    bool needsLogin();
    API *getAPI();

private:
    void init(string name, string url, API *api);
    void init(string name, API *api, string url_main, string url_search, string url_show, string url_login, bool login_required);

    string name;
    API *api;

    string url_main;
    string url_search;
    string url_show;
    string url_login;

    bool login_required;

};

#endif // BOORUSITE_H
