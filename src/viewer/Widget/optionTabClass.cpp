#include "optionTabClass.h"
#include "../fonctions_all.h"
#include "../constantes.h"
#include "../fileutils.h"
#include "../json/json.h"

#include <iostream>
#include <ctime>

#include "../widget.h"

OptionTab::OptionTab(Widget *parent) : QWidget(parent)
{
    conf_file = parent->getConfigFile();

    for(int i=0;i<LAYOUT_NUMBER_OPTIONS;i++)
    {
        horizontalLayouts[i] = new QHBoxLayout;
    }

    parentWidget = parent;

    /*Déclaration des objets*/
    groupBox = new QGroupBox("Options",this);
    layoutGroupBox = new QVBoxLayout;

    groupBoxCredits = new QGroupBox("Credits",this);


    layoutMain = new QVBoxLayout;
        credits = new QLabel("Gelbooru API | Moebooru API | Danbooru API",this);
        credits->setStyleSheet("qproperty-alignment: AlignCenter;");

            pushButtonUpdater = new QPushButton("Run Updater",this);

            pushButtonReset = new QPushButton("Reset Booru Settings",this);
            pushButtonCache = new QPushButton("Clear Cache",this);
            pushButtonRefreshCacheSize = new QPushButton("Refresh Cache",this);
            labelCache = new QLabel("Cache size :",this);

            pushButtonTags = new QPushButton("Refresh Tags",this);
            labelTags = new QLabel("Last refresh :",this);
/*
        QVBoxLayout *layoutDownloadPath2 = new QVBoxLayout;
            pushButtonResetAllDownloadPath = new QPushButton("Reset all download paths",this);
            lineEditDownloadPath = new QLineEdit(QString(root["paths"]["default_download_path"].asString().c_str()),this);*/

        checkBoxLoadingStartup = new QCheckBox("Load on Startup",this);
        checkBoxLoadingStartup->setChecked(conf_file->isLoadingOnStartup());

        searchRating = new QComboBox;
        searchRating->addItem("All");
        searchRating->addItem("Safe");
        searchRating->addItem("Questionnable");
        searchRating->addItem("Explicit");
        searchRating->setMaximumWidth(100);

        searchRating->setCurrentIndex(conf_file->getPreferredRating());

        labelDefaultRating = new QLabel("Default Rating");
        labelDefaultRating->setStyleSheet("qproperty-alignment: AlignCenter;");
        labelDefaultBooru = new QLabel("Default Booru");
        labelDefaultBooru->setStyleSheet("qproperty-alignment: AlignCenter;");

        defaultBooru = new QComboBox;
        for(int i=0;i<conf_file->getBooruNumber();i++)
        {
           defaultBooru->addItem(conf_file->getBooru(i)->getName().c_str());
        }
        defaultBooru->setMaximumWidth(100);

        QString tab2[2] = {"Colums","Rows"};
        QVBoxLayout *layout2 = new QVBoxLayout;
        for(int i=0;i<2;i++)
        {
            layoutImages[i] = new QHBoxLayout;
            labelQuadrillageImages[i] = new QLabel(tab2[i],this);
            nbImages[i] = new QComboBox;
            for(int j=0;j<10;j++)
            {
                nbImages[i]->addItem(QString::number(j));
            }
            layoutImages[i]->addWidget(labelQuadrillageImages[i]);
            layoutImages[i]->addWidget(nbImages[i]);
            layout2->addLayout(layoutImages[i]);
        }

        nbImages[0]->setCurrentIndex(conf_file->getPictureColumns());
        nbImages[1]->setCurrentIndex(conf_file->getPictureRow());

        textBrowserChangelog = new QTextBrowser(this);
        pushButtonSave = new QPushButton("Save Options",this);


    /*Assignations aux layouts*/
    QVBoxLayout *layoutMiscs[2];
    layoutMiscs[0] = new QVBoxLayout;
    layoutMiscs[1] = new QVBoxLayout;
    layoutMiscs[0]->addWidget(labelDefaultRating);
    layoutMiscs[0]->addWidget(searchRating);
    layoutMiscs[1]->addWidget(labelDefaultBooru);
    layoutMiscs[1]->addWidget(defaultBooru);

    horizontalLayouts[3]->addWidget(checkBoxLoadingStartup);
    horizontalLayouts[3]->addLayout(layoutMiscs[0]);
    horizontalLayouts[3]->addLayout(layoutMiscs[1]);
    horizontalLayouts[3]->addLayout(layoutMiscs[1]);
    horizontalLayouts[3]->addLayout(layout2);
    horizontalLayouts[3]->addStretch(1);

    //layoutDownloadPath2->addWidget(pushButtonResetAllDownloadPath);

    //horizontalLayouts[2]->addLayout(layoutDownloadPath2);
    //horizontalLayouts[2]->addWidget(lineEditDownloadPath);

    horizontalLayouts[4]->addWidget(credits);
    groupBoxCredits->setLayout(horizontalLayouts[4]);

    horizontalLayouts[5]->addStretch(1);
    horizontalLayouts[5]->addWidget(groupBoxCredits);
    horizontalLayouts[5]->addStretch(1);

    horizontalLayouts[0]->addWidget(pushButtonRefreshCacheSize);
    horizontalLayouts[0]->addWidget(pushButtonCache);
    horizontalLayouts[0]->addWidget(labelCache);
    horizontalLayouts[0]->addStretch(1);

    horizontalLayouts[1]->addWidget(pushButtonTags);
    horizontalLayouts[1]->addWidget(labelTags);
    horizontalLayouts[1]->addStretch(1);

    horizontalLayouts[6]->addWidget(pushButtonUpdater);

    for(int i=0;i<4;i++)
    {
        if(i!=2)
        {
            layoutGroupBox->addLayout(horizontalLayouts[i]) ;
        }
    }
    groupBox->setLayout(layoutGroupBox);

    layoutMain->addLayout(horizontalLayouts[5]);
    layoutMain->addWidget(groupBox);
    layoutMain->addWidget(textBrowserChangelog);
    layoutMain->addWidget(pushButtonSave);
    layoutMain->addWidget(pushButtonReset);
    layoutMain->addLayout(horizontalLayouts[6]);

    setLayout(layoutMain);

    /*Signaux*/
    connect(pushButtonCache, SIGNAL(clicked()), this, SLOT(deleteCache()));
    connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(resetBoorusSettings()));
    connect(pushButtonUpdater, SIGNAL(clicked()), this, SLOT(runUpdater()));
    connect(pushButtonTags, SIGNAL(clicked()), this, SLOT(refreshTagLists()));
    connect(pushButtonSave, SIGNAL(clicked()), this, SLOT(saveOptions()));
    connect(pushButtonResetAllDownloadPath, SIGNAL(clicked()), this, SLOT(resetBooruDownloadPath()));
    connect(pushButtonRefreshCacheSize, SIGNAL(clicked()),this,SLOT(refreshCacheSize()));

    refreshCacheSize();
    refreshTagTime();

    searchRating->setCurrentIndex(conf_file->getPreferredRating());
    defaultBooru->setCurrentIndex(conf_file->getPreferredBooru());
}

OptionTab::~OptionTab()
{
    for(int i=0;i<LAYOUT_NUMBER_OPTIONS;i++)
    {
        delete horizontalLayouts[i];
    }

    clearLayoutSecond(layoutGroupBox);
    clearLayoutSecond(layoutMain);
}

void OptionTab::resetBoorusSettings()
{
    //conf_file->

    parentWidget->refresh();
}

void OptionTab::deleteCache()
{
    FileUtils folder;
    bool success;
    int i;
    success = folder.removeDir(CACHE_PATH);

    if(success)
    {
        refreshCacheSize();
    }

    for(i=0;i<conf_file->getBooruNumber();i++)
    {
        checkFolder(conf_file->getBooru(i)->getCachePath());
        checkFolder(conf_file->getBooru(i)->getDownloadPath());
    }
}

void OptionTab::refreshCacheSize()
{
    int cache_size = dir_size(CACHE_PATH);
    QString cache_unit;

    if(cache_size > 1024*1024*1024)
    {
        cache_size = cache_size/(1024*1024*1024);
        cache_unit = " GB";
    }
    if(cache_size > 1024*1024)
    {
        cache_size = cache_size/(1024*1024);
        cache_unit = " MB";
    }
    else if(cache_size > 1024)
    {
        cache_size = cache_size/(1024);
        cache_unit = " kB";
    }
    else
    {
        cache_size = cache_size;
        cache_unit = " B";
    }

    labelCache->setText("Cache size : " + QString::number(cache_size) + cache_unit);
}

void OptionTab::runUpdater()
{
    runUpdaterFunction();
}

void OptionTab::refreshTagLists()
{
    int i;

    for(i=0;i<conf_file->getBooruNumber();i++)
    {
        cachingFile(strdup(conf_file->getBooru(i)->getTagUrl().c_str()), strdup(conf_file->getBooru(i)->getTagFilePath().c_str()),false, false);
    }

    refreshTagTime();

    int currentTime = time(NULL);
    //root["settings"]["last_tag_refresh"] =  currentTime;
}

void OptionTab::refreshTagTime()
{
    /*
    Json::Value root;
    root = loadJSONFile(CONF_FILE);

    int currentTime = time(NULL);
    int previousTime = root["settings"]["last_tag_refresh"].asInt();
    labelTags->setText(QString(returnTimeStringConvert(currentTime-previousTime).c_str()));
    */
}

void OptionTab::resetBooruDownloadPath()
{
    int i;

    std::vector<BooruSite*> boorus = conf_file->getBoorus();

    conf_file->setDownloadPath(lineEditDownloadPath->text().toStdString());
    conf_file->resetBooruSites();

    for(i=0;i<conf_file->getBooruNumber();i++)
    {
        boorus.at(i)->setDownloadPath(lineEditDownloadPath->text().toStdString() + boorus.at(i)->getName());
    }

    conf_file->setBoorus(boorus);
    conf_file->saveFile();
}

void OptionTab::saveOptions()
{
    conf_file->setDownloadPath(lineEditDownloadPath->text().toStdString());
    conf_file->setLoadingOnStartup(checkBoxLoadingStartup->isChecked());
    conf_file->setPreferredRating(searchRating->currentIndex());
    conf_file->setPreferredBooru(defaultBooru->currentIndex());
    conf_file->setPictureRow(nbImages[1]->currentText().toInt());
    conf_file->setPictureColumns(nbImages[0]->currentText().toInt());

    conf_file->saveFile();

    QMessageBox::information(this, "Info", "Configuration saved");
}
