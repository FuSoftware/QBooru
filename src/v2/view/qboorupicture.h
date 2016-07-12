#ifndef QBOORUPICTURE_H
#define QBOORUPICTURE_H

#include "model/boorupicture.h"

#include <QtWidgets>

class QBooruPicture : public QWidget
{
    Q_OBJECT
public:
    QBooruPicture(QWidget *parent = 0);
    QBooruPicture(BooruPicture *picture, QWidget* parent=0);

    void loadUI();

    void setBooruPicture(BooruPicture* picture);
    void setPixmap(QPixmap* pixmap);
    void setText(QString text);

signals:

public slots:

private:
    BooruPicture* picture;
    QPixmap *pixmap;

    QLabel *labelPicture;
    QLabel *labelComment;
};

#endif // QBOORUPICTURE_H
