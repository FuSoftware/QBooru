#ifndef QSEARCHWIDGET_H
#define QSEARCHWIDGET_H

#include <QtWidgets>
#include "controller/qsearchworker.h"
#include "model/boorusite.h"
#include "model/boorupicture.h"

class QSearchWidget : public QWidget
{
    Q_OBJECT
public:
    QSearchWidget(BooruSite* site, int limit = 15, QWidget *parent = nullptr);
signals:
    void loadedPictures(QVector<BooruPicture*> pics);

public slots:
    void search();

private:
    void loadUI();

    int limit = 15;

    QLineEdit *lineEditTags;
    QPushButton *pushButtonSearch;

    BooruSite *site;
    BooruSearchEngine *engine;
    QSearchWorker *worker;
};

#endif // QSEARCHWIDGET_H
