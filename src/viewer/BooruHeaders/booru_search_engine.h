#ifndef BOORUSEARCHENGINE_H
#define BOORUSEARCHENGINE_H

#include <iostream>
#include <QTimer>
#include "../fonctions_all.h"
#include "../Workers/cookiejar.h"
#include "../Workers/searchloggingworker.h"

class BooruSearchEngine : public QObject
{
    Q_OBJECT
public:    
    BooruSearchEngine(QObject *parent = 0);
    BooruSearchEngine(BooruSite* booru, QObject *parent = 0);
    BooruSearchEngine(BooruSite* booru, std::string tags, int page, QObject *parent = 0);
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
    void setDump(bool isDump);
    int getResultSize();
    int logSearch();

    int getPage();
    CookieJar *getCookie();
    std::string getTags();
    bool hasCookie();

private:
    bool has_cookie;
    BooruSite* booru;
    CookieJar* cookie;

    int image_count;

    std::string tags_org;
    std::string tags;
    std::string search_extension;
    std::string search_url;

    std::string rating_extension;

    std::string derpibooru_api_key;
    int page;
    int rating_id;
    bool isDump;

    SearchLoggingWorker *worker;
    QThread *thread;
};

#endif // BOORUSEARCHENGINE_H
