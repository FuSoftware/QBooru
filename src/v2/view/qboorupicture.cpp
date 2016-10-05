#include "qboorupicture.h"

QBooruPicture::QBooruPicture(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

QBooruPicture::QBooruPicture(BooruPicture *picture, QWidget *parent) : QWidget(parent)
{
    loadUI();
    setBooruPicture(picture);
}

void QBooruPicture::loadUI()
{
    labelPicture = new QLabel("Picture",this);
    labelComment = new QLabel("Size",this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelPicture);
    layout->addWidget(labelComment);

    setLayout(layout);
}

void QBooruPicture::loadBooruPicture(BooruPicture* picture)
{
    this->picture = picture;

    thread = new QThread;
    worker = new QDownloadWorker(picture,PREVIEW,false);

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(worker,SIGNAL(downloaded(QString)),this,SLOT(loadPixmap(QString)));

    thread->start();

    QString text = QString::number(picture->getW()) + QString("x") + QString::number(picture->getH());
    setText(text);
}

void QBooruPicture::setBooruPicture(BooruPicture* picture)
{
    this->picture = picture;

    QString text = QString::number(picture->getW()) + QString("x") + QString::number(picture->getH());
    setText(text);
    loadPixmap(QString(picture->getThumbnailPath().c_str()));
}

void QBooruPicture::loadPixmap(QString file)
{
    qDebug() << "Loading pixmap from" << file;
    QPixmap pixmap;
    pixmap.load(file);
    setPixmap(pixmap);
}

void QBooruPicture::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    pixmap.scaled(150,150, Qt::KeepAspectRatio);
    labelPicture->setPixmap(pixmap);
}

void QBooruPicture::setText(QString text)
{
    labelComment->setText(text);
}
