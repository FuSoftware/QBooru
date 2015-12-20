#include "qdownloadwidget.h"

QDownloadWidget::QDownloadWidget(QWidget *parent, bool reboot) : QWidget(parent)
{
    this->reboot = reboot;
    labelFile = new QLabel("File",this);
    labelUrl = new QLabel("URL",this);
    progressBar = new QProgressBar(this);
    labelProgress = new QLabel("Progress",this);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(labelFile);
    layout->addWidget(labelUrl);
    layout->addWidget(progressBar);
    layout->addWidget(labelProgress);

    setLayout(layout);
}

void QDownloadWidget::download(const char* url, const char* file, bool override)
{
    this->url = QString(url);
    this->file = QString(file);

    labelFile->setText("File: " + this->file);
    labelUrl->setText("URL: " + this->url);
    labelProgress->setText("Initializing (May take some time)");

    savefile = new QFile;
    savefile->setFileName(this->file);

    if(fexists(file) && !override)
    {
        progressBar->setValue(100);
        labelProgress->setText("Already existing");
    }
    else
    {
        //Getting redirection

        QUrl file_url = findRedirection(QUrl(QString(url)));

        //Synchronous download
        nam = new QNetworkAccessManager;
        QNetworkRequest request;


        request.setUrl(file_url.toString());
        request.setRawHeader("User-Agent", "TulpaDiary");
        request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

        reply = nam->get(request);

        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadProgress(qint64,qint64)));
        connect(reply,SIGNAL(finished()),this,SLOT(finished()));
    }
}

void QDownloadWidget::onDownloadProgress(qint64 bytesRead,qint64 bytesTotal)
{
    labelProgress->setText(QString("Downloading ") + QString::number(bytesRead) + QString("/") + QString::number(bytesTotal));
    progressBar->setMaximum(bytesTotal);
    progressBar->setValue(bytesRead);
}

void QDownloadWidget::finished()
{
    if(reply->error() != QNetworkReply::NoError)
    {
        labelProgress->setText("Error : " + reply->error());
        qDebug() << "Error while downloading " << url << " : " << reply->error() ;
    }
    else
    {
        savefile->open(QIODevice::WriteOnly);
        QDataStream out(savefile);
        out << reply->readAll();
        reply->deleteLater();
        savefile->close();

        labelProgress->setText("File saved");

        qDebug() << "Downloaded" << url << "to" << file ;
    }

    if(reboot)
    {
        qApp->exit(EXIT_CODE_UPDATE);
    }

    this->close();
}
