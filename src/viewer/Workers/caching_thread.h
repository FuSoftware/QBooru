#ifndef CACHING_THREAD_H_INCLUDED
#define CACHING_THREAD_H_INCLUDED

#include <QObject>
#include <QString>
#include "../fonctions_all.h"

class SearchTab;
class CachingWorker : public QObject
{
    Q_OBJECT
 
public:
    CachingWorker(const char *url, const char *outfilename, bool needs_output);
    CachingWorker();
    ~CachingWorker();

    char* file_name;
    char* file_url;
    bool output_text;
    int connection_state;
 
public slots:
    void process();
 
signals:
    void finished();
    void error(QString err);
 
private:

};

#endif//CACHING_THREAD_H_INCLUDED
