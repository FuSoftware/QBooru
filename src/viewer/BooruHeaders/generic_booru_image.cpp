#include "generic_booru_image.h"

BooruImage::BooruImage()
{

}

BooruImage::BooruImage(int booru_index)
{
    setBooru(booru_index);
}

BooruImage::BooruImage(BooruSite* booru)
{
    setBooru(booru);
}

BooruImage::~BooruImage()
{

}

void BooruImage::setBooru(int booru_index)
{
    booru = new BooruSite(booru_index);
    loadPaths();
}

void BooruImage::setBooru(BooruSite* booru)
{
    this->booru = booru;
    loadPaths();
}

void BooruImage::loadData(int picture_index)
{
    Json::Value root = loadJSONFile(stringToCString(booru->getSearchFilePath().c_str())); // will contains the root value after parsing

    std::string image;
    std::string directory;

    switch(booru->getSiteTypeInt())
    {
    case DERPIBOORU_TYPE:
        id        = root["search"][picture_index]["id_number"].asInt();
        created_at       = root["search"][picture_index]["created_at"].asString();
        author         = root["search"][picture_index]["uploader"].asString();
        score         = root["search"][picture_index]["score"].asInt();
        width  = root["search"][picture_index]["width"].asInt();
        height = root["search"][picture_index]["height"].asInt();
        source              = root["search"][picture_index]["source_url"].asString();
        preview_url   = root["search"][picture_index]["representations"]["thumb_small"].asString().c_str();
        sample_url   = root["search"][picture_index]["representations"]["medium"].asString().c_str();
        full_url   = root["search"][picture_index]["representations"]["full"].asString().c_str();
        break;
    case GELBOORU_TYPE:
        image = root[picture_index]["image"].asString();
        directory = root[picture_index]["directory"].asString();
        id               = root[picture_index]["id"].asInt();
        created_at       = returnTimeStringConvert(root[picture_index]["change"].asInt());
        author           = root[picture_index]["owner"].asString();
        score            = root[picture_index]["score"].asInt();
        file_size        = 0;
        full_url    =  booru->getBaseUrl() + std::string("/images/") + directory +std::string("/") + image;
        width       =  root[picture_index]["width"].asInt();
        height      =  root[picture_index]["height"].asInt();
        preview_url = booru->getBaseUrl() + std::string("/thumbnails/") + directory +std::string("/thumbnail_") + image.substr(0,image.find_last_of('.')) + std::string(".jpg"); //http://gelbooru.com/thumbnails/16/b2/thumbnail_16b2851ba391157b418d9d6cb2a3b602.jpg
        if(root[picture_index]["sample"].asBool())
        {
            sample_url = booru->getBaseUrl() + std::string("/samples/") + directory +std::string("/sample_") + image.substr(0,image.find_last_of('.')) + std::string(".jpg");//http://simg3.gelbooru.com/samples/16/24/sample_1624d72ba640bb22adb6820dbac88f01.jpg
        }
        else
        {
            sample_url = booru->getBaseUrl() + std::string("/images/") + directory +std::string("/") + image;//http://simg3.gelbooru.com/images/16/b2/16b2851ba391157b418d9d6cb2a3b602.jpg
        }
        rating   = *strdup(root[picture_index]["rating"].asString().c_str());
        tagNumber = loadTags(root[picture_index]["tags"].asString(), tags);
        break;
    case MOEBOORU_TYPE:
        id               = root["posts"][picture_index]["id"].asInt();
        created_at       = returnTimeStringConvert(returnPostAgeSec(root["posts"][picture_index]["created_at"].asInt()));
        author           = strdup(root["posts"][picture_index]["author"].asString().c_str());
        source           = strdup(root["posts"][picture_index]["source"].asString().c_str());
        score            = root["posts"][picture_index]["score"].asInt();
        file_size        = root["posts"][picture_index]["file_size"].asInt();
        full_url    = root["posts"][picture_index]["file_url"].asString();//File url
        width       = root["posts"][picture_index]["width"].asInt();
        height      = root["posts"][picture_index]["height"].asInt();
        preview_url             = root["posts"][picture_index]["preview_url"].asString();
        preview_height          = root["posts"][picture_index]["preview_height"].asInt();
        preview_width           = root["posts"][picture_index]["preview_width"].asInt();
        actual_preview_height   = root["posts"][picture_index]["actual_preview_height"].asInt();
        actual_preview_width    = root["posts"][picture_index]["actual_preview_width"].asInt();
        sample_url          = root["posts"][picture_index]["sample_url"].asString();
        sample_height       = root["posts"][picture_index]["sample_height"].asInt();
        sample_width        = root["posts"][picture_index]["sample_width"].asInt();
        sample_file_size    = root["posts"][picture_index]["sample_file_size"].asInt();
        //full_url          = root["posts"][picture_index]["jpeg_url"].asString();
        //full_height       = root["posts"][picture_index]["jpeg_height"].asInt();
        //full_width        = root["posts"][picture_index]["jpeg_width"].asInt();
        //full_file_size    = root["posts"][picture_index]["jpeg_file_size"].asInt();
        rating   = *strdup(root["posts"][picture_index]["rating"].asString().c_str());
        tagNumber = loadTags(root["posts"][picture_index]["tags"].asString(), tags);
        break;
    case DANBOORU2_TYPE:
        id               = root[picture_index]["id"].asInt();//Ok
        created_at       = root[picture_index]["created_at"].asString();//Ok
        author           = root[picture_index]["uploader_name"].asString(); //Ok
        source           = root[picture_index]["source"].asString();//Ok
        score            = root[picture_index]["score"].asInt();//Ok
        file_size        = root[picture_index]["file_size"].asInt();//Ok
        full_url    = booru->getBaseUrl() + root[ picture_index]["file_url"].asString();//Ok
        width       = root[picture_index]["image_width"].asInt(); //Ok
        height      = root[picture_index]["image_height"].asInt();// Ok
        preview_url = booru->getBaseUrl() + root[ picture_index]["preview_file_url"].asString(); //Ok
        sample_url = booru->getBaseUrl() + root[ picture_index]["large_file_url"].asString(); //Ok
        rating = *strdup(root[ picture_index]["rating"].asString().c_str()); //Ok
        tagNumber = loadTags(root[picture_index]["tag_string"].asString(), tags); //Ok
        break;
    }

    loadPaths();
}

void BooruImage::loadPaths()
{
    std::string fileName;
    std::string format;

    /*Thumb path*/
    fileName = preview_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    thumb_path = booru->getCachePath() + intToString(id) + "." + format;

    /*Medium Path*/
    fileName = sample_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    medium_path = booru->getCachePath() + intToString(id)+ "." + "_medium" + format;

    /*Full path*/
    fileName = full_url;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    full_path = booru->getDownloadPath() + intToString(id) + "_full." + format;
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

BooruSite* BooruImage::getBooru()
{
    return booru;
}
