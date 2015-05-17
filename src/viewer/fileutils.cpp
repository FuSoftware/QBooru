#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <iostream>

#include "fileutils.h"
#include "fonctions_all.h"
#include "constantes.h"

/*!
   Delete a directory along with all of its contents.

   \param dirName Path of directory to remove.
   \return true on success; false on error.
*/
bool FileUtils::removeDir(const QString &dirName)
{

    bool result = true;
    QDir dir(dirName);
    QString absoluteDirName;
    absoluteDirName = dir.absolutePath();
    outputInfo("INFO",
               std::string("Removing : ") + dir.absolutePath().toStdString(),
               LEVEL_TOP_WIDGET);

    QDir dir2(absoluteDirName);

    if (dir2.exists(absoluteDirName)) {
        Q_FOREACH(QFileInfo info, dir2.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.filePath());
            }
            else {
                result = QFile::remove(info.filePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir2.rmdir(absoluteDirName);
    }

    return result;
}

quint64 dir_size(const QString &str)
{
    quint64 sizex = 0;
    QFileInfo str_info(str);
    if (str_info.isDir())
    {
        QDir dir(str);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            if(fileInfo.isDir())
            {
                    sizex += dir_size(fileInfo.absoluteFilePath());
            }
            else
                sizex += fileInfo.size();
        }
    }
    return sizex;
}

