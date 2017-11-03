#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{

}

QList<QNetworkCookie> ConnectionManager::getLoginCookie(std::string url, std::string user, std::string pass){
    QString qurl = QString::fromStdString(url);
    QString quser = QString::fromStdString(user);
    QString qpass = QString::fromStdString(pass);

    return getLoginCookie(qurl,quser,qpass);
}

QList<QNetworkCookie> ConnectionManager::getLoginCookie(QString url, QString user, QString pass)
{
    //Getting redirection
    QUrlQuery *postData = new QUrlQuery;
    postData->addQueryItem("user", user);
    postData->addQueryItem("pass", pass);
    postData->addQueryItem("submit", "Log+in");

    QUrl qurl = QUrl(url);

    QNetworkReply* reply = execPostRequest(qurl,postData);

    //qDebug() << "Loop finished";
    QVariant variantCookies = reply->header(QNetworkRequest::SetCookieHeader);
    QList<QNetworkCookie> cookies = qvariant_cast<QList<QNetworkCookie> >(variantCookies);
    //qDebug() << "Cookies reply: " << cookies.toSet();

    if(reply->error() != QNetworkReply::NoError)
    {
        std::string output_s = std::string("Network error while downloading ") + url.toStdString();
        outputInfo(L_ERROR,output_s);
        outputInfo(L_ERROR,reply->errorString().toStdString());
    }

    delete reply;
    delete postData;

    return cookies;
}

void ConnectionManager::downloadFile(QString url, QString path, bool overwrite)
{
    downloadFile(QUrl(url),path, overwrite);
}

void ConnectionManager::downloadFile(QUrl url, QString path, bool overwrite)
{
    if(!fexists(path.toStdString()) || overwrite)
    {
        QNetworkReply* reply = execGetRequest(url);

        createFolder(path);
        QFile f(path);
        f.open(QIODevice::WriteOnly);
        f.write(reply->readAll());
        f.close();
    }
}

QNetworkReply* ConnectionManager::execPostRequest(QUrl url, QUrlQuery *data)
{
    return execRequest(url,POST,data);
}

QNetworkReply* ConnectionManager::execGetRequest(QUrl url, QUrlQuery *data)
{
    QUrl qurl;

    if(data)
        qurl = QUrl(url.url() + data->toString());
    else
        qurl = url;

    return execRequest(qurl,GET);
}

QNetworkReply* ConnectionManager::execRequest(QUrl url, ReqType type, QUrlQuery *data)
{
    //Synchronous download
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    url = findRedirection(url);

    request.setUrl(url.toString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "QBooru/2.0 FuSoftware https://github.com/FuSoftware/QBooru");
    //request.setRawHeader("Referer", referer);

    QNetworkReply* m_pReply;

    switch(type){
    case GET:
        //qDebug() << "Querying" << url.toString() << "with GET";
        m_pReply = manager->get(request);
        break;
    case POST:
        if(data != NULL){
            //qDebug() << "Querying" << url.toString() << "with POST" << data->toString(QUrl::FullyEncoded).toUtf8();
            m_pReply = manager->post(request, data->toString(QUrl::FullyEncoded).toUtf8());
        }else{
            qDebug() << "Could not query" << url.toString() << "with POST : " << "Post data empty";
            return 0;
        }
        break;
    default:
        break;
    }

    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    return m_pReply;
}

QUrl ConnectionManager::findRedirection(QUrl url)
{
    QNAMRedirect redirect;
    redirect.processUrl(url.toString());

    QEventLoop loop;
    QObject::connect(&redirect, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    return redirect.getLastRedirect();
}
