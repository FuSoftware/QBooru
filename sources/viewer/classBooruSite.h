/*
 * classBooruSite.h
 *
 * Contains all basic variables to be able to use Booru Websites such as : (Examples given for Safebooru)
 * - Name             (Safebooru)
 * - Type             (gelbooru)
 * - Base URL         ("http://safebooru.org")
 * - Search URL       ("http://safebooru.org/index.php?page=dapi&s=post&q=index")
 * - Taglist URL      ("http://safebooru.org/index.php?page=dapi&s=tag&q=index&order=name&limit=0")
 * - Post index URL   ("http://safebooru.org/index.php?page=post&s=view&id=")
 *
 * - Cache path       ("cache/Safebooru/")
 * - Download path    ("downloads/Safebooru/")
 * - Search File Path ("cache/Safebooru/search.xml")
 * - Tag file path    ("conf/tagsSafebooru.xml")
 */

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
