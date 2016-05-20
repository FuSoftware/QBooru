#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{

}

QList<QNetworkCookie> getLoginCookie(string url, string user, string pass){
    return getLoginCookie(QString(url.c_str()),QString(user.c_str()),QString(pass.c_str()));
}

QList<QNetworkCookie> getLoginCookie(QString url, QString user, QString pass)
{
    //Getting redirection
    QUrlQuery postData;
    postData.addQueryItem("user", user);
    postData.addQueryItem("pass", pass);
    postData.addQueryItem("submit", "Log+in");

    QUrl file_url = QUrl(url);

    //Synchronous download
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    request.setUrl(file_url.toString());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //request.setRawHeader("Referer", referer);

    qDebug() << "Querying" << file_url.toString() << "with POST" << postData.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkReply* m_pReply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    //qDebug() << "Loop finished";
    QVariant variantCookies = m_pReply->header(QNetworkRequest::SetCookieHeader);
    QList<QNetworkCookie> cookies = qvariant_cast<QList<QNetworkCookie> >(variantCookies);
    qDebug() << "Cookies reply: " << cookies;

    if(m_pReply->error() != QNetworkReply::NoError)
    {
        std::string output_s = std::string("Network error while downloading ") + std::string(url);
        outputInfo(L_ERROR,output_s);
        outputInfo(L_ERROR,m_pReply->errorString().toStdString());
        return cookies;
    }

    return cookies;
}
