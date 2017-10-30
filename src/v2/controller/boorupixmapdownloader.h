#ifndef BOORUPIXMAPDOWNLOADER_H
#define BOORUPIXMAPDOWNLOADER_H

#include <QObject>
#include <QPixmap>

class Connectionmanager;
class BooruPicture;

class BooruPixmapDownloader : public QObject
{
    Q_OBJECT
public:
    BooruPixmapDownloader(BooruPicture* pic, bool overwrite = false, QObject *parent = nullptr);
    BooruPixmapDownloader(QString url, QString path, bool overwrite = false, QObject *parent = nullptr);
    BooruPixmapDownloader(BooruPicture* pic, int type, bool overwrite = false, QObject *parent = nullptr);

signals:
    void pixmapLoaded(QPixmap pixmap);
    void finished();

public slots:
    void process();

private:
    QString url;
    QString path;
    int id;
    bool overwrite;
};

#endif // BOORUPIXMAPDOWNLOADER_H
