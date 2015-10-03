#ifndef BOORUTAGLIST_H
#define BOORUTAGLIST_H

#include <iostream>
#include <vector>

#include "./fonctions_all.h"

#include "boorutag.h"

class BooruSite;
class BooruTag;

class BooruTagList
{
public:
    BooruTagList(std::string file_path, BooruSite *parent);

    void loadTags();
    std::vector<BooruTag*> getTags();
    BooruTag* getTag(int i);
    int size();

private:
    Json::Value root;

    std::vector<BooruTag*> tags;
    std::string file_path;
    BooruSite *site;

};

#endif // BOORUTAGLIST_H
