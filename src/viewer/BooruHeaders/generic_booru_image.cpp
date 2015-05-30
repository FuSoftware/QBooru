#include "generic_booru_image.h"

BooruImage::BooruImage()
{

}

BooruImage::BooruImage(int booru_index)
{
    setBooru(booru_index);
}

BooruImage::BooruImage(BooruSite booru)
{
    setBooru(booru);
}

BooruImage::~BooruImage()
{

}

void BooruImage::setBooru(int booru_index)
{
    booru = BooruSite(booru_index);
    loadPaths();
}

void BooruImage::setBooru(BooruSite booru)
{
    this->booru = booru;
    loadPaths();
}

void BooruImage::loadPaths()
{
    std::string fileName;
    std::string format;

    /*Thumb path*/
    fileName = preview_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    thumb_path = booru.getCachePath() + intToString(id) + "." + format;

    /*Medium Path*/
    fileName = sample_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);

    medium_path = booru.getCachePath() + intToString(id)+ "." + "_medium" + format;

    /*Full path*/
    fileName = full_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    full_path = booru.getDownloadPath() + intToString(id) + "_full." + format;
}

void BooruImage::download_thumb()
{
    cachingFile(stringToCString(preview_url),stringToCString(thumb_path),false,true);
}

void BooruImage::download_medium()
{
    cachingFile(stringToCString(sample_url),stringToCString(medium_path),true,false);
}

void BooruImage::download_full()
{
    cachingFile(stringToCString(full_url),stringToCString(full_path),true,false);
}

std::string BooruImage::getThumbPath()
{
    return thumb_path;
}

std::string BooruImage::getMediumPath()
{
    return medium_path;
}

std::string BooruImage::getFullPath()
{
    return full_path;
}

BooruSite BooruImage::getBooru()
{
    return booru;
}
