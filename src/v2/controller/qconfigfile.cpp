#include "qconfigfile.h"

QConfigFile::QConfigFile(QObject *parent) : QObject(parent)
{
    settings = new QSettings(QString(CONFIG_FILE),QSettings::IniFormat);

    if(!fexists(CONFIG_FILE))
    {
        initialize();
    }

    load();

}

void QConfigFile::initialize()
{
    /* Display*/
    window_h = 768;
    window_w = 1024;
    pictures_x = 5;
    pictures_y = 3;
}

void QConfigFile::load()
{
    window_h = settings->value("Display/windiw_h").toInt();
    window_w = settings->value("Display/window_w").toInt();
    pictures_x = settings->value("Display/pictures_x").toInt();
    pictures_y = settings->value("Display.pictures_y").toInt();
}

void QConfigFile::save()
{
    /* Display*/
    settings->beginGroup("Display");
    settings->setValue("window_h",window_h);
    settings->setValue("window_w",window_w);
    settings->setValue("pictures_x",pictures_x);
    settings->setValue("pictures_y",pictures_y);
    settings->endGroup();
}

int QConfigFile::getPicturesX()
{
    return this->pictures_x;
}

int QConfigFile::getPicturesY()
{
    return this->pictures_y;
}

int QConfigFile::getWindowH()
{
    return this->window_h;
}

int QConfigFile::getWindowW()
{
    return this->window_w;
}
