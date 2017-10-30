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
    qDebug() << "Clicked picture " << QString::number(this->picture->getID()) << " from booru " << QString::fromStdString(this->picture->getWebsite()->getName());
    emit pictureClicked(this->picture);
}

void QBooruPicture::setBooruPicture(BooruPicture* picture)
{
    this->picture = picture;

    QString text = QString::number(picture->getW()) + QString("x") + QString::number(picture->getH());
    setText(text);

    BooruPixmapDownloader* d = new BooruPixmapDownloader(picture, PictureType::PREVIEW, true);
    QThread* t = new QThread(this);

    //Thread Management
    connect(t, SIGNAL(started()),  d, SLOT(process()));
    connect(d, SIGNAL(finished()), t, SLOT(quit()));
    connect(d, SIGNAL(finished()), d, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    //Output
    connect(d, SIGNAL(pixmapLoaded(QPixmap)), this, SLOT(setPixmap(QPixmap)));

    d->moveToThread(t);
    t->start();
}

void QBooruPicture::setPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    labelPicture->setPixmap(this->pixmap.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void QBooruPicture::setText(QString text)
{
    labelComment->setText(text);
}
