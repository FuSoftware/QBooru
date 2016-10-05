#include <QApplication>
#include <iostream>

#include "view/qsearchtab.h"
#include "model/boorusite.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //test_picture();
    QSearchTab* w = new QSearchTab(new BooruSite("Konachan","http://konachan.com",API::MOEBOORU));
    w->show();

    return a.exec();
}
