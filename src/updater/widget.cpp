#include "widget.h"

#include "fonctions.h"
#include "fonctions_json.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    textBrowser= new QTextBrowser(this);

    layoutButtons = new QHBoxLayout;
    pushButtonRunViewer = new QPushButton("Run viewer", this);
    pushButtonUpdate = new QPushButton("Update", this);
    pushButtonExit = new QPushButton("Exit", this);

    layoutVersions = new QHBoxLayout;
    labelLocalVersion = new QLabel(this);
    labelLastVersion = new QLabel(this);

    labelLocalVersion->setAlignment(Qt::AlignRight);
    labelLastVersion->setAlignment(Qt::AlignLeft);

    layoutVersions->addWidget(labelLocalVersion);
    layoutVersions->addWidget(labelLastVersion);

    layoutButtons->addWidget(pushButtonUpdate);
    layoutButtons->addWidget(pushButtonRunViewer);
    layoutButtons->addWidget(pushButtonExit);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(layoutVersions);
    mainLayout->addLayout(layoutButtons);

    setLayout(mainLayout);

    connect(pushButtonExit,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(pushButtonRunViewer,SIGNAL(clicked()),this,SLOT(runApplication()));
    connect(pushButtonUpdate,SIGNAL(clicked()),this,SLOT(updateSoftware()));

    textBrowser->setText(readChangelog());

    setMinimumSize(640,480);

    updateNeeded = false;

    Json::Value root = loadJSONFile(CONF_FILE);

    labelLocalVersion->setText(QString("Local : ") + QString(root["versions"]["viewer"]["local"].asCString()));
    labelLastVersion->setText(QString("Last : ") +QString(root["versions"]["viewer"]["last"].asCString()));

    getVersion(root["versions"]["viewer"]["local"].asCString(),viewerVersions[0]);//LOCAL
    getVersion(root["versions"]["viewer"]["last"].asCString(),viewerVersions[1]);//LAST

    for(int j=0;j<VERSION_CONTROL_DIGITS;j++)
    {
        if(viewerVersions[1][j] > viewerVersions[0][j])
        {
            updateNeeded = true;
        }
    }

    pushButtonUpdate->setEnabled(updateNeeded);

    if(updateNeeded)
    {
        pushButtonUpdate->setText("Update");
    }
    else
    {
        pushButtonUpdate->setText("Update not needed");
    }
}

Widget::~Widget()
{

}

void Widget::runApplication()
{
    outputInfo("INFO","Running Viewer",LEVEL_UPDATER);

    QString path = QString(VIEWER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000));

    outputInfo("INFO",Process->program().toStdString() + std::string(" Running"),LEVEL_UPDATER);
    outputInfo("INFO",Process->errorString().toStdString(),LEVEL_UPDATER);
    exit(0);
}

void Widget::runAndStopApplication()
{
    outputInfo("INFO","Running Viewer",LEVEL_UPDATER);

    QString path = QString(VIEWER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000));

    while(Process->waitForFinished(3000));

    outputInfo("INFO",Process->program().toStdString() + std::string(" Running"),LEVEL_UPDATER);
    outputInfo("INFO",Process->errorString().toStdString(),LEVEL_UPDATER);
}

void Widget::updateSoftware()
{
    cachingFile(LAST_EXECUTABLE_FILE_URL,VIEWER_MAIN_EXECUTABLE,true,false);
}
