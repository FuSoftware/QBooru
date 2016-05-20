#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <iostream>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "../utils/output.h"

using namespace std;

class ConnectionManager
{
public:
    ConnectionManager();

    string get(string url, string params);

    QList<QNetworkCookie> getLoginCookie(string url, string user, string pass);
    QList<QNetworkCookie> getLoginCookie(QString url, QString user, QString pass);


private:
};

#endif // CONNECTIONMANAGER_H
