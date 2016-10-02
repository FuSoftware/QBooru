#include "qsearchtab.h"

QSearchTab::QSearchTab(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

QSearchTab::QSearchTab(BooruSite* site,QWidget *parent) : QWidget(parent)
{
    loadUI();
    setupBooru(site);
}

void QSearchTab::loadUI()
{
    int rSize = 5;
    int cSize = 3;

    QPushButton* pbSearch = new QPushButton("Search",this);
    QPushButton* pbNextPage = new QPushButton("-->",this);
    QPushButton* pbPrevPage = new QPushButton("<--",this);

    //LineEdits
    lineEditPageNumber = new QLineEdit(this);
    lineEditSearch = new QLineEdit(this);

    //ComboBox
    QComboBox* cbRating = new QComboBox(this);

    //Layouts
    QHBoxLayout* layoutSearch = new QHBoxLayout;
    QGridLayout* layoutPictures = new QGridLayout;
    QVBoxLayout* layoutMain = new QVBoxLayout;
    QHBoxLayout* layoutPage = new QHBoxLayout;

    for(int i=0;i<rSize*cSize;i++)
    {
        pictureWidgets.push_back(new QBooruPicture(this));
        layoutPictures->addWidget(pictureWidgets.at(i),i/rSize,i%rSize);
    }

    layoutSearch->addWidget(cbRating);
    layoutSearch->addWidget(lineEditSearch);
    layoutSearch->addWidget(pbSearch);

    layoutPage->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed));
    layoutPage->addWidget(pbPrevPage);
    layoutPage->addWidget(lineEditPageNumber);
    layoutPage->addWidget(pbNextPage);
    layoutPage->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed));

    layoutMain->addLayout(layoutSearch);
    layoutMain->addLayout(layoutPictures);
    layoutMain->addLayout(layoutPage);

    setLayout(layoutMain);

    //Connections
    connect(pbSearch,SIGNAL(clicked()),this,SLOT(search()));
}

void QSearchTab::setupBooru(BooruSite* booru)
{
    this->booru = booru;
    engine = new BooruSearchEngine(booru);
}

void QSearchTab::search()
{
    pictures = engine->search(lineEditSearch->text().toStdString(),lineEditPageNumber->text().toInt());
}
