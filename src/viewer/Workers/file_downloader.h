#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>

#include "qnamredirect.h"

#include <QDebug>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    FileDownloader(QObject *parent = 0);
    FileDownloader(const char* url, const char* filename, QObject *parent = 0);
    void download(const char *url, const char *filename);
    QByteArray downloadedData() const;

    QUrl findRedirection(QUrl url);

signals:
    void downloaded();
    void saved();

public slots:
    void fileDownloaded(QNetworkReply* pReply);
    void saveData();

private:
    QEventLoop *loop;
    QString m_Url;
    QString m_Filename;
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
};

#endif // FILEDOWNLOADER_H
