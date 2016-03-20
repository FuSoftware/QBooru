#include "searchloggingworker.h"

// --- CONSTRUCTOR ---
SearchLoggingWorker::SearchLoggingWorker(string tags, int rating, int page, BooruSite* booru)
{
    this->tags = tags;
    this->rating = rating;
    this->booru = booru;
    this->page = page;
}

SearchLoggingWorker::SearchLoggingWorker()
{

}

// --- DECONSTRUCTOR ---
SearchLoggingWorker::~SearchLoggingWorker()
{
    // free resources
}

// --- PROCESS ---
void SearchLoggingWorker::process()
{
    //Sends the tags to be logged on a remote DB
    //Only function to need Qt specific classes

    QString user_agent = "QBooru";

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    QUrl url(URL_RECORDS); //Main URL
    QUrlQuery params;

    request.setUrl(url.toString());
    request.setRawHeader("User-Agent", user_agent.toLatin1());
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

    params.addQueryItem("tag_req", "1");
    params.addQueryItem("page", QString::number(page));

    params.addQueryItem("tags", QString(tags.c_str()));
    params.addQueryItem("rating", QString::number(rating));
    params.addQueryItem("booru_name", QString(booru->getName().c_str()));
    params.addQueryItem("booru_url", QString(booru->getBaseUrl().c_str()));

    QByteArray data;
    data.append(params.toString()); //POST params

    QNetworkReply* m_pReply = manager->post(request,data);
    QTimer timer(0);
    timer.setInterval(1000); //1s timeout

    QObject::connect(&timer, SIGNAL(timeout()),m_pReply, SLOT(abort()));
    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    //qDebug() <<  m_pReply->readAll();

    if(m_pReply->error() != QNetworkReply::NoError)
    {
        outputInfo(L_ERROR,std::string("Error when sending tags : ") + m_pReply->errorString().toStdString());
        outputInfo(L_ERROR,std::string("Full reply : ") +  m_pReply->readAll().toStdString());
    }

    emit finished();
}

