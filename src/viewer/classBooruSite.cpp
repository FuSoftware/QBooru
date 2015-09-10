#include "classBooruSite.h"
#include "fonctions_all.h"

BooruSite::BooruSite(std::string booruName, std::string booruUrl, int booruType, int booruIndex)
{
    outputInfo(L_DEBUG,std::string("Setting up type 1: ") + booruName);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = std::string(downloadPath()) + booruName;
    tag_file_path_base = tag_file_path = CONF_PATH + std::string("tags") + booruName;

    siteTypeInt = booruType;

    switch(booruType)
    {
    case DERPIBOORU_TYPE:
        search_url = base_url + "/search.json";
        tag_url = base_url + "/tags.json";

        search_file_path = cache_path + "search.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "derpibooru";
        break;
    case GELBOORU_TYPE:
        show_index_url = base_url + "/index.php?page=post&s=view&id=";
        search_url = base_url + "/index.php?page=dapi&json=1&s=post&q=index";
        tag_url = base_url + "/index.php?page=dapi&s=tag&q=index&order=name&limit=0";

        search_file_path = cache_path + "/search.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "gelbooru";
        break;
    case MOEBOORU_TYPE:
        show_index_url = booruUrl + "/post/show/";
        search_url = base_url + "/post.json";
        tag_url = base_url + "/tag.json?limit=0";

        search_file_path = cache_path + "post.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "moebooru";
        break;
    case DANBOORU2_TYPE:
        show_index_url = booruUrl + "/posts/";
        search_url = base_url + "/posts.json";
        tag_url = base_url + "/tag.json?limit=0";

        search_file_path = cache_path + "posts.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "danbooru";
        break;
    }
}

BooruSite::BooruSite(std::string booruName, std::string booruUrl, std::string downloadPath, int booruType, int booruIndex)
{
    outputInfo(L_DEBUG,std::string("Setting up type 2: ") + booruName);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = downloadPath;
    tag_file_path_base = tag_file_path = CONF_PATH + std::string("tags") + booruName;

    siteTypeInt = booruType;

    switch(booruType)
    {
    case DERPIBOORU_TYPE:
        search_url = base_url + "/search.json";
        tag_url = base_url + "/tags.json";

        search_file_path = cache_path + "search.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "derpibooru";
        break;
    case GELBOORU_TYPE:
        show_index_url = base_url + "/index.php?page=post&s=view&id=";
        search_url = base_url + "/index.php?page=dapi&s=post&q=index";
        tag_url = "/index.php?page=dapi&s=tag&q=index&order=name&limit=0";

        search_file_path = cache_path + "/search.xml";
        tag_file_path = tag_file_path_base + ".xml";
        site_type_string = "gelbooru";
        break;
    case MOEBOORU_TYPE:
        show_index_url = booruUrl + "/post/show/";
        search_url = base_url + "/post.json";
        tag_url = base_url + "/tag.json?limit=0";

        search_file_path = cache_path + "post.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "moebooru";
        break;
    case DANBOORU2_TYPE:
        show_index_url = booruUrl + "/posts/";
        search_url = base_url + "/posts.json";
        tag_url = base_url + "/tag.json?limit=0";

        search_file_path = cache_path + "posts.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "danbooru";
        break;
    }
}

BooruSite::BooruSite(std::string booruName, std::string booruUrl, std::string searchUrl, std::string tagUrl, std::string postIndexUrl, std::string downloadPath, int booruType,  int booruIndex)
{
    outputInfo(L_DEBUG,std::string("Setting up type 3: ") + booruName);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = downloadPath;
    tag_file_path_base = tag_file_path = CONF_PATH + std::string("tags") + booruName;

    siteTypeInt = booruType;
    search_url = searchUrl;
    tag_url = tagUrl;
    show_index_url = postIndexUrl;

    switch(booruType)
    {
    case DERPIBOORU_TYPE:
        search_file_path = cache_path + "search.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "derpibooru";
        break;
    case GELBOORU_TYPE:
        search_file_path = cache_path + "/search.xml";
        tag_file_path = tag_file_path_base + ".xml";
        site_type_string = "gelbooru";
        break;
    case MOEBOORU_TYPE:
        search_file_path = cache_path + "post.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "moebooru";
        break;
    case DANBOORU2_TYPE:
        search_file_path = cache_path + "post.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "danbooru";
        break;
    }
}

BooruSite::BooruSite(int index)
{
    loadFromJSON(index);
}

BooruSite::BooruSite(Json::Value booru_root)
{
    loadFromJSON(booru_root);
}

BooruSite::BooruSite()
{

}

BooruSite::~BooruSite()
{

}

Json::Value BooruSite::saveBooruSite(Json::Value root)
{
    outputInfo(L_INFO,std::string("Saving ") + name);
    //Json::Value root = loadJSONFile(CONF_FILE);

    /*
    std::cout << name << " parameters : " << std::endl <<
                site_type_string << std::endl <<
                base_url << std::endl <<
                search_url << std::endl <<
                tag_url << std::endl <<
                cache_path<< std::endl <<
                 download_path<< std::endl <<
                 search_file_path<< std::endl <<
                 tag_file_path<< std::endl <<
                 siteTypeInt<< std::endl <<
                 index<< std::endl;*/

    root["boorus"][index]["name"] = name;

    root["boorus"][index]["site_type_string"] = site_type_string;

    root["boorus"][index]["base_url"] = base_url;
    root["boorus"][index]["search_url"] = search_url;
    root["boorus"][index]["tag_url"] = tag_url;
    root["boorus"][index]["show_index_url"] = show_index_url;

    root["boorus"][index]["cache_path"] = cache_path;
    root["boorus"][index]["download_path"] = download_path;
    root["boorus"][index]["search_file_path"] = search_file_path;
    root["boorus"][index]["tag_file_path"] = tag_file_path;

    root["boorus"][index]["siteTypeInt"] = siteTypeInt;
    root["boorus"][index]["index"] = index;

    if(index >= (root["settings"]["booru_number"].asInt()))
    {
        root["settings"]["booru_number"] = index+1;
    }

    return root;
}

void BooruSite::loadFromJSON(int index)
{
    Json::Value root = loadJSONFile(CONF_FILE);

                 name = root["boorus"][index]["name"].asString();
     site_type_string = root["boorus"][index]["site_type_string"].asString();

              base_url = root["boorus"][index]["base_url"].asString();
            search_url = root["boorus"][index]["search_url"].asString();
               tag_url = root["boorus"][index]["tag_url"].asString();
        show_index_url = root["boorus"][index]["show_index_url"].asString();

           cache_path = root["boorus"][index]["cache_path"].asString();
        download_path = root["boorus"][index]["download_path"].asString();
     search_file_path = root["boorus"][index]["search_file_path"].asString();
        tag_file_path = root["boorus"][index]["tag_file_path"].asString();

    siteTypeInt = root["boorus"][index]["siteTypeInt"].asInt();
    this->index = index;
}

void BooruSite::loadFromJSON(Json::Value booru_root)
{  
            name = booru_root["name"].asString();
            outputInfo(L_DEBUG,
                       std::string("Loading from JSON ") + this->getName());

        site_type_string = booru_root["site_type_string"].asString();

              base_url = booru_root["base_url"].asString();
            search_url = booru_root["search_url"].asString();
               tag_url = booru_root["tag_url"].asString();
        show_index_url = booru_root["show_index_url"].asString();

              cache_path = booru_root["cache_path"].asString();
           download_path = booru_root["download_path"].asString();
        search_file_path = booru_root["search_file_path"].asString();
           tag_file_path = booru_root["tag_file_path"].asString();

        siteTypeInt = booru_root["siteTypeInt"].asInt();

            index = booru_root["index"].asInt();
}

/*Getters*/
string BooruSite::getName()
{
    return name;
}

string BooruSite::getTypeString()
{
    return site_type_string;
}

string BooruSite::getBaseUrl()
{
    return base_url;
}

string BooruSite::getSearchUrl()
{
    return search_url;
}

string BooruSite::getTagUrl()
{
    return tag_url;
}

string BooruSite::getShowIndexUrl()
{
    return show_index_url;
}

string BooruSite::getCachePath()
{
    return cache_path;
}

string BooruSite::getDownloadPath()
{
    return download_path;
}

string BooruSite::getSearchFilePath()
{
    return search_file_path;
}

string BooruSite::getTagFilePath()
{
    return tag_file_path;
}

int BooruSite::getSiteTypeInt()
{
    return siteTypeInt;
}

int BooruSite::getIndex()
{
    return index;
}

/*Setters*/
void BooruSite::setName(string in_name)
{
    name = in_name;
}

void BooruSite::setBaseUrl(string in_base_url)
{
    base_url = in_base_url;
}

void BooruSite::setSearchUrl(string in_search_url)
{
    search_url = in_search_url;
}

void BooruSite::setTagUrl(string in_tag_url)
{
    tag_url = in_tag_url;
}

void BooruSite::setShowIndexUrl(string in_show_index_url)
{
    show_index_url = in_show_index_url;
}

void BooruSite::setCachePath(string in_cache_path)
{
    cache_path = in_cache_path;
}

void BooruSite::setDownloadPath(string in_download_path)
{
    download_path = in_download_path;
}

void BooruSite::setSearchFilePath(string in_search_file_path)
{
    search_file_path = in_search_file_path;
}

void BooruSite::setTagFilePath(string in_tag_file_path)
{
    tag_file_path = in_tag_file_path;
}

void BooruSite::setSiteType(int type)
{
    siteTypeInt = type;

    switch(siteTypeInt)
    {
    case DERPIBOORU_TYPE:
        site_type_string = "derpibooru";
        break;
    case GELBOORU_TYPE:
        site_type_string = "gelbooru";
        break;
    case MOEBOORU_TYPE:
        site_type_string = "moebooru";
        break;
    case DANBOORU2_TYPE:
        site_type_string = "danbooru";
        break;
    }
}

void BooruSite::setIndex(int i)
{
    index = i;
}
