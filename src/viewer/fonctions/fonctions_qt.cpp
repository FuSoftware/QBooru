#include "fonctions_qt.h"

#include "../Workers/cookiejar.h"

void checkFolder(std::string path)
{
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

void runUpdaterFunction()
{
    outputInfo(L_INFO,"Running Updater");

    QString path = QString(UPDATER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000))

    while(Process->waitForFinished(3000))

    outputInfo(L_INFO,Process->program().toStdString() + std::string(" Running"));
    outputInfo(L_INFO,Process->errorString().toStdString());
    exit(0);
}

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget())
        {
            delete item->widget();
        }
        if (QSpacerItem *SpacerItem = item->spacerItem())
        {
            delete SpacerItem;
        }
        delete item;
    }
}

void clearLayoutSecond(QLayout *layout)
{
    int i = 0;

    for (i = 0; i < layout->count(); ++i)
    {
        QLayoutItem *layoutItem = layout->itemAt(i);

        if (layoutItem->spacerItem())
        {
            if(layoutItem->isEmpty())
            {
                layout->removeItem(layoutItem);
            }
            else
            {
                layout->removeItem(layoutItem);
                delete layoutItem;
            }
            --i;
        }
        if (layoutItem->layout())
        {
            layout->removeItem(layoutItem);
            delete layoutItem;
            --i;
        }
        if (layoutItem->widget())
        {
            if(i>-1)
            {
                if(layoutItem->isEmpty())
                {
                    layout->removeItem(layoutItem);
                }
                else
                {
                    layout->removeItem(layoutItem);
                    delete layoutItem;
                }
                --i;
            }
        }
    }
}

QString readChangelog()
{
    QString changelog;
    FILE* fp;
    char lettre;
    fp = fopen(CHANGELOG_FILE, "r");

    lettre = fgetc(fp);

    while(lettre != EOF)
    {
        changelog += lettre;
        lettre = fgetc(fp);
    }

    return changelog;
}
int downloadFile(const char *url, const char *file, CookieJar *cookies ,bool override, bool output, bool async)
{
    std::string output_s;
    QString referer = "Dummy";

    if(output)
    {
        output_s = std::string("Saving ") + std::string(url) + std::string(" to ") + std::string (file);
        outputInfo(L_INFO,output_s);
    }

    if(fexists(file) && !override)
    {
        //File exists and we don't want to everride
        return 0;
    }
    else
    {
        if(!async)
        {
            //Getting redirection

            QUrl file_url = findRedirection(QUrl(QString(url)));


            //Synchronous download
            QNetworkAccessManager *manager = new QNetworkAccessManager;
            QNetworkRequest request;

            request.setUrl(file_url.toString());
            request.setRawHeader("User-Agent", "QBooru");
            //request.setRawHeader("Referer", referer);

            //Cookies
            if(!cookies->isEmpty())
            {
                qDebug() << "Adding cookies" << cookies->getAllCookies();
                manager->setCookieJar(cookies);
            }

            QNetworkReply* m_pReply = manager->get(request);

            QEventLoop loop;
            QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
            loop.exec();

            //qDebug() << "Loop finished";

            if(m_pReply->error() != QNetworkReply::NoError)
            {
                output_s = std::string("Network error while downloading ") + std::string(url);
                outputInfo(L_ERROR,output_s);
                outputInfo(L_ERROR,m_pReply->errorString().toStdString());
                return m_pReply->error();
            }

            QString file_s = QString(file);

            QFile file(file_s);

            file.open(QIODevice::WriteOnly);
            file.write(m_pReply->readAll());
            file.close();
        }
        else
        {
            //Asynchronous download without feedback (Use the class directly for thread-dependant actions)
            FileDownloader downloader(0);
            downloader.download(url,file);
        }

        return 0;
    }
}

int downloadFile(const char* url, const char* file, bool override,  bool output , bool async)
{
    CookieJar *cookies = new CookieJar(0);
    downloadFile(url,file,cookies,override,async);
}

QList<QNetworkCookie> getLoginCookie(const char* url, QString user, QString pass)
{
    //Getting redirection
    QUrlQuery postData;
    postData.addQueryItem("user", user);
    postData.addQueryItem("pass", pass);
    postData.addQueryItem("submit", "Log+in");

    QUrl file_url = QUrl(QString(url));

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

QUrl findRedirection(QUrl url)
{
    QNAMRedirect redirect;
    redirect.processUrl(url.toString());

    QEventLoop loop;
    QObject::connect(&redirect, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    return redirect.getLastRedirect();
}
