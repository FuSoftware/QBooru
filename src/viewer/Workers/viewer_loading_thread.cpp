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
    outputInfo("DEBUG","Viewer Thread Started",LEVEL_TOP_WIDGET);

    parent_tab->imageViewer = cacheImageMediumGeneric(parent_tab->Image,parent_tab->booru.cache_path,false);

    parent_tab->labelImage->setPixmap(QPixmap(parent_tab->imageViewer).scaled(parent_tab->thumbZoneSize,  Qt::KeepAspectRatio, Qt::SmoothTransformation));

    emit finished();
}


