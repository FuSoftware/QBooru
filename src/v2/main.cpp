#include "view/qsearchtab.h"
#include <QApplication>
#include <iostream>

#include "tests.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //test_picture();
    QSearchTab* w = new QSearchTab();
    w->show();

    return a.exec();
}
