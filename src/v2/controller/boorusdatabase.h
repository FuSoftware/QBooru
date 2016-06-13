#ifndef BOORUSDATABASE_H
#define BOORUSDATABASE_H

#include <QSettings>
#include <QDebug>
#include <vector>

#include "../model/boorusite.h"

#define DB_FILE "boorus.ini"

class BoorusDatabase
{
public:
    BoorusDatabase();
    void addBooru(BooruSite* booru);

    BooruSite* loadFromSettings(QString name);
    BooruSite* loadBooru(int i);
    std::vector<BooruSite*> loadBoorus();

private:
    QSettings *settings;
};

#endif // BOORUSDATABASE_H
