#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include <QFileInfo>
#include<QDir>

using namespace std;

void checkFileFolder(QString path);
void checkFileFolder(string path);

string getFileExtension(string filename);
bool fexists(const char *filename);

#endif // FILE_H
