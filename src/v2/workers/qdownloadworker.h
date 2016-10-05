#ifndef QDOWNLOADWORKER_H
#define QDOWNLOADWORKER_H

#include <QObject>
#include "controller/connectionmanager.h"
#include "model/boorupicture.h"

class QDownloadWorker : public QObject
{
    Q_OBJECT
public:
    QDownloadWorker(QString url, QString file, bool override, QObject *parent = 0);
    QDownloadWorker(BooruPicture* picture, PictureType type, QObject *parent = 0);
signals:

public slots:
    void process();

private:
    QString url;
    QString file;
    bool override;
};

#endif // QDOWNLOADWORKER_H
