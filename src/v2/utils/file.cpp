#include "file.h"

void checkFileFolder(QString path)
{
    QFileInfo file(path);
    if (!file.absoluteDir().exists()) {
        file.absoluteDir().mkpath(".");
    }
}

void checkFileFolder(string path){
    return checkFileFolder(QString(path.c_str()));
}

string getFileExtension(string filename)
{
    return filename.substr(filename.find_last_of(".") + 1);
}

bool fexists(const char *filename)
{
    ifstream ifile(filename);
    return ifile.is_open();
}
