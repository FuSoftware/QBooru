/*
 * fileutils.h
 *
 * Allows simple management of folders by giving tools to :
 * - Delete folder and subfolders
 * - Get a folder's size
 */

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>

class FileUtils
{
public:
    static bool removeDir(const QString &dirName);
};

quint64 dir_size(const QString &str);

#endif // FILEUTILS_H
