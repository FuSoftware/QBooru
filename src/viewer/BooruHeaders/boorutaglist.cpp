#include "boorutaglist.h"

BooruTagList::BooruTagList(string file_path, BooruSite *parent)
{
    this->file_path = file_path;
    this->site = parent;

    root = loadJSONFile(file_path.c_str());

    loadTags();
}

void BooruTagList::loadTags()
{
    int i = 0;

    while(root[i].isObject())
    {
        tags.push_back(new BooruTag(root[i],site));
        i = i+1;
    }
}

std::vector<BooruTag*> BooruTagList::getTags()
{
    return this->tags;
}

BooruTag* BooruTagList::getTag(int i)
{
    if(i < tags.size())
    {
        return tags.at(i);
    }
    else
    {
        return 0;
    }
}

int BooruTagList::size()
{
    return tags.size();
}

