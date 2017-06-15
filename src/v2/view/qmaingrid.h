#ifndef QMAINGRID_H
#define QMAINGRID_H

#include <QtWidgets>
#include "qboorupicture.h"
#include "model/boorupicture.h"
#include "controller/boorupixmapdownloader.h"
#include <QThread>

class QMainGrid : public QWidget
{
    Q_OBJECT
public:
    QMainGrid(int l, int h, QWidget *parent = nullptr);

    void loadPictures(vector<BooruPicture *> pictures);
    QBooruPicture* getWidget(int i);
    QVector<QBooruPicture*> getWidgets();

    void setPicture(BooruPicture* pic, int i);
    int getWidgetCount();

signals:

public slots:

private:
    int l;
    int h;
    int count;

    QGridLayout *grid;
    QVector<QBooruPicture*> pictureWidgets;
    QVector<QThread*> threadPool;
    QVector<BooruPixmapDownloader*> workerPool;
};

#endif // QMAINGRID_H
