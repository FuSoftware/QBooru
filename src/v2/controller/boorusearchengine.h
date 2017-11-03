#ifndef BOORUSEARCHENGINE_H
#define BOORUSEARCHENGINE_H

#include <iostream>

#include "connectionmanager.h"

#include "../model/boorupicture.h"
#include "../model/boorusite.h"
#include "../utils/json.h"
#include "../utils/output.h"

enum Ratings{
    RATING_ALL = 0,
    RATING_SAFE,
    RATING_QUESTIONNABLE,
    RATING_EXPLICIT,
    RATING_LIST_END
};

class BooruSearchEngine
{
public:
    BooruSearchEngine(BooruSite* parent);

    QString generateRequest(QString tags, int page, int limit);

    vector<BooruPicture*> search(QString tags);
    vector<BooruPicture*> search(int page);
    vector<BooruPicture*> search(QString tags, int page);
    vector<BooruPicture*> search(QString tags, int page, int limit);
    vector<BooruPicture*> search();

    void set(QString tags);
    void set(int page);
    void set(QString tags, int page);
    void set(QString tags, int page, int limit);

    vector<BooruPicture*> parse(QString data);

private:
    QString tags;
    int page;
    int limit;
    BooruSite* parent;
};

#endif // BOORUSEARCHENGINE_H
