#include <QApplication>
#include <iostream>

#include "tests.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test_sample_boorus();

    return a.exec();
}
