#ifndef QBOORUPICTUREVIEWER_H
#define QBOORUPICTUREVIEWER_H

#include <QtWidgets>
#include "qboorupictureinfowidget.h"
#include "model/boorupicture.h"
#include "controller/boorupixmapdownloader.h"

class QBooruPictureViewer : public QWidget
{
    Q_OBJECT
public:
    QBooruPictureViewer(QWidget *parent = nullptr);
    void loadUI();

signals:

public slots:
    void loadPicture(BooruPicture* picture);
    void setPixmap(QPixmap p);

private:
    QLabel *label_picture = 0;
    QBooruPictureInfoWidget *info_widget = 0;
};

#endif // QBOORUPICTUREVIEWER_H
