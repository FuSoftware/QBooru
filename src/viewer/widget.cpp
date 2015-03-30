#include <iostream>
#include "widget.h"
#include "json/json.h"
#include "fonctions.h"
#include "fileutils.h"

#include "classBooruSite.h"

Widget::Widget(QMessageBox* msgBox, QWidget *parent) : QWidget(parent)
{
    LoadingWidget *loadingWidget;
    Json::Value root = loadJSONFile(CONF_FILE);
    int i;
    int booruIndexMax = root["settings"]["booru_number"].asInt();

    BooruSite boorus[booruIndexMax];
    loadBooruSites(boorus,booruIndexMax);

    mainLayout = new QVBoxLayout;

    setupHosts(boorus, booruIndexMax);

    tabWidgetMain = new QTabWidget(this);
    viewerIndex = booruIndexMax;

    for(i=0;i<booruIndexMax;i++)
    {
        searchtabs[i] = new SearchTab(this, boorus[i]);
        tabWidgetMain->addTab(searchtabs[i],hostNames[i]);
    }

    viewerTab = new ViewerTab(this);
    tabWidgetMain->addTab(viewerTab,"Image Viewer");
    optionTab = new OptionTab(this);
    tabWidgetMain->addTab(optionTab,"Options");
    settingTabs = new BooruSettingsTab(this);
    tabWidgetMain->addTab(settingTabs,"Edit Boorus");

    setMinimumSize(1024,768);
    mainLayout->addWidget(tabWidgetMain);
    setLayout(mainLayout);
    show();

    resize(root["settings"]["window_w"].asInt(), root["settings"]["window_h"].asInt());

    searchtabs[0]->checkPageButtonStatus();

    connect(tabWidgetMain,SIGNAL(currentChanged(int)), this, SLOT(on_tab_changed(int)));

    /*Chargement initial*/
    for(i=0;i<booruIndexMax;i++)
    {
        if(root["settings"]["load_on_startup"].asBool())
        {
            thread[i] = new QThread;
            connect(thread[i], SIGNAL(started()), searchtabs[i], SLOT(newSearch()));
            searchtabs[i]->moveToThread(thread[i]);
            thread[i]->start();
        }
    }

    tabWidgetMain->setCurrentIndex(root["settings"]["preferred_booru"].asInt());
}

Widget::~Widget()
{
    Json::Value root = loadJSONFile(CONF_FILE);
    Json::StyledWriter writer;
    root["settings"]["window_h"] = height();
    root["settings"]["window_w"] = width();
    saveJSONFile(CONF_FILE, writer.write(root));

    outputInfo("INFO",
               "Deleting Widget",
               LEVEL_TOP_WIDGET);

    clearLayoutSecond(mainLayout);
}

void Widget::refresh()
{
    int i;
    Json::Value root = loadJSONFile(CONF_FILE);
    int booruIndexMax = root["settings"]["booru_number"].asInt();

    BooruSite boorus[booruIndexMax];
    loadBooruSites(boorus,booruIndexMax);

    delete tabWidgetMain;

    setupHosts(boorus, booruIndexMax);

    tabWidgetMain = new QTabWidget(this);

    for(i=0;i<booruIndexMax;i++)
    {
        searchtabs[i] = new SearchTab(this, boorus[i]);
        tabWidgetMain->addTab(searchtabs[i],hostNames[i]);
    }

    viewerTab = new ViewerTab(this);
    tabWidgetMain->addTab(viewerTab,"Image Viewer");
    optionTab = new OptionTab(this);
    tabWidgetMain->addTab(optionTab,"Options");
    settingTabs = new BooruSettingsTab(this);
    tabWidgetMain->addTab(settingTabs,"Edit Boorus");
    mainLayout->addWidget(tabWidgetMain);

    tabWidgetMain->setCurrentIndex(booruIndexMax+2);
}

void Widget::setupHosts(BooruSite boorus[], int index)
{    
    for(int i=0;i<index;i++)
    {
        hostNames[i] = QString(boorus[i].name.c_str());
    }
}

void Widget::loadTag(QString tag, int imageHostInt)
{
    searchtabs[imageHostInt]->loadTagViewer(tag);
}

void Widget::on_tab_changed(int tabIndex)
{
    Json::Value root = loadJSONFile(CONF_FILE);
    int viewerIndex = root["settings"]["booru_number"].asInt();

    if(tabIndex < viewerIndex) //SearchPages
    {
        searchtabs[tabIndex]->checkPageButtonStatus();
    }

    if(tabIndex == viewerIndex) //Viewer
    {
        viewerTab->grabKeyboard();
    }
    else
    {
        viewerTab->releaseKeyboard();
    }
}

void Widget::setTab(int tab)
{
    tabWidgetMain->setCurrentIndex(tab);
}

