#include "boorupixmapdownloader.h"

#include "model/boorupicture.h"
#include "controller/connectionmanager.h"

BooruPixmapDownloader::BooruPixmapDownloader(BooruPicture* pic, bool overwrite, QObject *parent) : QObject(parent)
{
    this->url = QString::fromStdString(pic->getThumbnailUrl());
    this->path = QString::fromStdString(pic->getThumbnailPath());
    this->id = pic->getID();
    this->overwrite = overwrite;
}

BooruPixmapDownloader::BooruPixmapDownloader(QString url, QString path, bool overwrite, QObject *parent) : QObject(parent)
{
    this->url = url;
    this->path = path;
    id = 0;
    this->overwrite = overwrite;
}

BooruPixmapDownloader::BooruPixmapDownloader(BooruPicture* pic, int type, bool overwrite, QObject *parent) : QObject(parent)
{
    this->url = QString::fromStdString(pic->getURL(type));
    this->path = QString::fromStdString(pic->getFile(type));
    id = pic->getID();
    this->overwrite = overwrite;
}

void BooruPixmapDownloader::process()
{
    ConnectionManager* c = new ConnectionManager();
    c->downloadFile(this->url,this->path,this->overwrite);
    QPixmap p(this->path);
    delete c;

    emit pixmapLoaded(p);
    emit finished();
}
