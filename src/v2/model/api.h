#ifndef API_H
#define API_H

/* This class will store the different API const
 *
 * It works like the Java enums
 *
 * An API stores the URL extensions to the basesite to load different data, such as search pages or posts' root.
 *
 * The values are in api.cpp
 */

#include <iostream>
#include <vector>

enum ID{
    ID_GELBOORU = 0,
    ID_MOEBOORU,
    ID_DANBOORU,
    ID_E621
};

using namespace std;

class API
{
public:
    // Enum value DECLARATIONS - they are defined later
    static API* GELBOORU;
    static API* MOEBOORU;
    static API* DANBOORU;
    static API* E621;
    static API* getAPIFromID(int id);

private:
    //Private variables
    int id;
    string name;
    string url_search;
    string file_search;
    string url_posts;
    string url_login;
    string source;

private:
    //Constructor
    API(int id, string name, string url_search, string file_search, string url_posts, string url_login, string source)
    {
        this->id = id;
        this->name = name;
        this->url_search = url_search;
        this->file_search = file_search;
        this->url_posts = url_posts;
        this->url_login = url_login;
        this->source = source;
    }

public:
    //Properties and methods
    //Don't forget they are CONST
    API(const API* api);

    int getID()const;
    string getName()const;
    string getSearchUrl()const;
    string getSearchFile()const;
    string getPostsUrl()const;
    string getSource()const;
    string getLoginUrl()const;


};
static vector<const API *> values();

#endif // API_H
