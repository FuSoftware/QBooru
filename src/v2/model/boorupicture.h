#ifndef BOORUPICTURE_H
#define BOORUPICTURE_H

#include <iostream>
#include <vector>
#include <sstream> //Used for int to string conversion
#include <ctime> //Used to generate the post's age

//Used to check the Taglist, might be improved
#include <cstdio>
#include <cctype>

#include "jsonobject.h"
#include "boorusite.h"
#include "const.h"
#include "utils/conversion.h"

using namespace std;

class BooruPicture
{
public:
    BooruPicture(Json::Value root, BooruSite *parent);

    int getH();
    int getW();
    string getThumbnailUrl();
    string getThumbnailPath();

private:
    void loadGelbooru(Json::Value root);
    void loadMoebooru(Json::Value root);
    void loadDanbooru(Json::Value root);
    void loadE621(Json::Value root);
    void loadTags(string tags_str);

    BooruSite *parent;

    int id;
    string created_at;
    string author;
    string source;

    int score;
    int size;

    vector<string> taglist;
    string tags;

    int w;
    int h;

    string url_preview;
    string url_sample;
    string url_full;
    string url_show;

    string rating;

    string file_preview;
    string file_sample;
    string file_download;
    string ext;


};

string secondsToString(int time);
int postAge(int postDate);

#endif // BOORUPICTURE_H
