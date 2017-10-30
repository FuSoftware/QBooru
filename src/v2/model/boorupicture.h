#ifndef BOORUPICTURE_H
#define BOORUPICTURE_H

#include <iostream>
#include <vector>
#include <sstream> //Used for int to std::string conversion
#include <ctime> //Used to generate the post's age

//Used to check the Taglist, might be improved
#include <cstdio>
#include <cctype>

#include "jsonobject.h"
#include "boorusite.h"

#include "const.h"
#include "utils/conversion.h"

enum PictureType{
    PREVIEW = 0,
    PREVIEW_JPG,
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
    int getID();

    std::string getThumbnailUrl();
    std::string getThumbnailPath();
    std::string getURL(int type);
    std::string getFile(int type);
    std::string getShowUrl();

    std::string getAuthor();
    std::string getCreationDate();
    BooruSite* getWebsite();
    int getScore();

private:
    void loadGelbooru(Json::Value root);
    void loadMoebooru(Json::Value root);
    void loadDanbooru(Json::Value root);
    void loadE621(Json::Value root);
    void loadTags(std::string tags_str);

    BooruSite *parent;

    int id;
    std::string created_at;
    std::string author;
    std::string source;

    int score;
    int size;

    vector<std::string> taglist;
    std::string tags;

    int w;
    int h;

    std::string url[PICTURE_TYPE_END];
    std::string url_show;

    std::string rating;

    std::string file[PICTURE_TYPE_END];
    std::string ext;


};

std::string secondsToString(int time);
int postAge(int postDate);

#endif // BOORUPICTURE_H
