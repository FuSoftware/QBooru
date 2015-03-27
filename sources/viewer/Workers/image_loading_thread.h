#ifndef IMAGE_LOADING_THREAD_H
#define IMAGE_LOADING_THREAD_H

#include "../Widget/searchTabClass.h"
#include <QString>
#include <QThread>

class SearchTabLoadingWorker : public QObject
{
    Q_OBJECT

public:
    SearchTabLoadingWorker(SearchTab *parent, int image_index);
    ~SearchTabLoadingWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    SearchTab *parent_tab;
    int index;
};

#endif // IMAGE_LOADING_THREAD_H
