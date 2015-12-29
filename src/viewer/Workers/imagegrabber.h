#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>

#include "../fonctions_all.h"
#include "../BooruHeaders/booru_search_engine.h"
#include "../BooruHeaders/generic_booru_image.h"

class ImageGrabber : public QObject
{
    Q_OBJECT
public:
    ImageGrabber(std::vector<BooruSite*> boorus, std::string tags, int rating = 0, int limit = 0, QObject *parent = 0);
    ImageGrabber(std::vector<BooruSite*> boorus, std::vector<CookieJar*> cookies, string tags, int rating = 0, int limit = 0, QObject *parent = 0);
    int logSearch(int index);
    void setCookie(int index, CookieJar* cookie);

signals:
    void status(QString);
    void progress(int,int);

    void search_completed();
    void finished();

public slots:
    void grabSearchFiles();
    void search();
    void dump();

private:
    std::vector<BooruImage*> images;
    std::vector<BooruSearchEngine*> searchEngines;
    std::vector<BooruSite*> boorus;

    std::vector<int> dumped_pics;

    int rating;
    int limit;
    std::string tags;
};

#endif // IMAGEGRABBER_H
