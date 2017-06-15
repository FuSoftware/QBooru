#include "qmaingrid.h"

QMainGrid::QMainGrid(int l, int h, QWidget *parent) : QWidget(parent)
{
    this->l = l;
    this->h = h;
    this->count = l*h;

    //Setting up the main GridLayout
    this->grid = new QGridLayout();


    for(int i=0;i<h;i++)
    {
        for(int j=0;j<l;j++)
        {
            int index = (i*l)+j;
            //Initializes the QBooruPicture
            pictureWidgets.push_back(new QBooruPicture(this));

            //Adds it to the grid
            grid->addWidget(pictureWidgets[index],i,j);
        }
    }

    setLayout(grid);
}

void QMainGrid::loadPictures(vector<BooruPicture*> pictures)
{
    for(int i=0;i<this->count;i++)
    {
        pictureWidgets[i]->setBooruPicture(pictures[i]);
        BooruPixmapDownloader* d = new BooruPixmapDownloader(pictures[i],true);
        QThread* t = new QThread(this);

        //Thread Management
        connect(t, SIGNAL(started()),  d, SLOT(process()));
        connect(d, SIGNAL(finished()), t, SLOT(quit()));
        connect(d, SIGNAL(finished()), d, SLOT(deleteLater()));
        connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

        //Output
        connect(d, SIGNAL(pixmapLoaded(QPixmap)), pictureWidgets[i], SLOT(setPixmap(QPixmap)));

        threadPool.push_back(t);
        workerPool.push_back(d);

        d->moveToThread(t);
        t->start();
    }
}

QBooruPicture* QMainGrid::getWidget(int i)
{
    return pictureWidgets[i];
}

QVector<QBooruPicture*> QMainGrid::getWidgets()
{
    return this->pictureWidgets;
}

void QMainGrid::setPicture(BooruPicture* pic, int i)
{
    pictureWidgets[i]->setBooruPicture(pic);
}

int QMainGrid::getWidgetCount()
{
    return count;
}
