#ifndef QDOWNLOADWIDGET_H
#define QDOWNLOADWIDGET_H

#include <QtWidgets>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>
#include <QUrlQuery>

#include "../constantes.h"
#include "../fonctions_all.h"

class QDownloadWidget : public QWidget
{
    Q_OBJECT
public:
    QDownloadWidget(QWidget *parent = 0, bool reboot = false);

signals:

public slots:
    void download(const char* url, const char* file, bool override = true);
    void onDownloadProgress(qint64 bytesRead,qint64 bytesTotal);
    void finished();

private:
    QNetworkAccessManager *nam;

    QLabel *labelFile;
    QLabel *labelUrl;
    QProgressBar *progressBar;
    QLabel *labelProgress;

    QString url;
    QString file;

    QFile *savefile;
    QNetworkReply* reply;

    bool reboot;
};

#endif // QDOWNLOADWIDGET_H
