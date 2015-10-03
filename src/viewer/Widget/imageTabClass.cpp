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

    setParent(parent);

    conf_file = parent->getConfigFile();

    imageHost = imageHostInt;
    parentWidget = parent;

    layout = new QVBoxLayout;
    imageThumbnail = new ClickableLabel("Thumbnail");
    imageDescription = new QLabel("Description");

    imageThumbnail->setPixmap(QPixmap(ICON_PATH));
    imageThumbnail->setStyleSheet("qproperty-alignment: AlignCenter;");
    imageThumbnail->setMinimumSize(100,100);

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

    thumbnailPath = imagePath;
    commentString = comment;

    QPixmap pixmap = QPixmap(thumbnailPath);

    QSize imageSize = imageThumbnail->size();
    QSize windowSize = parentWidget->size();

    int width = windowSize.width();
    int height = windowSize.height();

    if(height < 768){height = 768;}
    if(width < 1024){width = 1024;}

    parentWidget->getImageTabsWidget()->updateGeometry();

    imageSize.setWidth(parentWidget->getImageTabsWidget()->width() / conf_file->getPictureColumns());
    imageSize.setHeight((parentWidget->getImageTabsWidget()->height() / conf_file->getPictureRow()) - imageDescription->height()*2);

    //outputInfo(L_DEBUG,"Size : " + intToString(imageSize.width()) + "x" + intToString(imageSize.height()));
    //imageSize.setWidth(125);
    //imageSize.setHeight(125);

    imageThumbnail->setPixmap(pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageDescription->setText(commentString);
}

void ImageTab::resizeEvent(QResizeEvent * event)
{
}
