#include "cookiejar.h"

CookieJar::CookieJar(QObject *parent) : QNetworkCookieJar(parent), m_loaded(false)
{
    path = QString(CONF_PATH) + QString(FILE_NAME);
    cookie_location = QString("cookies");
}

CookieJar::CookieJar(QString booru_name, QObject *parent) : QNetworkCookieJar(parent), m_loaded(false)
{
    path = QString(CACHE_PATH) + booru_name + QString("/") + QString(FILE_NAME);
    cookie_location = QString("cookies");
}

void CookieJar::load()
{
    if (m_loaded)
        return;

    QSettings *settings = new QSettings(path, QSettings::IniFormat);
    settings->beginGroup(cookie_location);
    QList<QNetworkCookie> savedCookies = QNetworkCookie::parseCookies(settings->value("cookie_location").toByteArray());

    for (int j = 0; j < savedCookies.count(); j++)
        insertCookie(savedCookies.at(j));

    m_loaded = true;
    emit cookiesChanged();
}

void CookieJar::save()
{
    if (!m_loaded)
        return;

    QList<QNetworkCookie> cookies = allCookies();

    QSettings *settings = new QSettings(path, QSettings::IniFormat);
    settings->beginGroup(cookie_location);
    settings->setValue(cookies[0].name(), cookies[0].toRawForm());
    settings->setValue(cookies[1].name(), cookies[1].toRawForm());
}

QList<QNetworkCookie> CookieJar::cookiesForUrl(const QUrl &url) const
{
    // This function is called by the default QNetworkAccessManager::createRequest(),
    // which adds the cookies returned by this function to the request being sent.

    CookieJar *that = const_cast<CookieJar*>(this);
    if (!m_loaded)
        that->load();

    return QNetworkCookieJar::cookiesForUrl(url);
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
    if (!m_loaded)
        load();

    QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
    save();     //Save cookie permanently in setting file.
    emit cookiesChanged();
    return true;
}

bool CookieJar::isEmpty()
{
    return this->allCookies().empty();
}

QList<QNetworkCookie> CookieJar::getAllCookies()
{
    return this->allCookies();
}

QString CookieJar::getUrl()
{
    return QString("http://") + this->allCookies().at(0).domain();
}

