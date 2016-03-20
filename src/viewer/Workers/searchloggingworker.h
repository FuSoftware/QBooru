#ifndef SEARCHLOGGINGWORKER_H
#define SEARCHLOGGINGWORKER_H

#include <QObject>
#include <QTimer>
#include "../fonctions_all.h"
#include "../Workers/cookiejar.h"

class SearchLoggingWorker : public QObject
{
    Q_OBJECT    
public:
    SearchLoggingWorker(string tags, int rating, int page, BooruSite* booru);
    SearchLoggingWorker();
    ~SearchLoggingWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    string tags;
    int rating;
    int page;
    BooruSite* booru;
};

#endif // SEARCHLOGGINGWORKER_H
