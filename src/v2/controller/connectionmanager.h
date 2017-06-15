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

enum ReqType{
    GET = 0,
    POST
};

using namespace std;

class ConnectionManager
{
public:
    ConnectionManager();

    string get(string url, string params);

    QList<QNetworkCookie> getLoginCookie(string url, string user, string pass);
    QList<QNetworkCookie> getLoginCookie(QString url, QString user, QString pass);

    void downloadFile(QString url, QString path, bool overwrite = false);
    void downloadFile(QUrl url, QString path, bool overwrite = false);

    QNetworkReply* execPostRequest(QUrl url, QUrlQuery *data = 0);

    QNetworkReply* execGetRequest(QUrl url, QUrlQuery *data = 0);

    QNetworkReply* execRequest(QUrl url, ReqType type = GET, QUrlQuery *data = 0);


private:
};

#endif // CONNECTIONMANAGER_H
