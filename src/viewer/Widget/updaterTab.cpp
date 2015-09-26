#include "updaterTab.h"

#include "./fonctions/fonctions.h"
#include "./fonctions/fonctions_json.h"

UpdaterTab::UpdaterTab(Widget *parent)
    : QWidget(parent)
{
    conf_file = parent->getConfigFile();

    mainLayout = new QVBoxLayout;
    textBrowser= new QTextBrowser(this);

    layoutButtons = new QHBoxLayout;
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
    layoutButtons->addWidget(pushButtonExit);

    mainLayout->addWidget(textBrowser);
    mainLayout->addLayout(layoutVersions);
    mainLayout->addLayout(layoutButtons);

    setLayout(mainLayout);

    connect(pushButtonExit,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(pushButtonUpdate,SIGNAL(clicked()),this,SLOT(updateSoftware()));

    connect(this,SIGNAL(rebootApp()),parent,SLOT(slotReboot()));

    //setMinimumSize(640,480);

    refreshInterface();
}

UpdaterTab::~UpdaterTab()
{

}

void UpdaterTab::refreshInterface()
{
    textBrowser->setText(readChangelog());

    updateNeeded = false;
    conf_file->checkSoftwareVersions();
    updateNeeded = conf_file->getUpdateState();

    labelLocalVersion->setText(QString("Local : ") + QString(conf_file->getVersionString(VER_LOCAL).c_str()));
    labelLastVersion->setText(QString("Last : ") +QString(conf_file->getVersionString(VER_LAST).c_str()));

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

void UpdaterTab::updateSoftware()
{
    cachingFile(LAST_EXECUTABLE_FILE_URL,VIEWER_MAIN_EXECUTABLE,true,false);
    refreshInterface();  
    emit rebootApp();
}
