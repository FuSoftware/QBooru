#include "caching_thread.h"

// --- CONSTRUCTOR ---
CachingWorker::CachingWorker(char url[4096], char outfilename[4096], bool needs_output)
{
    file_url = url;
    output_text = needs_output;
    strncpy(file_url, url, 4096);
    strncpy(file_name, outfilename, 4096);
}

CachingWorker::CachingWorker()
{

}
 
// --- DECONSTRUCTOR ---
CachingWorker::~CachingWorker()
{
    // free resources
}
 
// --- PROCESS ---
void CachingWorker::process()
{
    connection_state = cachingFile(file_url,file_name,output_text, true);
    emit finished();
}
