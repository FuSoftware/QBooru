#ifndef QSEARCHTAB_H
#define QSEARCHTAB_H

#include <QtWidgets>

#include <QList>

#include "controller/boorusearchengine.h"
#include "model/boorusite.h"
#include "view/qboorupicture.h"

class QSearchTab : public QWidget
{
    Q_OBJECT
public:
    QSearchTab(QWidget *parent = 0);
    QSearchTab(BooruSite* site, QWidget *parent = 0);
    void loadUI();
    void setupBooru(BooruSite* booru);

signals:

public slots:
    void search();

private:
    BooruSite* booru;
    BooruSearchEngine* engine;

    QLineEdit* lineEditSearch;
    QLineEdit* lineEditPageNumber;

    QList<QBooruPicture*> pictureWidgets;
    std::vector<BooruPicture*> pictures;
};

#endif // QSEARCHTAB_H
