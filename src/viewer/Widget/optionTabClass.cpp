#include "optionTabClass.h"
#include "../fonctions.h"
#include "../constantes.h"
#include "../fileutils.h"
#include "../json/json.h"

#include <iostream>
#include <ctime>

#include "../widget.h"

OptionTab::OptionTab(Widget *parent) : QWidget(parent)
{
    Json::Value root;
    Json::StyledWriter writer;
    root = loadJSONFile(CONF_FILE);

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

        QVBoxLayout *layoutDownloadPath2 = new QVBoxLayout;
            pushButtonResetAllDownloadPath = new QPushButton("Reset all download paths",this);
            lineEditDownloadPath = new QLineEdit(QString(root["paths"]["default_download_path"].asString().c_str()),this);

        checkBoxLoadingStartup = new QCheckBox("Load on Startup",this);
        checkBoxLoadingStartup->setChecked(root["settings"]["load_on_startup"].asBool());

        searchRating = new QComboBox;
        searchRating->addItem("All");
        searchRating->addItem("Safe");
        searchRating->addItem("Questionnable");
        searchRating->addItem("Explicit");
        searchRating->setMaximumWidth(100);

        searchRating->setCurrentIndex(root["settings"]["preferred_rating"].asInt());

        labelDefaultRating = new QLabel("Default Rating");
        labelDefaultRating->setStyleSheet("qproperty-alignment: AlignCenter;");
        labelDefaultBooru = new QLabel("Default Booru");
        labelDefaultBooru->setStyleSheet("qproperty-alignment: AlignCenter;");

        defaultBooru = new QComboBox;
        for(int i=0;i<root["settings"]["booru_number"].asInt();i++)
        {
           defaultBooru->addItem(root["boorus"][i]["name"].asCString());
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

        nbImages[0]->setCurrentIndex(root["settings"]["picture_columns"].asInt());
        nbImages[1]->setCurrentIndex(root["settings"]["picture_rows"].asInt());

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

    layoutDownloadPath2->addWidget(pushButtonResetAllDownloadPath);

    horizontalLayouts[2]->addLayout(layoutDownloadPath2);
    horizontalLayouts[2]->addWidget(lineEditDownloadPath);

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
       layoutGroupBox->addLayout(horizontalLayouts[i]) ;
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

    searchRating->setCurrentIndex(root["settings"]["preferred_rating"].asInt());
    defaultBooru->setCurrentIndex(root["settings"]["preferred_booru"].asInt());
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
    Json::Value root = loadJSONFile(CONF_FILE);
    Json::StyledWriter writer;
    root = resetBooruSites(root);
    saveJSONFile(CONF_FILE,writer.write(root));

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

    Json::Value root = loadJSONFile(CONF_FILE);

    for(i=0;i<root["boorus"][i]["imageLimit"].asInt();i++)
    {
        checkFolder(root["boorus"][i]["cache_path"].asString());
        checkFolder(root["boorus"][i]["donwload_path"].asString());
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
    Json::Value root;
    Json::StyledWriter writer;
    root = loadJSONFile(CONF_FILE);

    for(i=0;i<root["settings"]["index"].asInt();i++)
    {
        cachingFile(strdup(root["boorus"][i]["tag"].asCString()), strdup(root["boorus"][i]["tag_file_path"].asCString()),false, false);
    }

    refreshTagTime();

    int currentTime = time(NULL);
    root["settings"]["last_tag_refresh"] =  currentTime;

    saveJSONFile(CONF_FILE, writer.write(root));
}

void OptionTab::refreshTagTime()
{
    Json::Value root;
    root = loadJSONFile(CONF_FILE);

    int currentTime = time(NULL);
    int previousTime = root["settings"]["last_tag_refresh"].asInt();
    labelTags->setText(QString(returnTimeStringConvert(currentTime-previousTime).c_str()));
}

void OptionTab::resetBooruDownloadPath()
{
    int i;
    Json::Value root;
    Json::StyledWriter writer;
    root = loadJSONFile(CONF_FILE);

    BooruSite boorus[root["settings"]["booru_number"].asInt()];
    loadBooruSites(boorus,root["settings"]["booru_number"].asInt());

    root["paths"]["default_download_path"] = lineEditDownloadPath->text().toStdString();
    for(i=0;i<root["settings"]["booru_number"].asInt();i++)
    {
        boorus[i].setDownloadPath(lineEditDownloadPath->text().toStdString() + boorus[i].getName());
        boorus[i].saveBooruSite();
    }

    saveJSONFile(CONF_FILE, writer.write(root));
}

void OptionTab::saveOptions()
{
    Json::Value root;
    Json::StyledWriter writer;
    root = loadJSONFile(CONF_FILE);

    root["paths"]["default_download_path"] = lineEditDownloadPath->text().toStdString();
    root["settings"]["load_on_startup"] = checkBoxLoadingStartup->isChecked();
    root["settings"]["preferred_rating"] = searchRating->currentIndex();
    root["settings"]["preferred_booru"] = defaultBooru->currentIndex();
    root["settings"]["picture_rows"] = nbImages[1]->currentText().toInt();
    root["settings"]["picture_columns"] = nbImages[0]->currentText().toInt();

    saveJSONFile(CONF_FILE, writer.write(root));

    QMessageBox::information(this, "Info", "Configuration saved");
}
