#include "qboorupictureviewer.h"

#include "qboorupictureinfowidget.h"
#include "model/boorupicture.h"
#include "controller/boorupixmapdownloader.h"

QBooruPictureViewer::QBooruPictureViewer(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

void QBooruPictureViewer::loadUI()
{
    this->info_widget = new QBooruPictureInfoWidget(this);
    this->label_picture = new QLabel(this);

    this->info_widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label_picture);
    layout->addWidget(info_widget);

    this->setLayout(layout);
}

void QBooruPictureViewer::loadPicture(BooruPicture *picture)
{
    this->info_widget->loadPicture(picture);

    BooruPixmapDownloader* d = new BooruPixmapDownloader(picture, PictureType::SAMPLE, true);
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

void QBooruPictureViewer::setPixmap(QPixmap p)
{
    this->label_picture->setPixmap(p);
}
