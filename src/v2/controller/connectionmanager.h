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

#include <QFile>
#include <QFileInfo>

#include "utils/output.h"
#include "utils/file.h"
#include "utils/qnamredirect.h"

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

    bool downloadFile(std::string url, std::string path, bool override);
    bool downloadFile(QString url, QString path, bool override);

    QList<QNetworkCookie> getLoginCookie(string url, string user, string pass);
    QList<QNetworkCookie> getLoginCookie(QString url, QString user, QString pass);

    QNetworkReply* execPostRequest(QUrl url, QUrlQuery *data = 0);

    QNetworkReply* execGetRequest(QUrl url, QUrlQuery *data = 0);

    QNetworkReply* execRequest(QUrl url, ReqType type = GET, QUrlQuery *data = 0);

    QUrl findRedirection(QUrl url);


private:
};

#endif // CONNECTIONMANAGER_H
