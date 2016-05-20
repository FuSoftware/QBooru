#include "api.h"

/* Static functions/enum */
API* API::GELBOORU = new API(ID_GELBOORU, "gelbooru", "/index.php?page=dapi&json=1&s=post&q=index", "/search.json", "/index.php?page=post&s=view&id=", "/index.php?page=account&s=login&code=00", "http://gelbooru.com/index.php?page=help&topic=dapi");
API* API::MOEBOORU = new API(ID_MOEBOORU, "moebooru", "/post.json", "post.json", "/post/show/", "","https://konachan.com/help/api");
API* API::DANBOORU = new API(ID_DANBOORU, "danbooru2", "/posts.json", "posts.json", "/posts/", "","https://danbooru.donmai.us/wiki_pages/43568");
API* API::E621 = new API(ID_E621, "e621", "/post/index.json", "posts.json", "/post/show/", "","https://e621.net/help/api");

API* API::getAPIFromID(int id)
{
    for(unsigned int i=0;i<values().size();i++){
        if(values().at(i)->getID() == id){
            return new API(values().at(i));
        }
    }

    return NULL;
}

vector<const API*> values()
{
    vector<const API*> vec;
    vec.push_back(API::GELBOORU);
    vec.push_back(API::MOEBOORU);
    vec.push_back(API::DANBOORU);
    vec.push_back(API::E621);
    return vec;
}

/* Methods */
API::API(const API* api){
    this->id = api->id;
    this->name = api->name;
    this->url_search = api->url_search;
    this->file_search = api->file_search;
    this->url_posts = api->url_posts;
    this->url_login = api->url_login;
    this->source = api->source;
}

int API::getID() const
{
    return this->id;
}

string API::getName() const
{
    return this->name;
}
string API::getSearchUrl() const
{
    return this->url_search;
}
string API::getSearchFile() const
{
    return this->file_search;
}
string API::getPostsUrl() const
{
    return this->url_posts;
}
string API::getSource() const
{
    return this->source;
}

string API::getLoginUrl() const
{
    return this->url_login;
}
