#include "image_loading_thread.h"

// --- CONSTRUCTOR ---
SearchTabLoadingWorker::SearchTabLoadingWorker(SearchTab *parent, int image_index)
{
    parent_tab = parent;
    index = image_index;
}

// --- DECONSTRUCTOR ---
SearchTabLoadingWorker::~SearchTabLoadingWorker()
{
    // free resources
}

// --- PROCESS ---
void SearchTabLoadingWorker::process()
{
    QString pathFile;
    QString uploader;

    parent_tab->thread_pool[index] = new QThread(this);

    int connectionState[MAX_PICTURE_NUMBER];

    pathFile = cacheImageGeneric(parent_tab->images[index], parent_tab->booru.cache_path, parent_tab, index);
    uploader = QString::number(parent_tab->images[index].width) + QString("x") + QString::number(parent_tab->images[index].height);

    parent_tab->imageTabs[index]->loadPicture(pathFile, uploader);

    emit finished();
}

