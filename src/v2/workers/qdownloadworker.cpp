#include "qdownloadworker.h"

QDownloadWorker::QDownloadWorker(QString url, QString file, bool override, QObject *parent) : QObject(parent)
{
    this->url = url;
    this->file = file;
    this->override = override;
}

QDownloadWorker::QDownloadWorker(BooruPicture* picture, PictureType type, QObject *parent) : QObject(parent)
{
    this->url = QString(picture->getURL(type).c_str());
    this->file = QString(picture->getFile(type).c_str());
    this->override = false;
}

void QDownloadWorker::process()
{
    ConnectionManager* mgr = new ConnectionManager;
    bool res = mgr->downloadFile(url.toStdString(),file.toStdString(),override);
    if(res){emit downloaded(file);}
    emit finished();
}
