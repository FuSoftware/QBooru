#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

using namespace std;

string getFileExtension(string filename);
bool fexists(const char *filename);

#endif // FILE_H
