#include "qboorutab.h"

#include "qsearchwidget.h"
#include "qmaingrid.h"
#include "qpageswitcher.h"

QBooruTab::QBooruTab(BooruSite* site, QWidget *parent) : QWidget(parent)
{
    this->site = site;
    this->loadUI();
}

void QBooruTab::loadUI()
{
    this->search_widget = new QSearchWidget(this->site,15, this);
    this->main_grid = new QMainGrid(5,3,this);
    this->page_switcher = new QPageSwitcher(this->site, this);

    //Logic
    connect(this->search_widget,SIGNAL(loadedPictures(QVector<BooruPicture*>)),this->main_grid,SLOT(loadPictures(QVector<BooruPicture*>)));
    connect(this->main_grid, SIGNAL(pictureClicked(BooruPicture*)), this, SIGNAL(pictureClicked(BooruPicture*)));

    connect(this->page_switcher, SIGNAL(openPage(int)), this->search_widget, SLOT(setPage(int)));
    connect(this->search_widget, SIGNAL(pageSet(int)), this->page_switcher, SLOT(setCurrentPage(int)));

    //Layout
    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(this->search_widget);
    l->addWidget(this->main_grid);
    l->addWidget(this->page_switcher);
    setLayout(l);


    this->page_switcher->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->search_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    this->main_grid->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    l->setAlignment(this->search_widget, Qt::AlignTop);
}

BooruSite* QBooruTab::getBooru()
{
    return this->site;
}

QString QBooruTab::getTitle()
{
    return QString::fromStdString(this->site->getName());
}
