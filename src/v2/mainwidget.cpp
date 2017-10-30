#include "mainwidget.h"

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
}

void MainWidget::addBooru(BooruSite* site)
{
    QBooruTab *tab = new QBooruTab(site);
    this->tab_widget->addTab(tab, QString::fromStdString(site->getName()));
}
