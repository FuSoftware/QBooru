#ifndef QSEARCHWIDGET_H
#define QSEARCHWIDGET_H

#include <QtWidgets>
#include "controller/qsearchworker.h"
#include "model/boorusite.h"
#include "model/boorupicture.h"

#define DEFAULT_LIMIT 15

class QSearchWidget : public QWidget
{
    Q_OBJECT
public:
    QSearchWidget(BooruSite* site, int limit = DEFAULT_LIMIT, QWidget *parent = nullptr);
signals:
    void loadedPictures(QVector<BooruPicture*> pics);
    void pageSet(int page);

public slots:
    void setPage(int page);
    void search();

private:
    void search(int page);
    void search(QString tags, int page, int limit);
    void loadUI();

    QLineEdit *lineEditTags;
    QPushButton *pushButtonSearch;

    BooruSite *site;
    BooruSearchEngine *engine;
    QSearchWorker *worker;

    QString tags = "";
    int page = 0;
    int limit = DEFAULT_LIMIT;
};

#endif // QSEARCHWIDGET_H
