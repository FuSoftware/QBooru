#ifndef CLASSBOORUSITE_H_INCLUDED
#define CLASSBOORUSITE_H_INCLUDED

#include <iostream>

using namespace std;

class BooruSite
{
public:
    BooruSite(string booruName, string booruUrl, int booruType, int booruIndex);
    BooruSite(string booruName, string booruUrl, string downloadPath, int booruType, int booruIndex);
    BooruSite(string booruName, string booruUrl, string searchUrl, string tagUrl, string postIndexUrl, string downloadPath, int booruType, int booruIndex);
    BooruSite();
    ~BooruSite();
    void saveBooruSite();

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
	
private:
};

#endif
