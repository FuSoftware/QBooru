#ifndef QSEARCHWORKER_H
#define QSEARCHWORKER_H

#include <QObject>
#include <QVector>

#include "controller/boorusearchengine.h"

class QSearchWorker : public QObject
{
    Q_OBJECT
public:
    QSearchWorker(BooruSearchEngine* engine, QObject *parent=0);

signals:
    void results(QVector<BooruPicture*>);
    void finished();

public slots:
    void process();

private:
    BooruSearchEngine* engine;
};

#endif // QSEARCHWORKER_H
