#ifndef BOORUTAG_H
#define BOORUTAG_H

#include <iostream>
#include "./classBooruSite.h"

enum TagTypes{
    TAG_COMMON = 0,
    TAG_ARTIST = 1,
    TAG_CHARA = 4
};

class BooruSite;

class BooruTag
{
public:
    BooruTag(Json::Value root, BooruSite *parent);

    void loadFromJson(Json::Value root);
    int getId();
    std::string getName();
    int getCount();
    int getCategory();
    std::string getCategoryType();


private:
    BooruSite *site;

    int id;
    std::string name;
    int count;
    int type;
    std::string type_name;
};

#endif // BOORUTAG_H

/* Moebooru
{
  "id": 88647,
  "name": ">_<",
  "count": 0,
  "type": 0,
  "ambiguous": false
}
*/

