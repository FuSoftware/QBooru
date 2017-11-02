#include "qsearchwidget.h"

QSearchWidget::QSearchWidget(BooruSite *site, int limit, QWidget *parent) : QWidget(parent)
{
    this->site = site;
    this->engine = new BooruSearchEngine(site);
    this->limit = limit;
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

void QSearchWidget::search()
{
    QString tags = lineEditTags->text();

    engine->set(tags.toStdString(),0,limit);

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
