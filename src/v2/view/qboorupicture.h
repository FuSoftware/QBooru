#ifndef QBOORUPICTURE_H
#define QBOORUPICTURE_H

#include <QtWidgets>
#include <QDebug>
#include "clickablelabel.h"

class BooruPicture;

class QBooruPicture : public QWidget
{
    Q_OBJECT
public:
    QBooruPicture(QWidget *parent = 0);
    QBooruPicture(BooruPicture *picture, QWidget* parent=0);

    void loadUI();

signals:
    void pictureClicked(BooruPicture* picture);

public slots:
    void setBooruPicture(BooruPicture* picture);
    void setPixmap(QPixmap pixmap);
    void setText(QString text);
    void onPictureClicked();

private:
    BooruPicture* picture;
    QPixmap pixmap;

    ClickableLabel *labelPicture;
    QLabel *labelComment;
};

#endif // QBOORUPICTURE_H
