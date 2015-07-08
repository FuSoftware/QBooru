#ifndef IMAGETABCLASS_H
#define IMAGETABCLASS_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSignalMapper>
#include <QMovie>

#include "clickableLabel.h"
#include "searchTabClass.h"

#include "../config_file.h"

class SearchTab;

class ImageTab : public QWidget
{
    Q_OBJECT

public:
    ImageTab(SearchTab *parent = 0, int imageHostInt = 3);
    ~ImageTab();
    void loadPicture(QString imagePath, QString comment);
    void resizeEvent(QResizeEvent * event);
    void setLoading();

    /*Objets publics*/
    ClickableLabel *imageThumbnail;
    QMovie *loadingAnimation;

private:
    ConfigFile *conf_file;
    SearchTab *parentWidget;

    QString thumbnailPath;
    QString commentString;

    QVBoxLayout *layout;
    QLabel *imageDescription;

    int imageHost;

};

#endif // IMAGETABCLASS_H
