#ifndef QBOORUPICTURE_H
#define QBOORUPICTURE_H

#include "model/boorupicture.h"
#include "controller/connectionmanager.h"
#include "workers/qdownloadworker.h"

#include <QtWidgets>
#include <QDebug>

class QBooruPicture : public QWidget
{
    Q_OBJECT
public:
    QBooruPicture(QWidget *parent = 0);
    QBooruPicture(BooruPicture *picture, QWidget* parent=0);

    void loadUI();

    void loadBooruPicture(BooruPicture* picture);
    void setBooruPicture(BooruPicture* picture);
    void setPixmap(QPixmap pixmap);
    void setText(QString text);

signals:

public slots:
    void loadPixmap(QString file);

private:
    BooruPicture* picture;
    QPixmap pixmap;

    QLabel *labelPicture;
    QLabel *labelComment;

    QThread* thread;
    QDownloadWorker* worker;
};

#endif // QBOORUPICTURE_H
