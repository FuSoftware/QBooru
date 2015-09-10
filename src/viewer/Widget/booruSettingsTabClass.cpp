#include <iostream>

#include "booruSettingsTabClass.h"
#include "BooruSettingsWidgetClass.h"
#include "../classBooruSite.h"
#include "../json/json.h"
#include "widget.h"
#include "fonctions_all.h"

BooruSettingsTab::BooruSettingsTab(Widget *parent)
{
    conf_file = parent->getConfigFile();

    selectedBooru = 0;
    mainGridLayout = new QGridLayout;

    parentWidget = parent;

    QLabel *label2 = new QLabel("<b>Edit Booru</b>", this);
    label2->setMaximumSize(label2->maximumWidth(),21);
    label2->setStyleSheet("qproperty-alignment: AlignCenter;");

    comboBoxBooru = new QComboBox(this);

    loadBoorus();

    editBooruWidget = new BooruSettings(this);

    mainGridLayout->addWidget(label2,0,0);

    mainGridLayout->addWidget(comboBoxBooru,1,0);

    mainGridLayout->addWidget(editBooruWidget,2,0);

    pushbuttonDeleteBooru = new QPushButton("Delete");

    void (QComboBox:: *indexChangedSignal)(int) = &QComboBox::currentIndexChanged;

    connect(editBooruWidget->saveButton,SIGNAL(clicked()), editBooruWidget, SLOT(editBooru()));
    connect(editBooruWidget->saveButton,SIGNAL(clicked()), parentWidget, SLOT(refresh()));

    connect(pushbuttonDeleteBooru,SIGNAL(clicked()), this, SLOT(deleteBooru()));
    connect(pushbuttonDeleteBooru,SIGNAL(clicked()), parentWidget, SLOT(refresh()));

    connect(comboBoxBooru,
            SIGNAL(currentIndexChanged(int)),
            editBooruWidget,
            SLOT(loadBooru(int)));

    connect(comboBoxBooru,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(refreshActiveBooru(int)));

    mainGridLayout->addWidget(pushbuttonDeleteBooru,3,0);

    setLayout(mainGridLayout);
}

BooruSettingsTab::~BooruSettingsTab()
{
    //clearLayout(mainGridLayout);
}

void BooruSettingsTab::refreshActiveBooru(int index)
{
    selectedBooru = index;
}

void BooruSettingsTab::loadBoorus()
{
    comboBoxBooru->clear();

    for(int i=0; i < conf_file->getBooruNumber(); i++)
    {
        comboBoxBooru->addItem(QString(conf_file->getBooru(i)->getName().c_str()));
    }

    comboBoxBooru->addItem("New Booru");
}

void BooruSettingsTab::deleteBooru()
{
    int booru_number = conf_file->getBooruNumber();

    for(int i=selectedBooru ; i<booru_number ; i++)
    {
        conf_file->getBoorus().at(i) = conf_file->getBoorus().at(i+1);
    }

    conf_file->getBoorus().erase(conf_file->getBoorus().begin()+booru_number);
    conf_file->setBooruNumber(booru_number-1);
    conf_file->saveFile();
}

ConfigFile *BooruSettingsTab::getConfigFile()
{
    return conf_file;
}
