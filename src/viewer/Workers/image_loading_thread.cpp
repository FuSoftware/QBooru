#include "image_loading_thread.h"

// --- CONSTRUCTOR ---
SearchTabLoadingWorker::SearchTabLoadingWorker()
{
    parent_tab = 0;
    index = 0;
}

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
void SearchTabLoadingWorker::setPicture(SearchTab *parent, int image_index)
{
    parent_tab = parent;
    index = image_index;
}

void SearchTabLoadingWorker::process()
{
    QString pathFile;
    QString uploader;

    parent_tab->setLoadingState(index, true);
    parent_tab->thread_pool[index] = new QThread(this);

    parent_tab->images[index].download_thumb();
    uploader = QString::number(parent_tab->images[index].width) + QString("x") + QString::number(parent_tab->images[index].height);

    parent_tab->imageTabs[index]->loadPicture(QString(parent_tab->images[index].getThumbPath().c_str()), uploader);

    parent_tab->setLoadingState(index, false);

    emit finished(index);
    emit finished();
}

