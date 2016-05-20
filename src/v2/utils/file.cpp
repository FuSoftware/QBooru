#include "file.h"

string getFileExtension(string filename)
{
    return filename.substr(filename.find_last_of(".") + 1);
}

bool fexists(const char *filename)
{
  ifstream ifile(filename);

#if __linux
  return ifile.is_open();
#else
  return ifile;
#endif
}
