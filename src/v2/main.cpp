#include "mainwidget.h"
#include <QApplication>
#include <iostream>

/*Test Headers*/
#include "model/boorusite.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    BooruSite* site = new BooruSite(string("Gelbooru"),string("http://gelbooru.com"), API::GELBOORU);

    cout << "Site " << site->getName() << " has search url " << site->getSearchUrl() << endl;

    return a.exec();
}
