#include "mainwidget.h"
#include <QApplication>
#include <iostream>

#include "tests.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test_maingrid();

    return a.exec();
}
