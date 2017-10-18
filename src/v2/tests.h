#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <vector>

#include <QVector>

#include "model/boorusite.h"
#include "controller/boorusearchengine.h"
#include "controller/boorusdatabase.h"

#include "view/qboorupicture.h"
#include "view/qmaingrid.h"
#include "view/qsearchwidget.h"

using namespace std;

void test_search();
void test_site();
void test_database();
void test_picture();
void test_maingrid();
void test_simple_tab();

#endif // TESTS_H
