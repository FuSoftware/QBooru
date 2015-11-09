#include "file_downloader.h"

FileDownloader::FileDownloader(QObject *parent) : QObject(parent)
{
    loop = new QEventLoop(this);
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
    connect(this, SIGNAL(saved()), loop, SLOT(quit()));
}

FileDownloader::FileDownloader(const char *url, const char *filename, QObject *parent) : QObject(parent)
{
    loop = new QEventLoop(this);
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),this, SLOT (fileDownloaded(QNetworkReply*)));
    connect(this, SIGNAL(saved()), loop, SLOT(quit()));
    download(url, filename);
}

void FileDownloader::download(const char *url, const char *filename)
{
    QString referer = "Dummy referer";

    this->m_Filename = QString(filename);
    this->m_Url = QString(url);

    QUrl file_url(m_Url);

    this->m_Url = findRedirection(file_url).toString();
    QUrl new_url(m_Url);

    QNetworkRequest request;

    request.setUrl(new_url.toString());
    request.setRawHeader("User-Agent", "QBooru");
    //request.setRawHeader("Referer", referer);

    m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();
    //emit a signal
    delete pReply;

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
    file.write(this->downloadedData());
    file.close();
    emit saved();
}

/*Redirection*/
QUrl FileDownloader::findRedirection(QUrl url)
{
    QNAMRedirect redirect;
    redirect.processUrl(url.toString());

    QEventLoop loop;
    QObject::connect(&redirect, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    qDebug() << "URl :" << redirect.getLastRedirect();
    return redirect.getLastRedirect();
}
