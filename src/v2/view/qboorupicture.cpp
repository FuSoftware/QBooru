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

void QBooruPicture::setBooruPicture(BooruPicture* picture)
{
    this->picture = picture;

    QString text = QString::number(picture->getW()) + QString("x") + QString::number(picture->getH());
    setText(text);

    //TODO : Thread this
    ConnectionManager *mgr = new ConnectionManager;
    mgr->downloadFile(picture->getThumbnailUrl(), picture->getThumbnailPath(),true);

    QPixmap pixmap;
    pixmap.load(QString(picture->getThumbnailPath().c_str()));
    setPixmap(pixmap);
}

void QBooruPicture::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    labelPicture->setPixmap(pixmap);
}

void QBooruPicture::setText(QString text)
{
    labelComment->setText(text);
}
