#include "fonctions.h"
#include "widget.h"
#include "searchTabClass.h"
#include "imageTabClass.h"

#include "../classBooruSite.h"

SearchTab::SearchTab(Widget *parent, BooruSite site) : QWidget(parent)
{
    Json::Value root = loadJSONFile(CONF_FILE);
    picture_number = root["settings"]["picture_number"].asInt();
    picture_rows = root["settings"]["picture_rows"].asInt();
    picture_columns = root["settings"]["picture_columns"].asInt();

    booru = site;
    recherche = 0;
    derpibooruAPIKey = root["settings"]["api_key_derpibooru"].asString();
    int i=0;
    int j=0;
    int k=0;

    parentWidget = parent;

    installEventFilter(this);

    signalMapper = new QSignalMapper(this);
    buttonMapper = new QSignalMapper(this);

    /*Déclaration des objects*/
    layoutMain = new QVBoxLayout;

        layoutSearch = new QHBoxLayout;
        layoutTags = new QHBoxLayout;

            searchButton = new QPushButton("Refresh");
            lineEditTags = new QLineEdit;
            lineEditTags->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            lineEditTags->setMaximumHeight(21);

            layoutSearchStatus = new QVBoxLayout;
                progressBarSearch = new QProgressBar;
                progressBarSearch->setMaximumHeight(21);
                labelSearchStatus = new QLabel("Waiting for search");
                labelSearchStatus->setMaximumHeight(21);

            layoutSearchRating = new QHBoxLayout;

            searchRating = new QComboBox;
            searchRating->addItem("All");
            searchRating->addItem("Safe");
            searchRating->addItem("Questionnable");
            searchRating->addItem("Explicit");
            searchRating->setMaximumHeight(21);

        layoutImageTabs = new QGridLayout;
            for(i=0;i<picture_number;i++)
            { 
                imageTabs[i] = new ImageTab(this, booru.siteTypeInt);
                buttonMapper->setMapping(imageTabs[i]->imageThumbnail, i);
                connect(imageTabs[i]->imageThumbnail, SIGNAL(clicked()), buttonMapper , SLOT(map()));
            }

        layoutSearchPage = new QHBoxLayout;
            pushButtonPageMoins = new QPushButton("<--");
            lineEditPageSet = new QLineEdit("1");
            lineEditPageSet->setStyleSheet("qproperty-alignment: AlignCenter;");
            pushButtonPagePlus = new QPushButton("-->");

    /*Assignation des layout*/

        /*SearchStatus*/
        layoutSearchStatus->addWidget(progressBarSearch);
        layoutSearchStatus->addWidget(labelSearchStatus);

    /*Search elements*/
    QVBoxLayout *verticalLayoutSearch = new QVBoxLayout;
    layoutSearchRating->addWidget(searchRating);
    layoutSearchRating->addWidget(searchButton);
    layoutSearchRating->addWidget(lineEditTags);
    verticalLayoutSearch->addLayout(layoutSearchRating);
    verticalLayoutSearch->addLayout(layoutTags);
    layoutSearch->addLayout(verticalLayoutSearch,3);
    layoutSearch->addLayout(layoutSearchStatus,1);

    /*SearchPage*/
    layoutSearchPage->addStretch(1);
    layoutSearchPage->addWidget(pushButtonPageMoins);
    layoutSearchPage->addWidget(lineEditPageSet);
    layoutSearchPage->addWidget(pushButtonPagePlus);
    layoutSearchPage->addStretch(1);

    /*ImageTabs*/
    for(j=0;j<picture_rows;j++)
    {
        for(i=0;i<picture_columns;i++)
        {
           layoutImageTabs->addWidget(imageTabs[k], j, i);
           layoutImageTabs->setAlignment(imageTabs[k],Qt::AlignCenter);
           k++;
        }
    }
    layoutImageTabs->setVerticalSpacing(0);
    layoutImageTabs->setHorizontalSpacing(0);

    signalMapper->setMapping(searchButton, 0);
    signalMapper->setMapping(lineEditTags, 1);
    signalMapper->setMapping(lineEditPageSet, 2);
    signalMapper->setMapping(pushButtonPageMoins, 3);
    signalMapper->setMapping(pushButtonPagePlus, 4);

    connect(searchButton, SIGNAL(clicked()), signalMapper , SLOT(map()));
    connect(lineEditTags, SIGNAL(returnPressed()),signalMapper,SLOT(map()));
    connect(lineEditPageSet, SIGNAL(returnPressed()),signalMapper,SLOT(map()));
    connect(pushButtonPageMoins, SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(pushButtonPagePlus, SIGNAL(clicked()),signalMapper,SLOT(map()));

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(searchActionToggled(int)));
    connect(buttonMapper, SIGNAL(mapped(int)), this, SLOT(setViewer(int)));


    /*Main Layout*/
    layoutMain->addLayout(layoutSearch);
    layoutMain->addLayout(layoutImageTabs);
    layoutMain->addLayout(layoutSearchPage);

    setLayout(layoutMain);

    initialisationMiniatures();


    pushButtonPagePlus->setDisabled(true);

    for(i=0;i<picture_number;i++)
    {
        imageTabs[i]->setDisabled(true);
        isAffiched[i] = false;
    }
    checkPageButtonStatus();

    searchRating->setCurrentIndex(root["settings"]["preferred_rating"].asInt());
}

SearchTab::~SearchTab()
{
    int i;
    for(i=0;i<picture_number;i++)
    {
        delete imageTabs[i];
    }
    clearLayoutSecond(layoutMain);
}

void SearchTab::initialisationMiniatures()
{
    int i = 0;
    QString pathFile, uploader;

    pathFile = QString(CONFPATH)+QString("derpibooruDefault.png");

    if(recherche)
    {
        uploader = "Loading picture";
    }
    else
    {
        uploader = "Waiting for search";
    }

    for(i=0;i<picture_number;i++)
    {
        imageTabs[i]->setDisabled(false);
        imageTabs[i]->loadPicture(pathFile, uploader);
    }
}


void SearchTab::loadTagViewer(QString tagString)
{
    lineEditTags->setText(tagString);
    lineEditPageSet->setText("1");
    loadSearch(1);
}

void SearchTab::loadSearch(int refreshTags)
{
    recherche = 1;
    QString tags;
    QString pathFile =  QString(CONFPATH)+QString("derpibooruDefault.png");
    int i = 0;

    if(refreshTags == 1)
    {
        tags = lineEditTags->text();

        switch(booru.siteTypeInt)
        {
        case DERPIBOORU_TYPE:
            switch(searchRating->currentIndex())
            {
            case RATING_SAFE:
                tags += ",safe";
                break;
            case RATING_QUESTIONNABLE:
                tags += ",questionable";
                break;
            case RATING_EXPLICIT:
                 tags += ",explicit" ;
                break;
            }
            break;
        case GELBOORU_TYPE:
            switch(searchRating->currentIndex())
            {
            case RATING_SAFE:
                tags += " rating:safe";
                break;
            case RATING_QUESTIONNABLE:
                tags += " rating:questionable";
                break;
            case RATING_EXPLICIT:
                 tags += " rating:explicit" ;
                break;
            }
            break;
        case MOEBOORU_TYPE:
        case DANBOORU_TYPE:
            switch(searchRating->currentIndex())
            {
            case RATING_SAFE:
                tags += " rating:s";
                break;
            case RATING_QUESTIONNABLE:
                tags += " rating:q";
                break;
            case RATING_EXPLICIT:
                 tags += " rating:e" ;
                break;
            }
        }
    }
    else
    {
        tags = tagsSearched;
    }

    progress = 0;
    int state;

    initialisationMiniatures();

    labelSearchStatus->setText("Loading search page");
    progressBarSearch->setValue(progress);
    parentWidget->viewerTab->labelLoading->setText("Loading search page");
    parentWidget->viewerTab->progressBar->setValue(progress);

    /*Tags*/

    switch(booru.siteTypeInt)
    {
    case DERPIBOORU_TYPE:
        state = setTagsDerpibooru(tags.toStdString(), lineEditPageSet->text().toStdString(), derpibooruAPIKey, booru.cache_path, booru.search_url);
        break;
    case GELBOORU_TYPE:
        state = setTagsGelbooru(tags.toStdString(), lineEditPageSet->text().toInt(), picture_number, booru.search_file_path, booru.search_url);
        break;
    case MOEBOORU_TYPE:
        state = setTagsMoebooru(tags.toStdString(), lineEditPageSet->text().toStdString(), picture_number, booru.cache_path, booru.search_url);
        break;
    case DANBOORU_TYPE:
        state = setTagsDanbooru(tags.toStdString(), lineEditPageSet->text().toStdString(), picture_number, booru.cache_path, booru.search_url);
        break;
    }

    /*Chargement*/

    if(state == 0)
    {
        loaded_pictures = 0;

        progress +=20;//Progress = 20
        progressBarSearch->setValue(progress);
        labelSearchStatus->setText("Loading pictures");
        parentWidget->viewerTab->labelLoading->setText("Loading pictures");
        parentWidget->viewerTab->progressBar->setValue(progress);

        switch(booru.siteTypeInt)
        {
        case DERPIBOORU_TYPE:
            chargementImagesDerpibooru(images, booru.search_file_path);
            break;
        case GELBOORU_TYPE:
            chargementImagesGelbooru(images, booru.search_file_path);
            break;
        case MOEBOORU_TYPE:
            chargementImagesMoebooru(images, booru.search_file_path);
            break;
        case DANBOORU_TYPE:
            chargementImagesDanbooru(images, booru.search_file_path,booru.base_url);
            break;
        }

        progress +=20;//Progress = 40
        progressBarSearch->setValue(progress);
        labelSearchStatus->setText("Loading thumbnails");
        parentWidget->viewerTab->labelLoading->setText("Loading thumbnails");
        parentWidget->viewerTab->progressBar->setValue(progress);

        loaded_pictures = 0;

        for(i=0;i<picture_number;i++)
        {
            if(images[i].id != 0)
            {
                imageTabs[i]->setDisabled(false);
                isAffiched[i] = true;
                startLoadingPicture(i);
                //imageRefreshUnique(i);
            }
            else
            {
                imageTabs[i]->loadPicture(pathFile, "...");
                imageTabs[i]->setDisabled(true);
                isAffiched[i] = false;
            }
        }
        outputInfo("INFO","Search completed",LEVEL_SEARCH);
    }
    else
    {
        labelSearchStatus->setText(QString("Error loading search (Error ") + QString::number(state) + QString(")"));
    }
    tagsSearched = tags;
}

void SearchTab::searchActionToggled(int sender)
{
    //0 = Search Button
    //1 = lineEdit Tags
    //2 = lineEdit Page Set
    //3 = pushButton Page Moins
    //4 = pushButton Page Plus
    int refresh;

    switch(sender)
    {
    case 0:
        refresh = 1;
        break;
    case 1:
        refresh = 1;
        break;
    case 2:
        refresh = 0;
        break;
    case 3:
        on_pushButton_pageMoins_clicked();
        refresh = 0;
        break;
    case 4:
        on_pushButton_pagePlus_clicked();
        refresh = 0;
        break;
    }

    if(refresh == 1)
    {
        lineEditPageSet->setText("1");
    }

    loadSearch(refresh);
}

void SearchTab::on_pushButton_pagePlus_clicked()
{
    int pageNumber;
    QString pageText;
    QString tags = tagsSearched;

    pageText = lineEditPageSet->text();

    pageNumber = pageText.toInt();
    pageNumber++;

    lineEditPageSet->setText(QString::number(pageNumber));
    checkPageButtonStatus();
}

void SearchTab::on_pushButton_pageMoins_clicked()
{
    int pageNumber;
    QString pageText;

    pageText = lineEditPageSet->text();

    pageNumber = pageText.toInt();

    if(pageNumber > 1)
    {
        pageNumber--;
        lineEditPageSet->setText(QString::number(pageNumber));
    }
    checkPageButtonStatus();
}

void SearchTab::setViewer(int sender)
{
    parentWidget->viewerTab->loadPicture(booru.siteTypeInt, booru.index, sender, lineEditPageSet->text().toInt(), booru);
}

void SearchTab::checkPageButtonStatus()
{
    int i;

    if(lineEditPageSet->text().toInt() == 1)
    {
        pushButtonPageMoins->setDisabled(true);
    }
    else
    {
        pushButtonPageMoins->setDisabled(false);
    }

    for(i=0;i<picture_number;i++)
    {
        if(isAffiched)
        {
            pushButtonPagePlus->setDisabled(false);
        }
        else
        {
            pushButtonPagePlus->setDisabled(true);
        }
    }
}

void SearchTab::setKeyboard()
{
    //grabKeyboard();
}

bool SearchTab::eventFilter(QObject *object, QEvent *event)
{
    if (object != lineEditTags && object != lineEditPageSet && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *k = static_cast<QKeyEvent *>(event);
        if(k->key() == Qt::Key_Left)
        {
            on_pushButton_pageMoins_clicked();
            loadSearch(0);
            return QWidget::event(event);
        }
        else if(k->key() == Qt::Key_Right)
        {
            on_pushButton_pagePlus_clicked();
            loadSearch(0);
            return  QWidget::event(event);
        }
        else
        {
            return false;
        }
    }
    else
    {
    }
    return false;
}

void SearchTab::newSearch()
{
    loadSearch(1);
    outputInfo("INFO","Thread Started",LEVEL_TOP_WIDGET);
}

void SearchTab::startLoadingPicture(int i)
{
    thread_pool_loading[i] = new QThread;
    loading_worker[i] = new SearchTabLoadingWorker(this,i);

    loading_worker[i]->moveToThread(thread_pool_loading[i]);

    connect(thread_pool_loading[i], SIGNAL(started()), loading_worker[i], SLOT(process()));
    connect(loading_worker[i], SIGNAL(finished()), thread_pool_loading[i], SLOT(quit()));
    connect(loading_worker[i], SIGNAL(finished()), loading_worker[i], SLOT(deleteLater()));
    connect(loading_worker[i], SIGNAL(finished()), this, SLOT(image_loaded()));
    connect(thread_pool_loading[i], SIGNAL(finished()), thread_pool_loading[i], SLOT(deleteLater()));

    thread_pool_loading[i]->start();
}

void SearchTab::image_loaded()
{
    loaded_pictures++;
    progress += 4;
    progressBarSearch->setValue(progress);
    parentWidget->viewerTab->progressBar->setValue(progress);

    labelSearchStatus->setText(QString("Loaded thumbnails ") + QString::number(loaded_pictures) + QString("/") + QString::number(picture_number));
    parentWidget->viewerTab->labelLoading->setText(QString("Loaded thumbnails ") + QString::number(loaded_pictures) + QString("/") + QString::number(picture_number));
}
