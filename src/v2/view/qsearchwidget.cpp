#include "qsearchwidget.h"

QSearchWidget::QSearchWidget(BooruSite *site, int limit, QWidget *parent) : QWidget(parent)
{
    this->site = site;
    this->engine = new BooruSearchEngine(site);
    this->limit = limit;
    this->page = site->getAPI()->getStartPage();
    loadUI();
}

void QSearchWidget::loadUI()
{
    pushButtonSearch = new QPushButton("Search",this);
    lineEditTags = new QLineEdit();

    QHBoxLayout *l = new QHBoxLayout;
    l->addWidget(lineEditTags);
    l->addWidget(pushButtonSearch);

    setLayout(l);

    connect(pushButtonSearch,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(lineEditTags,SIGNAL(returnPressed()),this,SLOT(search()));
}

void QSearchWidget::setPage(int page)
{
    this->page = page;
    search(page);
}

void QSearchWidget::search()
{
    this->tags = lineEditTags->text();
    this->page = this->site->getAPI()->getStartPage();;
    emit pageSet(this->page);

    search(this->tags, this->page, this->limit);
}

void QSearchWidget::search(int page)
{
    search(this->tags, page, this->limit);
}

void QSearchWidget::search(QString tags, int page, int limit)
{
    engine->set(tags,page,limit);

    QThread *t = new QThread(this);
    worker = new QSearchWorker(engine);

    worker->moveToThread(t);

    //Thread Management
    connect(t, SIGNAL(started()),  worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), t, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    //Output
    connect(worker,SIGNAL(results(QVector<BooruPicture*>)),this,SIGNAL(loadedPictures(QVector<BooruPicture*>)));

    t->start();
}
