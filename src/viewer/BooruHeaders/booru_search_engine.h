#ifndef BOORUSEARCHENGINE_H
#define BOORUSEARCHENGINE_H

#include <iostream>
#include "../fonctions_all.h"
#include "../Workers/cookiejar.h"

class BooruSearchEngine
{
public:
    BooruSearchEngine();
    BooruSearchEngine(BooruSite* booru);
    BooruSearchEngine(BooruSite* booru, std::string tags, int page);
    ~BooruSearchEngine();

    void generateUrlExtension();

    void search();
    void search(std::string tags);
    void search(int page);
    void search(std::string tags, int page);
    void search(std::string tags, int page, CookieJar* cookie);

    void setRating(int rating_id);

    void setCookie(CookieJar *cookie);
    void setBooru(BooruSite* booru);
    void setTags(std::string tags);
    void setImageCount(int count);
    void setPage(int page);
    void setApiKey(std::string key);

private:
    bool has_cookie;
    BooruSite* booru;
    CookieJar* cookie;

    int image_count;

    std::string tags;
    std::string search_extension;
    std::string search_url;

    std::string rating_extension;

    std::string derpibooru_api_key;
    int page;
    int rating_id;
};

#endif // BOORUSEARCHENGINE_H
