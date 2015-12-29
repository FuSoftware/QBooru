#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>
#include <QSettings>
#include <QObject>

#include "../classBooruSite.h"

#define FILE_NAME "cookies.ini"

class CookieJar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    CookieJar(QObject *parent = 0);
    CookieJar(QString booru_name, QObject *parent = 0);
    void load();
    void save();
    QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const;
    bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);
    bool isEmpty();
    QList<QNetworkCookie> getAllCookies();
    QString getUrl();
    QString getCookieData(int id);

signals:
    void cookiesChanged();

private:
    bool m_loaded;
    QString path;
    QString cookie_location;
};

#endif // COOKIEJAR_H
