#include "imageTabClass.h"
#include "constantes.h"
#include "fonctions_all.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMovie>

ImageTab::ImageTab(SearchTab *parent, int imageHostInt) : QWidget(parent)
{
    conf_file = parent->getConfigFile();

    setParent(parent);
    int image_width =  parent->width() / conf_file->getPictureColumns();
    int image_height = parent->height() / conf_file->getPictureRow();


    imageHost = imageHostInt;
    parentWidget = parent;

    layout = new QVBoxLayout;
    imageThumbnail = new ClickableLabel("Thumbnail");
    imageDescription = new QLabel("Description");

    imageThumbnail->setPixmap(QPixmap(ICON_PATH));
    imageThumbnail->setStyleSheet("qproperty-alignment: AlignCenter;");
    imageThumbnail->setMinimumSize(image_width,image_height);

    imageDescription->setStyleSheet("qproperty-alignment: AlignCenter;");
    imageDescription->setMaximumSize(imageDescription->maximumWidth(),21);


    imageThumbnail->setAlignment(Qt::AlignCenter);
    imageDescription->setAlignment(Qt::AlignCenter);

    layout->addWidget(imageThumbnail);
    layout->addWidget(imageDescription);
    layout->setSizeConstraint(layout->SetNoConstraint);

    thumbnailPath = QString(ICON_PATH);

    setLayout(layout);
}

ImageTab::~ImageTab()
{
    //clearLayoutSecond(layout);
}

void ImageTab::loadPicture(QString imagePath, QString comment)
{
    this->updateGeometry();

    int espacement_h = 3;
    int espacement_w = 3;
    thumbnailPath = imagePath;
    commentString = comment;

    QPixmap pixmap = QPixmap(thumbnailPath);

    QSize imageSize = imageThumbnail->size();
    QSize windowSize = parentWidget->size();

    int width = windowSize.width();
    int height = windowSize.height();

    if(height < 768){height = 768;}
    if(width < 1024){width = 1024;}

    imageSize.setWidth(parentWidget->width() / conf_file->getPictureColumns());
    imageSize.setHeight(parentWidget->height() / conf_file->getPictureRow());

    imageThumbnail->setPixmap(pixmap.scaled(this->height()-imageDescription->minimumHeight(),this->width(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageDescription->setText(commentString);

    this->updateGeometry();
    imageThumbnail->setPixmap(pixmap.scaled(this->height()-imageDescription->minimumHeight(),this->width(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTab::resizeEvent(QResizeEvent * event)
{
}
