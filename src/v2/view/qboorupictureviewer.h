#ifndef QBOORUPICTUREVIEWER_H
#define QBOORUPICTUREVIEWER_H

#include <QtWidgets>

class QBooruPictureInfoWidget;
class BooruPicture;
class BooruPixmapDownloader;

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
