#ifndef QMAINGRID_H
#define QMAINGRID_H

#include <QtWidgets>
#include <QThread>

class BooruPixmapDownloader;
class BooruPicture;
class QBooruPicture;

class QMainGrid : public QWidget
{
    Q_OBJECT
public:
    QMainGrid(int l, int h, QWidget *parent = nullptr);

    QBooruPicture* getWidget(int i);
    QVector<QBooruPicture*> getWidgets();

    void setPicture(BooruPicture* pic, int i);
    int getWidgetCount();

signals:
    void pictureClicked(BooruPicture *picture);

public slots:
    void loadPictures(std::vector<BooruPicture *> pictures);
    void loadPictures(QVector<BooruPicture *> pictures);

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
