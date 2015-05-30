#include "viewer_loading_thread.h"

// --- CONSTRUCTOR ---
ViewerTabLoadingWorker::ViewerTabLoadingWorker(ViewerTab *parent)
{
    parent_tab = parent;
}

// --- DECONSTRUCTOR ---
ViewerTabLoadingWorker::~ViewerTabLoadingWorker()
{
    // free resources
}

// --- PROCESS ---
void ViewerTabLoadingWorker::process()
{
    parent_tab->setLoadingState(true);

    parent_tab->Image.download_medium();
    parent_tab->imageViewer = QString(parent_tab->Image.getMediumPath().c_str());
    parent_tab->labelImage->setPixmap(QPixmap(parent_tab->imageViewer).scaled(parent_tab->thumbZoneSize,  Qt::KeepAspectRatio, Qt::SmoothTransformation));

    parent_tab->setLoadingState(false);
    emit finished();
}


