#include <QApplication>
#include <iostream>

#include "tests.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test_simple_tab();

    return a.exec();
}
