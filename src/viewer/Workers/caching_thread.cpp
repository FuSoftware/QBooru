#include "caching_thread.h"

// --- CONSTRUCTOR ---
CachingWorker::CachingWorker(const char* url, const char* outfilename, bool needs_output)
{
    //file_url = url;
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
    downloadFile(file_url,file_name,false,output_text,false);
    emit finished();
}
