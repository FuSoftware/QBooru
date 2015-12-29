#include "widget.h"

Widget::Widget(ConfigFile * cfg, QWidget *parent) : QWidget(parent)
{
    conf_file = cfg;

    int i;
    int booruIndexMax = conf_file->getBooruNumber();

    std::vector<BooruSite*> boorus;
    boorus = conf_file->getBoorus();

    mainLayout = new QVBoxLayout;

    setupHosts(boorus, booruIndexMax);

    tabWidgetMain = new QTabWidget(this);
    viewerIndex = booruIndexMax;

    for(i=0;i<booruIndexMax;i++)
    {
        searchtabs[i] = new SearchTab(this, boorus.at(i));
        tabWidgetMain->addTab(searchtabs[i],hostNames[i]);
    }

    viewerTab = new ViewerTab(this);
    tabWidgetMain->addTab(viewerTab,"Image Viewer");
    grabberTab = new GrabberWidget(this);
    tabWidgetMain->addTab(grabberTab,"Grabber");
    optionTab = new OptionTab(this);
    tabWidgetMain->addTab(optionTab,"Options");
    settingTabs = new BooruSettingsTab(this);
    tabWidgetMain->addTab(settingTabs,"Edit Boorus");

    setMinimumSize(1024,768);
    mainLayout->addWidget(tabWidgetMain);
    setLayout(mainLayout);
    show();

    resize(conf_file->getWindowW(), conf_file->getWindowH());

    //searchtabs[0]->checkPageButtonStatus();

    connect(tabWidgetMain,SIGNAL(currentChanged(int)), this, SLOT(on_tab_changed(int)));

    /*Chargement initial*/
    for(i=0;i<booruIndexMax;i++)
    {
        if(conf_file->isLoadingOnStartup())
        {
            thread[i] = new QThread;
            connect(thread[i], SIGNAL(started()), searchtabs[i], SLOT(newSearch()));
            searchtabs[i]->moveToThread(thread[i]);
            thread[i]->start();
        }
    }

    tabWidgetMain->setCurrentIndex(conf_file->getPreferredBooru());
}

Widget::~Widget()
{
    outputInfo(L_INFO,"Deleting Widget");

    //clearLayoutSecond(mainLayout);
}

void Widget::refresh()
{
    int i;
    int booruIndexMax = conf_file->getBooruNumber();

    std::vector<BooruSite*> boorus;
    boorus = conf_file->getBoorus();

    delete tabWidgetMain;

    setupHosts(boorus, booruIndexMax);

    tabWidgetMain = new QTabWidget(this);

    for(i=0;i<booruIndexMax;i++)
    {
        searchtabs[i] = new SearchTab(this, boorus.at(i));
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

void Widget::setupHosts(std::vector<BooruSite*> boorus, int index)
{    
    for(int i=0;i<index;i++)
    {
        hostNames[i] = QString(boorus.at(i)->getName().c_str());
    }
}

void Widget::loadTag(QString tag, int imageHostInt)
{
    searchtabs[imageHostInt]->loadTagViewer(tag);
}

void Widget::on_tab_changed(int tabIndex)
{
    int viewerIndex = conf_file->getBooruNumber();

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

    if(tabIndex == viewerIndex+1) //Grabber
    {
        QMessageBox::warning(this,"Grabber","The Grabber is still an experimental feature.\nThis feature is heavy for servers, and you may get blocked, or banned.\nYour IP and UserID are recorded in case of abuse, and are sent through the created cookies.\n\nIn case of IP or ID ban, I'm not responsible. Please don't overuse this feature.");
    }
}

void Widget::setTab(int tab)
{
    tabWidgetMain->setCurrentIndex(tab);
}

ConfigFile *Widget::getConfigFile()
{
    return conf_file;
}
