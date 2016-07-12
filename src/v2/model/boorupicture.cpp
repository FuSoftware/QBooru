#include "boorupicture.h"

BooruPicture::BooruPicture(Json::Value root, BooruSite *parent)
{
    this->parent = parent;

    switch(parent->getAPI()->getID())
    {
    case ID_GELBOORU:
        loadGelbooru(root);
        break;
    case ID_MOEBOORU:
        loadMoebooru(root);
        break;
    case ID_DANBOORU:
        loadDanbooru(root);
        break;
    case ID_E621:
        loadE621(root);
        break;
    }
}

void BooruPicture::loadGelbooru(Json::Value root){
    string pic;
    string dir;

    pic = root["image"].asString();
    dir = root["directory"].asString();

    /* Main Data */
    id = root["id"].asInt();
    created_at = secondsToString(root["change"].asInt());
    author = root["owner"].asString();
    score = root["score"].asInt();

    /* Size */
    this->size = 0;
    this->w = root["width"].asInt();
    this->h = root["height"].asInt();

    /* URLs */
    this->url_full = parent->getMainUrl() + std::string("/images/") + dir +std::string("/") + pic;
    this->url_preview = parent->getMainUrl() + std::string("/thumbnails/") + dir +std::string("/thumbnail_") + pic.substr(0,pic.find_last_of('.')) + std::string(".jpg"); //http://gelbooru.com/thumbnails/16/b2/thumbnail_16b2851ba391157b418d9d6cb2a3b602.jpg
    if(root["sample"].asBool())
    {
        this->url_sample = parent->getMainUrl() + std::string("/samples/") + dir +std::string("/sample_") + pic.substr(0,pic.find_last_of('.')) + std::string(".jpg");//http://simg3.gelbooru.com/samples/16/24/sample_1624d72ba640bb22adb6820dbac88f01.jpg
    }
    else
    {
        this->url_sample = parent->getMainUrl() + std::string("/images/") + dir +std::string("/") + pic;//http://simg3.gelbooru.com/images/16/b2/16b2851ba391157b418d9d6cb2a3b602.jpg
    }
    this->rating = root["rating"].asString();
    loadTags(root["tags"].asString());
}

void BooruPicture::loadMoebooru(Json::Value root){
    this->id          = root["id"].asInt();
    this->created_at  = secondsToString(postAge(root["created_at"].asInt()));
    this->author      = root["author"].asString();
    this->source      = root["source"].asString();
    this->score       = root["score"].asInt();
    this->size        = root["file_size"].asInt();
    this->url_full    = root["file_url"].asString();//File url
    this->w         = root["width"].asInt();
    this->h         = root["height"].asInt();
    this->url_preview  = root["preview_url"].asString();
    this->url_sample   = root["sample_url"].asString();
    this->rating   = root["rating"].asString();
    loadTags(root["posts"]["tags"].asString());
}

void BooruPicture::loadDanbooru(Json::Value root){
    this->id               = root["id"].asInt();
    this->created_at       = root["created_at"].asString();
    this->author           = root["uploader_name"].asString();
    this->source           = root["source"].asString();
    this->score            = root["score"].asInt();
    this->size        = root["file_size"].asInt();
    this->url_full    = parent->getMainUrl() + root["file_url"].asString();
    this->w       = root["image_width"].asInt();
    this->h      = root["image_height"].asInt();
    this->url_preview = parent->getMainUrl() + root["preview_file_url"].asString();
    this->url_sample = parent->getMainUrl() + root["large_file_url"].asString();
    this->rating = root["rating"].asString();
    loadTags(root["tag_string"].asString());
}

void BooruPicture::loadE621(Json::Value root){
    this->id               = root["id"].asInt();
    this->created_at       = secondsToString(postAge(root["created_at"]["s"].asInt()));
    this->author           = root["author"].asString();
    this->source           = root["source"].asString();
    this->score            = root["score"].asInt();
    this->size        = root["file_size"].asInt();
    this->url_full    = root["file_url"].asString();
    this->w       = root["width"].asInt();
    this->h      = root["height"].asInt();
    this->url_preview = root["preview_url"].asString();
    this->url_sample = root["sample_url"].asString();
    this->rating = root["rating"].asString();
    loadTags(root["tags"].asString());
}

void BooruPicture::loadTags(std::string tags_str)
{
    char lettre;
    string mot = "";
    unsigned int i;
    unsigned int j = 0;

    for(i=0;i<tags_str.size();i++)
    {
        lettre = tags_str.at(i);
        if(isspace(lettre))
        {
            taglist.push_back(mot);
            j++;
            mot = "";
        }
        else
        {
            mot += lettre;
        }
    }

    taglist.push_back(mot);
    mot = "";
}

string secondsToString(int time){
    int i=0;
    string timeUnit;
    string timeString;
    stringstream ss;

    while(time >= 60 && i<2)
    {
        time /= 60;
        i++;
    }

    switch(i)
    {
    case 0:
        if(time == 1){timeUnit = " sec ago";}
        else{timeUnit = " secs ago";}
        break;
    case 1:
        if(time == 1){timeUnit = " min ago";}
        else{timeUnit = " mins ago";}
        break;
    case 2:
        if(time == 1){timeUnit = " hour ago";}
        else{timeUnit = " hours ago";}
        break;
    }

    if(time >=24)
    {
        time /= 24;
        if(time == 1){timeUnit = " day ago";}
        else{timeUnit = " days ago";}

        if(time >=365)
        {
            time /= 365;
            if(time == 1){timeUnit = " year ago";}
            else{timeUnit = " years ago";}
        }
        else if(time >=30)
        {
            time /= 30;
            if(time == 1){timeUnit = " month ago";}
            else{timeUnit = " months ago";}
        }
    }

    ss << time;

    timeString = ss.str() + timeUnit;

    return timeString;
}

int postAge(int postDate){
    return time(NULL) - postDate;
}

int BooruPicture::getW(){
    return this->w;
}

int BooruPicture::getH(){
    return this->h;
}
