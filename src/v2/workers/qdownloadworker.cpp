#include "qdownloadworker.h"

QDownloadWorker::QDownloadWorker(QString url, QString file, bool override, QObject *parent) : QObject(parent)
{
    this->url = url;
    this->file = file;
    this->override = override;
}

QDownloadWorker::QDownloadWorker(BooruPicture* picture, PictureType type, QObject *parent = 0) : QObject(parent)
{
    this->url = picture->getURL(type);
    this->file = picture->getFile(type);
    this->override = false;
}

void QDownloadWorker::process()
{
    ConnectionManager* mgr = new ConnectionManager;
    mgr->downloadFile(url.toStdString(),file.toStdString(),override);
    emit finished();
}
