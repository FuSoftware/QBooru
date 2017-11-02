#ifndef QCONFIGFILE_H
#define QCONFIGFILE_H

#define CONFIG_FILE "config.ini"

#include <QObject>
#include <QString>
#include <QList>
#include <QSettings>

#include "utils/file.h"

class QConfigFile : public QObject
{
    Q_OBJECT
public:
    QConfigFile(QObject *parent = 0);
    void initialize();

    void load();
    void save();

    int getPicturesX();
    int getPicturesY();
    int getWindowH();
    int getWindowW();


signals:

public slots:

private:
    QSettings *settings;
    int window_h;
    int window_w;

    int pictures_x;
    int pictures_y;

};

#endif // QCONFIGFILE_H
