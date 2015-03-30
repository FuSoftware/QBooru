#ifndef VIEWER_LOADING_THREAD_H
#define VIEWER_LOADING_THREAD_H

#include "../Widget/viewerTabClass.h"
#include <QString>
#include <QThread>

class ViewerTab;

class ViewerTabLoadingWorker : public QObject
{
    Q_OBJECT

public:
    ViewerTabLoadingWorker(ViewerTab *parent);
    ~ViewerTabLoadingWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    ViewerTab *parent_tab;
};

#endif // VIEWER_LOADING_THREAD_H
