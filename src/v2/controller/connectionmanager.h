#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <iostream>

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QString>
#include <QEventLoop>

#include <QList>
#include <QNetworkCookie>
#include <QVariant>

#include "utils/file.h"
#include "utils/output.h"
#include <QFile>
#include <QFileInfo>
#include "utils/qnamredirect.h"

enum ReqType{
    GET = 0,
    POST
};

class ConnectionManager
{
public:
    ConnectionManager();

    static QList<QNetworkCookie> getLoginCookie(std::string url, std::string user, std::string pass);
    static QList<QNetworkCookie> getLoginCookie(QString url, QString user, QString pass);

    static void downloadFile(QString url, QString path, bool overwrite = false);
    static void downloadFile(QUrl url, QString path, bool overwrite = false);

    static QNetworkReply* execPostRequest(QUrl url, QUrlQuery *data = 0);
    static QNetworkReply* execGetRequest(QUrl url, QUrlQuery *data = 0);
    static QNetworkReply* execRequest(QUrl url, ReqType type = GET, QUrlQuery *data = 0);

    static QUrl findRedirection(QUrl url);

private:
};

#endif // CONNECTIONMANAGER_H
