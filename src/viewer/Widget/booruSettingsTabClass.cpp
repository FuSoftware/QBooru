#include <iostream>

#include "booruSettingsTabClass.h"
#include "BooruSettingsWidgetClass.h"
#include "../classBooruSite.h"
#include "../json/json.h"
#include "widget.h"
#include "fonctions_all.h"

BooruSettingsTab::BooruSettingsTab(Widget *parent)
{
    selectedBooru = 0;
    mainGridLayout = new QGridLayout;

    Json::Value root = loadJSONFile(CONF_FILE);
    parentWidget = parent;

    QLabel *label2 = new QLabel("<b>Edit Booru</b>", this);
    label2->setMaximumSize(label2->maximumWidth(),21);
    label2->setStyleSheet("qproperty-alignment: AlignCenter;");

    comboBoxBooru = new QComboBox(this);

    for(int i=0; i < root["settings"]["booru_number"].asInt(); i++)
    {
        comboBoxBooru->addItem(QString(root["boorus"][i]["name"].asCString()));
    }
    comboBoxBooru->addItem("New Booru");
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
    clearLayout(mainGridLayout);
}

void BooruSettingsTab::refreshActiveBooru(int index)
{
    selectedBooru = index;
}

void BooruSettingsTab::deleteBooru()
{
    Json::Value root = loadJSONFile(CONF_FILE);
    int booru_number = root["settings"]["booru_number"].asInt();

    for(int i=selectedBooru ; i<booru_number ; i++)
    {
        root["boorus"][i] = root["boorus"][i+1];
    }

    root["boorus"][booru_number].clear();

    root["settings"]["booru_number"] = booru_number-1;

    Json::StyledWriter writer;
    saveJSONFile(CONF_FILE,writer.write(root));
}
