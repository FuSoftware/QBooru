#include "mainwidget.h"
#include <QApplication>
#include <iostream>

#include "tests.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    test_database();

    return a.exec();
}
