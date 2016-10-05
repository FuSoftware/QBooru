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

enum PictureType{
    PREVIEW = 0,
    SAMPLE,
    FULL,
    PICTURE_TYPE_END
};

class BooruPicture
{
public:
    BooruPicture(Json::Value root, BooruSite *parent);

    int getH();
    int getW();
    string getThumbnailUrl();
    string getThumbnailPath();
    string getURL(PictureType type);
    string getFile(PictureType type);

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

    string url[PICTURE_TYPE_END];
    string url_show;

    string rating;

    string file[PICTURE_TYPE_END];
    string ext;


};

string secondsToString(int time);
int postAge(int postDate);

#endif // BOORUPICTURE_H
