#include "downloadworker.h"

// --- CONSTRUCTOR ---
ImageDownloadWorker::ImageDownloadWorker(BooruImage *image)
{
    this->image = image;
}

ImageDownloadWorker::ImageDownloadWorker()
{

}

// --- DECONSTRUCTOR ---
ImageDownloadWorker::~ImageDownloadWorker()
{
    // free resources
}

// --- PROCESS ---
void ImageDownloadWorker::process()
{
    image->download_full();
    emit finished();
}

