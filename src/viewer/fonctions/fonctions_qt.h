#ifndef FONCTIONS_QT_H
#define FONCTIONS_QT_H

#include <iostream>
#include "../constantes.h"
#include "../Workers/file_downloader.h"
#include "../Workers/qnamredirect.h"
#include "fonctions.h"

#include <QString>
#include <QDir>

#include <QLayout>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>
#include <QThread>
#include <QUrlQuery>
#include <QVariant>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>

class CookieJar;

void checkFileFolder(std::string path);
void checkFolder(std::string path);
void runUpdaterFunction();

void clearLayout(QLayout *layout);
void clearLayoutSecond(QLayout *layout);
QString readChangelog();

int downloadFile(const char *url, const char *file, CookieJar *cookies ,bool override = true, bool output = false, bool async = false);
int downloadFile(const char* url, const char* file, bool override = true, bool output = false, bool async = false );
QList<QNetworkCookie> getLoginCookie(const char* url, QString user, QString pass);

QUrl findRedirection(QUrl url);

#endif
