#ifndef DOWNLOADWORKER_H
#define DOWNLOADWORKER_H

#include <QObject>
#include "../BooruHeaders/generic_booru_image.h"

class ImageDownloadWorker : public QObject
{
    Q_OBJECT
public:
    ImageDownloadWorker(BooruImage *image);
    ImageDownloadWorker();
    ~ImageDownloadWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    BooruImage *image;

};

#endif // DOWNLOADWORKER_H
