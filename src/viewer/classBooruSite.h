#ifndef CLASSBOORUSITE_H_INCLUDED
#define CLASSBOORUSITE_H_INCLUDED

#include <iostream>
#include "constantes.h"
#include "json/json.h"

using namespace std;

class BooruSite
{
public:
    BooruSite(string booruName, string booruUrl, int booruType, int booruIndex);
    BooruSite(string booruName, string booruUrl, string downloadPath, int booruType, int booruIndex);
    BooruSite(string booruName, string booruUrl, string searchUrl, string tagUrl, string postIndexUrl, string downloadPath, int booruType, int booruIndex);
    BooruSite(int index);
    BooruSite(std::string name);
    BooruSite();
    ~BooruSite();
    void saveBooruSite();

    void loadFromJSON(int index);
    void loadFromJSON(std::string name);

    /*Getters*/
    string getName();
    string getTypeString();
    string getBaseUrl();
    string getSearchUrl();
    string getTagUrl();
    string getShowIndexUrl();
    string getCachePath();
    string getDownloadPath();
    string getSearchFilePath();
    string getTagFilePath();
    int getSiteTypeInt();
    int getIndex();

    /*Setters*/
    void setName(string in_name);
    void setBaseUrl(string in_base_url);
    void setSearchUrl(string in_search_url);
    void setTagUrl(string in_tag_url);
    void setShowIndexUrl(string in_show_index_url);
    void setCachePath(string in_cache_path);
    void setDownloadPath(string in_download_path);
    void setSearchFilePath(string in_search_file_path);
    void setTagFilePath(string in_tag_file_path);
    void setSiteType(int type);
    void setIndex(int i);
	
private:
    string name;
    string site_type_string;

    string base_url;
    string search_url;
    string tag_url;
    string show_index_url;

    string cache_path;
    string download_path;
    string search_file_path;
    string tag_file_path;

    int siteTypeInt;
    int index;
};

#endif
