#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include <QFile>
#include <QString>
#include <QDir>
#include <QFileInfo>

using namespace std;

string getFileExtension(string filename);
bool fexists(string filename);
bool fexists(const char *filename);

void createFolder(string file);
void createFolder(QString file);

#endif // FILE_H
