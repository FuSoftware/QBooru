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
    std::string name;
    std::string url_search;
    std::string file_search;
    std::string url_posts;
    std::string url_login;
    std::string source;
    int start_page;

private:
    //Constructor
    API(int id, std::string name, std::string url_search, int start_page, std::string file_search, std::string url_posts, std::string url_login, std::string source)
    {
        this->id = id;
        this->name = name;
        this->url_search = url_search;
        this->file_search = file_search;
        this->url_posts = url_posts;
        this->url_login = url_login;
        this->source = source;
        this->start_page = start_page;
    }

public:
    //Properties and methods
    //Don't forget they are CONST
    API(const API* api);

    int getID()const;
    std::string getName()const;
    std::string getSearchUrl()const;
    std::string getSearchFile()const;
    std::string getPostsUrl()const;
    std::string getSource()const;
    std::string getLoginUrl()const;
    int getStartPage()const;
};
static std::vector<const API *> values();

#endif // API_H
