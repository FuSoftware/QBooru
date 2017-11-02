#include "mainwidget.h"

#include "view/qboorutab.h"
#include "view/qboorupictureviewer.h"

MainWidget::MainWidget(QWidget *parent): QWidget(parent)
{
    loadUI();
}

MainWidget::~MainWidget()
{

}

void MainWidget::loadUI()
{
    this->tab_widget = new QTabWidget(this);
    this->viewer = new QBooruPictureViewer(this);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(tab_widget);
    this->setLayout(l);
}

void MainWidget::loadBoorus(QVector<BooruSite*> sites)
{
    for(int i=0;i<sites.size();i++)
    {
        this->addBooru(sites[i]);
    }

    this->reorderTabs();
}

void MainWidget::addBooru(BooruSite* site)
{
    QBooruTab *tab = new QBooruTab(site, this);
    this->tabs.push_back(tab);

    QObject::connect(tab, SIGNAL(pictureClicked(BooruPicture*)), this->viewer, SLOT(loadPicture(BooruPicture*)));
}

void MainWidget::reorderTabs()
{
    this->tab_widget->clear();

    //Booru Tabs
    for(int i=0;i<this->tabs.size();i++)
    {
        this->tab_widget->addTab(this->tabs[i], this->tabs[i]->getTitle());
    }

    //Viewer
    this->tab_widget->addTab(this->viewer, "Viewer");
}
