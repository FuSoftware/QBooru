#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include <QFile>
#include <QString>
#include <QDir>
#include <QFileInfo>

std::string getFileExtension(std::string filename);
bool fexists(std::string filename);
bool fexists(const char *filename);

void createFolder(std::string file);
void createFolder(QString file);

#endif // FILE_H
