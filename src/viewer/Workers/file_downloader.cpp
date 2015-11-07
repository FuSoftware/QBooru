#include "file_downloader.h"

FileDownloader::FileDownloader(QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
}

FileDownloader::FileDownloader(const char *url, const char *filename, QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
    download(url, filename);
}

void FileDownloader::download(const char *url, const char *filename)
{
    this->m_Filename = QString(filename);
    this->m_Url = QString(url);

    QUrl file_url(m_Url);

    QNetworkRequest request(file_url);
    m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
    saveData();
}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}

void FileDownloader::saveData()
{
    QFile file(m_Filename);

    file.open(QIODevice::WriteOnly);
    file.write(m_DownloadedData);
    file.close();
}
