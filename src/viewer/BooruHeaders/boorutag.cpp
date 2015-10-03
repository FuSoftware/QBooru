#include "boorutag.h"

BooruTag::BooruTag(Json::Value root, BooruSite *parent)
{
    this->site = parent;
    loadFromJson(root);
}

void BooruTag::loadFromJson(Json::Value root)
{
    switch(site->getSiteTypeInt())
    {
    case DERPIBOORU_TYPE:
        break;
    case GELBOORU_TYPE:
        break;
    case MOEBOORU_TYPE:
        this->id    = root["id"].asInt();
        this->name  = root["name"].asString();
        this->count = root["count"].asInt();
        this->type  = root["type"].asInt();
        break;
    case DANBOORU2_TYPE:
        this->id    = root["id"].asInt();
        this->name  = root["name"].asString();
        this->count = root["post_count"].asInt();
        this->type  = root["category"].asInt();
        break;
    }

    switch(this->type)
    {
    case TAG_COMMON:
        type_name = "Common";
        break;
    case TAG_ARTIST:
        type_name = "Artist";
        break;
    case TAG_CHARA:
        type_name = "Character";
        break;
    default:
        type_name = "Undefined";
        break;
    }
}

int BooruTag::getId()
{
    return this->id;
}

std::string BooruTag::getName()
{
    return this->name;
}

int BooruTag::getCount()
{
    return this->count;
}

int BooruTag::getCategory()
{
    return this->type;
}

std::string BooruTag::getCategoryType()
{
    return this->type_name;
}
