#include "qboorupicture.h"

#include "model/boorupicture.h"
#include "controller/boorupixmapdownloader.h"

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
    labelPicture = new ClickableLabel("Picture",this);
    labelComment = new QLabel("Size",this);

    labelPicture->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelPicture);
    layout->addWidget(labelComment);

    layout->setAlignment(labelPicture, Qt::AlignCenter | Qt::AlignVCenter);
    layout->setAlignment(labelComment, Qt::AlignCenter | Qt::AlignBottom);

    setLayout(layout);
    connect(labelPicture, SIGNAL(clicked()), this, SLOT(onPictureClicked()));
}

void QBooruPicture::onPictureClicked()
{
    if(this->picture)
    {
        qDebug() << "Clicked picture " << QString::number(this->picture->getID()) << " from booru " << QString::fromStdString(this->picture->getWebsite()->getName());
        qDebug() << "PREVIEW: " << QString::fromStdString(this->picture->getURL(0));
        qDebug() << "PREVIEW_jpg: " << QString::fromStdString(this->picture->getURL(1));
        qDebug() << "SAMPLE" << QString::fromStdString(this->picture->getURL(2));
        qDebug() << "FULL" << QString::fromStdString(this->picture->getURL(3));
        qDebug() << "PICTURE_TYPE_END" << QString::fromStdString(this->picture->getURL(4));
        emit pictureClicked(this->picture);
    }
}

void QBooruPicture::setBooruPicture(BooruPicture* picture)
{
    //Delete the previously stored picture to prevent memory leaks
    if(this->picture != 0)
        delete this->picture;

    this->picture = picture;

    QString text = QString::number(picture->getW()) + QString("x") + QString::number(picture->getH());
    setText(text);

    BooruPixmapDownloader* d = new BooruPixmapDownloader(picture, PictureType::PREVIEW, true);
    QThread* t = new QThread(this);

    d->moveToThread(t);

    //Thread Management
    connect(t, SIGNAL(started()),  d, SLOT(process()));
    connect(d, SIGNAL(finished()), t, SLOT(quit()));
    connect(d, SIGNAL(finished()), d, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    //Output
    connect(d, SIGNAL(pixmapLoaded(QPixmap)), this, SLOT(setPixmap(QPixmap)));

    t->start();
}

void QBooruPicture::setBooruPictureEmpty()
{
    //Delete the previously stored picture to prevent memory leaks
    if(this->picture)
        delete this->picture;

    this->picture = 0;
    QString text = QString("");
    setText(text);

    BooruPixmapDownloader* d = new BooruPixmapDownloader(QString(""), QString("empty.png"), false);
    QThread* t = new QThread(this);

    d->moveToThread(t);

    //Thread Management
    connect(t, SIGNAL(started()),  d, SLOT(process()));
    connect(d, SIGNAL(finished()), t, SLOT(quit()));
    connect(d, SIGNAL(finished()), d, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    //Output
    connect(d, SIGNAL(pixmapLoaded(QPixmap)), this, SLOT(setPixmap(QPixmap)));

    t->start();
}

void QBooruPicture::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    labelPicture->setPixmap(this->pixmap.scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void QBooruPicture::setText(QString text)
{
    labelComment->setText(text);
}
