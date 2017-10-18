#include "file.h"

string getFileExtension(string filename)
{
    return filename.substr(filename.find_last_of(".") + 1);
}

bool fexists(string filename)
{
    return fexists(filename.c_str());
}

bool fexists(const char *filename)
{
    ifstream ifile(filename);
    return ifile.is_open();
}

void createFolder(string file)
{
    createFolder((QString(file.c_str())));
}

void createFolder(QString file)
{
    QFileInfo f(file);

    if(!QDir(f.absoluteDir()).exists())
        QDir().mkdir(f.absoluteDir().absolutePath());
}
