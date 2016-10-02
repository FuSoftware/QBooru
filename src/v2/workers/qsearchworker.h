#ifndef QSEARCHWORKER_H
#define QSEARCHWORKER_H

#include <QObject>

class QSearchWorker : public QObject
{
    Q_OBJECT
public:
    explicit QSearchWorker(QObject *parent = 0);

signals:

public slots:
};

#endif // QSEARCHWORKER_H