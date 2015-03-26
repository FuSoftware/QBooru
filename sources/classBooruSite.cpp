#include <iostream>
#include "classBooruSite.h"
#include "constantes.h"
#include "fonctions.h"
#include "json/json.h"

BooruSite::BooruSite(std::string booruName, std::string booruUrl, int booruType, int booruIndex)
{
    outputInfo("INFO",std::string("Setting up type 1: ") + booruName,LEVEL_TOP_WIDGET);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = std::string(downloadPath()) + booruName;
    tag_file_path_base = tag_file_path = CONFPATH + std::string("tags") + booruName;

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
    case DANBOORU_TYPE:
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
    outputInfo("INFO",std::string("Setting up type 2: ") + booruName,LEVEL_TOP_WIDGET);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = downloadPath;
    tag_file_path_base = tag_file_path = CONFPATH + std::string("tags") + booruName;

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
    case DANBOORU_TYPE:
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
    outputInfo("INFO",std::string("Setting up type 3: ") + booruName,LEVEL_TOP_WIDGET);
    index = booruIndex;
    std::string tag_file_path_base;

    name = booruName;
    base_url = booruUrl;

    cache_path = CACHE_PATH + booruName + "/";
    download_path = downloadPath;
    tag_file_path_base = tag_file_path = CONFPATH + std::string("tags") + booruName;

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
    case DANBOORU_TYPE:
        search_file_path = cache_path + "post.json";
        tag_file_path = tag_file_path_base + ".json";
        site_type_string = "danbooru";
        break;
    }
}

BooruSite::BooruSite()
{

}

BooruSite::~BooruSite()
{

}

void BooruSite::saveBooruSite()
{
    outputInfo("INFO",std::string("Saving ") + name,LEVEL_TOP_WIDGET);
    Json::Value root = loadJSONFile(CONF_FILE);

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
                 index<< std::endl;


    Json::StyledWriter writer;

    root["boorus"][index] = root["boorus"][index-1];

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

    std::string output = writer.write(root);

    saveJSONFile(CONF_FILE, output);
}
