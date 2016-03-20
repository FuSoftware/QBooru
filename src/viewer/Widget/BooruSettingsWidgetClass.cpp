#include <iostream>
#include <ctime>

#include "BooruSettingsWidgetClass.h"
#include "booruSettingsTabClass.h"
#include "../classBooruSite.h"
#include "../json/json.h"
#include "widget.h"
#include "fonctions_all.h"

BooruSettings::BooruSettings(BooruSettingsTab *parent)
{
    conf_file = parent->getConfigFile();

    layoutMain = new QVBoxLayout;
    parentWidget = parent;
    QString buffer;
    int i=0;

    QList<QWidget*> list = generateInputs();

    groupBoxMainSettings = new QGroupBox("Main Settings", this);
    layoutGroupBoxMainSettings = new QVBoxLayout;

        layoutGroupBoxMainSettings->addWidget(list.at(L_NAME));

        checkBoxPreset = new QCheckBox("Presets",this);
        checkBoxPreset->setChecked(false);

        comboBoxPreset = new QComboBox(this);
        comboBoxPreset->setDisabled(true);
        layoutGroupBoxMainSettings->addWidget(checkBoxPreset);
        layoutGroupBoxMainSettings->addWidget(comboBoxPreset);

        Json::Value root = loadJSONFile(BOORU_LIST);
        while(i < root["boorus"].size())
        {
            buffer = QString(root["boorus"][i]["name"].asCString());
            buffer[0].toUpper();
            comboBoxPreset->addItem(buffer);
            i++;
        }

        //qDebug() << "Generated the Options tab" ;
        layoutGroupBoxMainSettings->addWidget(list.at(L_URL));
        //qDebug() << "Generated the Options tab" ;

        QHBoxLayout * lay = new QHBoxLayout;
        labelBooruType = new QLabel("Booru Type",this);
        comboBoxBooruType = new QComboBox(this);
        comboBoxBooruType->addItem("Derpibooru (not recommended, is being recoded)");
        comboBoxBooruType->addItem("Gelbooru");
        comboBoxBooruType->addItem("Moebooru");
        comboBoxBooruType->addItem("Danbooru");
        comboBoxBooruType->addItem("E621");
        lay->addWidget(labelBooruType);
        lay->addWidget(comboBoxBooruType);
        layoutGroupBoxMainSettings->addLayout(lay);
        layoutGroupBoxMainSettings->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));

        comboBoxBooruType->setCurrentIndex(GELBOORU_TYPE);


     groupBoxMainSettings->setLayout(layoutGroupBoxMainSettings);

     layoutMain->addWidget(groupBoxMainSettings);

     saveButton = new QPushButton("Save");

     connect(comboBoxPreset,SIGNAL(currentIndexChanged(int)),this,SLOT(loadPreset(int)));
     connect(checkBoxPreset,SIGNAL(clicked(bool)),comboBoxPreset,SLOT(setEnabled(bool)));

     layoutMain->addWidget(saveButton);

     setLayout(layoutMain);

}

BooruSettings::~BooruSettings()
{
    //clearLayout(layoutMain);
}

QList<QWidget*> BooruSettings::generateInputs()
{
    QList<QWidget*> list;
    QWidget* widget;
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit* lineEdit;

    for(int i=0;i<L_SIZE;i++)
    {
        widget = new QWidget(this);
        layout = new QHBoxLayout;
        label = new QLabel(label_strings[i],this);
        lineEdit = new QLineEdit(this);

        layout->addWidget(label);
        layout->addWidget(lineEdit);
        widget->setLayout(layout);
        list.push_back(widget);
        lineEdits.push_back(lineEdit);
    }

    return list;
}

void BooruSettings::editBooru()
{
    /*!
     Saves an edited booru into your config file, replacing its previous configuration
     */
    BooruSite *booru;
    int index = parentWidget->comboBoxBooru->currentIndex();

    booru = new BooruSite(lineEdits.at(L_NAME)->text().toStdString(),
                          lineEdits.at(L_URL)->text().toStdString(),
                          comboBoxBooruType->currentIndex(),
                          index);

    conf_file->setBooru(booru, index);
    conf_file->saveFile();
    delete booru;
}

void BooruSettings::loadBooru(int index)
{
    /*!
     Loads a saved Booru into the Widget, allowing for edits

     \param index of the booru to load
     */

    if(index < conf_file->getBooruNumber())
    {
        lineEdits.at(L_NAME)->setText(QString(conf_file->getBooru(index)->getName().c_str()));

        lineEdits.at(L_URL)->setText(QString(conf_file->getBooru(index)->getBaseUrl().c_str()));

        comboBoxBooruType->setCurrentIndex(conf_file->getBooru(index)->getSiteTypeInt());
    }
}

void BooruSettings::loadPreset(int index)
{
    /*!
     Loads a preset into the Widget, allowing for edits and save

     \param index of the booru to load
     */
    Json::Value root = loadJSONFile(BOORU_LIST);

    lineEdits.at(L_NAME)->setText(QString(root["boorus"][index]["name"].asCString()));

    lineEdits.at(L_URL)->setText(QString(root["boorus"][index]["base_url"].asCString()));

    comboBoxBooruType->setCurrentIndex(root["boorus"][index]["siteTypeInt"].asInt());
}
