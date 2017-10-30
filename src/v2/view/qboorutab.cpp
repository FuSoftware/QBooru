#include "qboorutab.h"

QBooruTab::QBooruTab(BooruSite* site, QWidget *parent) : QWidget(parent)
{
    this->site = site;
    this->loadUI();
}

void QBooruTab::loadUI()
{
    this->search_widget = new QSearchWidget(this->site,15,this);
    this->main_grid = new QMainGrid(5,3,this);

    //Logic
    connect(this->search_widget,SIGNAL(loadedPictures(QVector<BooruPicture*>)),this->main_grid,SLOT(loadPictures(QVector<BooruPicture*>)));
    connect(this->main_grid, SIGNAL(pictureClicked(BooruPicture*)), this, SIGNAL(pictureClicked(BooruPicture*)));

    //Layout
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(this->search_widget);
    l->addWidget(this->main_grid);
    setLayout(l);


    this->search_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->main_grid->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    l->setAlignment(this->search_widget, Qt::AlignTop);
}

BooruSite* QBooruTab::getBooru()
{
    return this->site;
}
