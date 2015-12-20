#include "qstartupwidget.h"

QStartupWidget::QStartupWidget(QWidget *parent) : QWidget(parent)
{
    connect(this,SIGNAL(processStatus(QString)),this,SLOT(updateStatus(QString)));
    loadUI();
}

void QStartupWidget::loadUI()
{
   QVBoxLayout *layout = new QVBoxLayout;
   progressBar = new QProgressBar(this);
   labelStatus = new QLabel("Starting",this);

   layout->addWidget(progressBar);
   layout->addWidget(labelStatus);

   setLayout(layout);
   this->show();
}

void QStartupWidget::process()
{
    checkVersions();
    loadConfigFile();
    emit finished();
}

int QStartupWidget::checkVersions()
{
    //Contacts the remote server to update the database regarding the number of users.
    //It sends the version of the software. The PHP page uses the IP and the current time

    emit processStatus("Getting versions");

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    QUrl url("http://florentuguet.net16.net/qbooru/software.php"); //Main URL
    //QUrl url("http://florentuguet.net16.net/tulpadiary/software-test\.php"); //Test URL
    QUrlQuery params;

    request.setUrl(url.toString());
    request.setRawHeader("User-Agent", "TulpaDiary");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

    params.addQueryItem("version", QString(APP_VERSION));
    params.addQueryItem("os", QString(OS_ID));
    params.addQueryItem("build", QString::number(BUILD));

    if(DEBUG){params.addQueryItem("type", "debug");}
    else{params.addQueryItem("type", "release");}

    QByteArray data;
    data.append(params.toString()); //POST params

    QNetworkReply* m_pReply = manager->post(request,data);

    emit processStatus("Getting last version");
    QTimer timer(0);
    timer.setInterval(5000); //5s timeout

    QObject::connect(&timer, SIGNAL(timeout()),m_pReply, SLOT(abort()));

    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();


    if(m_pReply->error() != QNetworkReply::NoError)
    {
        outputInfo(L_ERROR,std::string("Error when sending version : ") + m_pReply->errorString().toStdString());
        emit processStatus(QString("Error when sending version : ") + m_pReply->errorString());
        return m_pReply->error();
    }

    bool ok;

    qDebug() << "Version :"<<m_pReply->rawHeader("X-Version") <<m_pReply->rawHeader("X-Build");
    qDebug()<< m_pReply->rawHeaderList();

    QString lastBuild_s = QString(m_pReply->rawHeader("X-Build"));
    QString version = QString(m_pReply->rawHeader("X-Version"));

    int lastBuild = lastBuild_s.toInt(&ok);

    if(!ok)
    {
        //Logs the HTTP response
        emit processStatus("Error while retrieving the build, check the log file");
        outputInfo(L_ERROR,std::string("Retrieved build isn't a String : ") + lastBuild_s.toStdString());
        outputInfo(L_ERROR,std::string("Full string : ") + QString(m_pReply->readAll()).toStdString());
    }
    else
    {
        //Checks the update status
        if(lastBuild > BUILD)
        {
            //Update needed
            emit processStatus(QString("Update required : ") + QString(APP_VERSION) + QString((" -> ") + version));
            outputInfo(L_DEBUG,std::string("Update required : ") + std::string(APP_VERSION) + std::string(" -> ") + version.toStdString());

            QMessageBox msgBox(0);
            msgBox.setTextFormat(Qt::RichText);
            int rep = msgBox.question(0,"Update","Version " + version  + " is available, do you wish to update ?\nYou will need to restart the software after the update is complete.\n<a href=\"https://github.com/FlorentUguet/QBooru/blob/master/changelog.md\">Changelog</a>", QMessageBox ::Yes | QMessageBox::No);
            if (rep == QMessageBox::Yes)
            {
                QDownloadWidget *down = new QDownloadWidget(0,true);
                down->show();
                down->download(LAST_EXECUTABLE_FILE_URL,EXECUTABLE_DL,true);
            }
        }
        else
        {
            //Update not needed
            outputInfo(L_DEBUG,std::string("You have the latest version"));
        }
    }
    emit processStatus("Versions OK");
    return 0;
}

void QStartupWidget::loadConfigFile()
{
    cfg = new ConfigFile;
    cfg->process();
    emit processStatus("Configuration OK");
}

void QStartupWidget::updateStatus(QString status)
{
    labelStatus->setText(status);
}

ConfigFile *QStartupWidget::getCfg()
{
    return this->cfg;

}
