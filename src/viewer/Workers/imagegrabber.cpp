#include "imagegrabber.h"

ImageGrabber::ImageGrabber(std::vector<BooruSite *> boorus, string tags, int rating, int limit, QObject *parent) : QObject(parent)
{
    //Clears previous searches
    searchEngines.clear();
    dumped_pics.clear();
    images.clear();

    qDebug() << "Starting grabber";
    this->boorus = boorus;
    this->tags = tags;
    this->rating = rating;
    this->limit = limit;

    if(limit ==0)
    {
        limit = 500;// Arbitrary number
    }

    //Sets up search engines
    emit status("Setting up the grabber");

    for(int i=0;i<boorus.size();i++)
    {
        searchEngines.push_back(new BooruSearchEngine(boorus.at(i)));
        searchEngines.at(i)->setRating(rating);
        searchEngines.at(i)->setTags(tags);
        searchEngines.at(i)->setPage(1);
        searchEngines.at(i)->setImageCount(limit);
        searchEngines.at(i)->setDump(true);
        searchEngines.at(i)->generateUrlExtension();

        dumped_pics.push_back(0);
    }
    qDebug() << "Grabber loaded";
}

ImageGrabber::ImageGrabber(std::vector<BooruSite *> boorus, std::vector<CookieJar *> cookies, string tags, int rating, int limit, QObject *parent) : QObject(parent)
{
    //Clears previous searches
    searchEngines.clear();
    dumped_pics.clear();
    images.clear();

    qDebug() << "Starting grabber";
    this->boorus = boorus;
    this->tags = tags;
    this->rating = rating;
    this->limit = limit;

    if(limit ==0)
    {
        limit = 500;// Arbitrary number
    }

    //Sets up search engines
    emit status("Setting up the grabber");

    for(int i=0;i<boorus.size();i++)
    {
        searchEngines.push_back(new BooruSearchEngine(boorus.at(i)));
        searchEngines.at(i)->setRating(rating);
        searchEngines.at(i)->setTags(tags);
        searchEngines.at(i)->setPage(1);
        searchEngines.at(i)->setImageCount(limit);
        searchEngines.at(i)->setDump(true);
        searchEngines.at(i)->generateUrlExtension();

        if(!cookies.at(i)->isEmpty())
        {
            searchEngines.at(i)->setCookie(cookies.at(i));
        }

        dumped_pics.push_back(0);
    }
    qDebug() << "Grabber loaded";
}

void ImageGrabber::grabSearchFiles()
{
    for(int i=0; i<searchEngines.size();i++)
    {
        qDebug() << "Searching" << boorus.at(i)->getName().c_str();

        searchEngines.at(i)->search();
        qDebug() << "Got" << searchEngines.at(i)->getResultSize() << "pictures";


        while(searchEngines.at(i)->getResultSize() > 0)
        {
            //Tries next page
            searchEngines.at(i)->setPage(searchEngines.at(i)->getPage()+1);
            searchEngines.at(i)->generateUrlExtension();
            searchEngines.at(i)->search();
            qDebug() << "Got" << searchEngines.at(i)->getResultSize() << "pictures";
        }
    }
}

void ImageGrabber::search()
{
    int index=0;
    int k=0;

    std::string folder = std::string(DOWNLOAD_PATH) + std::string("grabber/") + tags + std::string("/");

    for(int i=0; i<searchEngines.size();i++)
    {
        do
        {
            //Downloads the requested page
            emit status(QString("Searching ") + QString(boorus.at(i)->getName().c_str()));
            searchEngines.at(i)->search();

            k = searchEngines.at(i)->getResultSize();
            for(int x=0;x<k;x++)
            {
                //Loads pictures for the current page
                images.push_back(new BooruImage(boorus.at(i)));
                images.at(index)->loadData(x);
                images.at(index)->loadPaths(folder,boorus.at(i)->getName());
                index++;
            }
            //Prepares next page
            searchEngines.at(i)->setPage(searchEngines.at(i)->getPage()+1);
            searchEngines.at(i)->generateUrlExtension();
            dumped_pics[i] += k;

            if(dumped_pics[i] >= limit){break;}
        }while(k > 0);

        logSearch(i);
    }

    qDebug() << "Dumping" << images.size() << "pictures";

    emit search_completed();
}

void ImageGrabber::dump()
{
    for(int i=0;i<images.size();i++)
    {
        emit status(QString("Downloading picture ") + QString::number(i+1) + QString("/") + QString::number(images.size()));
        images.at(i)->download_full();
        emit progress(i+1,images.size());
    }
    emit status(QString("Completed"));
    emit finished();
}

int ImageGrabber::logSearch(int index)
{
    //Sends the tags to be logged on a remote DB
    //Only function to need Qt specific classes

    BooruSearchEngine *engine = searchEngines.at(index);

    QString user_agent = "QBooru";

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    QUrl url(URL_RECORDS); //Main URL
    QUrlQuery params;

    if(engine->hasCookie())
    {
        user_agent += " - UserID : ";
        user_agent += engine->getCookie()->getCookieData(1); //Should return the UserID, for testing purposes only
    }

    request.setUrl(url.toString());
    request.setRawHeader("User-Agent", user_agent.toLatin1());
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

    params.addQueryItem("dump_req", "1");
    params.addQueryItem("size", QString::number(dumped_pics.at(index)));

    if(engine->hasCookie())
    {
        params.addQueryItem("user_id", engine->getCookie()->getCookieData(1));
    }

    params.addQueryItem("tags", QString(this->tags.c_str()));
    params.addQueryItem("rating", QString::number(this->rating));
    params.addQueryItem("booru_name", QString(boorus.at(index)->getName().c_str()));
    params.addQueryItem("booru_url", QString(boorus.at(index)->getBaseUrl().c_str()));

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
        return m_pReply->error();
    }

    return 0;
}

void ImageGrabber::setCookie(int index, CookieJar* cookie)
{
    searchEngines.at(index)->setCookie(cookie);
}
