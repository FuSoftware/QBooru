#include "file.h"

std::string getFileExtension(std::string filename)
{
    return filename.substr(filename.find_last_of(".") + 1);
}

bool fexists(std::string filename)
{
    return fexists(filename.c_str());
}

bool fexists(const char *filename)
{
    std::ifstream ifile(filename);
    return ifile.is_open();
}

void createFolder(std::string file)
{
    createFolder((QString::fromStdString(file)));
}

void createFolder(QString file)
{
    QFileInfo f(file);

    if(!QDir(f.absoluteDir()).exists())
        QDir().mkdir(f.absoluteDir().absolutePath());
}
