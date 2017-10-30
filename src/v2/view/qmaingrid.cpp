#include "qmaingrid.h"

#include "qboorupicture.h"
#include "model/boorupicture.h"
#include "controller/boorupixmapdownloader.h"

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
            connect(pictureWidgets[i], SIGNAL(pictureClicked(BooruPicture*)), this, SIGNAL(pictureClicked(BooruPicture*)));

            //Adds it to the grid
            grid->addWidget(pictureWidgets[index],i,j);
        }
    }

    setLayout(grid);
}

void QMainGrid::loadPictures(std::vector<BooruPicture*> pictures)
{
    loadPictures(QVector<BooruPicture*>::fromStdVector(pictures));
}

void QMainGrid::loadPictures(QVector<BooruPicture*> pictures)
{
    qDebug() << "Loading pictures";
    for(int i=0;i<pictures.size();i++)
    {
        pictureWidgets[i]->setBooruPicture(pictures[i]);
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
