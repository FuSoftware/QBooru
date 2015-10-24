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
    int getMaxTagLength();
    int getMaxTagLengthIndex();

private:
    Json::Value root;

    std::vector<BooruTag*> tags;
    std::string file_path;
    BooruSite *site;

    int max_tag_length;
    int max_tag_length_index;

};

#endif // BOORUTAGLIST_H
