#ifndef FONCTIONS_QT_H
#define FONCTIONS_QT_H

#include <iostream>
#include "../constantes.h"
#include "fonctions.h"

#include <QString>
#include <QDir>

#include <QLayout>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>
#include <QThread>

void checkFolder(std::string path);
void runUpdaterFunction();

void criticalCURLError(QWidget *parent, int error);
void criticalProgramError(QWidget *parent, int error);
void clearLayout(QLayout *layout);
void clearLayoutSecond(QLayout *layout);
QString readChangelog();

#endif
