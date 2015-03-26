#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHboxLayout>
#include <QScrollArea>

#include "fullscreenImageTabClass.h"
#include <SDL/SDL.h>

FullScreenImageTab::FullScreenImageTab(QWidget *parent, QString imagePath)
{
    image = new QLabel(this);
    scrollAreaTags = new QScrollArea(this);

    QPixmap *imagePixmap = new QPixmap(imagePath);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QSize imageSize = imagePixmap->size();
    image->setPixmap(QPixmap(imagePath).scaled(imageSize,  Qt::KeepAspectRatio, Qt::SmoothTransformation));

    scrollAreaTags->setWidget(image);
    mainLayout->addWidget(scrollAreaTags);
    setLayout(mainLayout);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Fullscreen");

    delete imagePixmap;
}

FullScreenImageTab::~FullScreenImageTab()
{
    SDL_Quit();
}
