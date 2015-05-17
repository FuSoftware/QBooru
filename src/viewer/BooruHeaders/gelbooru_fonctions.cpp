#include <iostream>
#include <string>
#include <sstream>
#include "widget.h"

#include <QString>
#include <QDir>
#include <QNetworkAccessManager>

#include "json/json.h"

#include "fonctions_all.h"
#include "gelbooru_fonctions.h"
#include "generic_booru_image.h"

void chargementImagesGelbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath, std::string baseSiteIndex)
{
    int i;
    Json::Value root = loadJSONFile(stringToCString(searchFilePath)); // will contains the root value after parsing
    Json::Value root_config = loadJSONFile(CONF_FILE); // will contains the root config value after parsing
    int picture_number = root_config["settings"]["picture_number"].asInt();

    std::string image;
    std::string directory;

    for(i=0;i<picture_number;i++)
    {
        image = root[i]["image"].asString();
        directory = root[i]["directory"].asString();

        imagesAffichage[i].id               = root[i]["id"].asInt();
        imagesAffichage[i].created_at       = returnTimeStringConvert(root[i]["change"].asInt());
        imagesAffichage[i].author           = root[i]["owner"].asString();
        imagesAffichage[i].score            = root[i]["score"].asInt();
        imagesAffichage[i].file_size        = 0;

        imagesAffichage[i].file_url    =  baseSiteIndex + std::string("/images/") + directory +std::string("/") + image;
        imagesAffichage[i].width       =  root[i]["width"].asInt();
        imagesAffichage[i].height      =  root[i]["height"].asInt();

        /*Search tab*/
        imagesAffichage[i].preview_url = baseSiteIndex + std::string("/thumbnails/") + directory +std::string("/thumbnail_") + image.substr(0,image.find_last_of('.')) + std::string(".jpg"); //http://gelbooru.com/thumbnails/16/b2/thumbnail_16b2851ba391157b418d9d6cb2a3b602.jpg

        if(root[i]["sample"].asBool())
        {
            imagesAffichage[i].sample_url = baseSiteIndex + std::string("/samples/") + directory +std::string("/sample_") + image.substr(0,image.find_last_of('.')) + std::string(".jpg");//http://simg3.gelbooru.com/samples/16/24/sample_1624d72ba640bb22adb6820dbac88f01.jpg
        }
        else
        {
            imagesAffichage[i].sample_url = baseSiteIndex + std::string("/images/") + directory +std::string("/") + image;//http://simg3.gelbooru.com/images/16/b2/16b2851ba391157b418d9d6cb2a3b602.jpg
        }

        imagesAffichage[i].rating   = *strdup(root[i]["rating"].asString().c_str());
        imagesAffichage[i].tagNumber = loadTags(root[i]["tags"].asString(), imagesAffichage[i].tags);
    }
}

int returnTagNumberGelbooru(Json::Value root)
{
    int tagIndex = 0;
    while(root[tagIndex]["id"] == Json::intValue)
    {
        tagIndex++;
    }
    return tagIndex;
}

int lectureTagsGelbooru(std::string input, std::string output[][3], Json::Value root)
{
    int tagIndex = 0;
    int j = 0;

    /*Indicateurs des colonnes*/

    output[j][0] = "Tag Name";
    output[j][1] = "Tag ID";
    output[j][2] = "Tag Count";
    j++;

    /*Lecture des tags*/
    while(root[tagIndex]["id"] == Json::intValue)
    {
        if(strncmp(root[tagIndex]["name"].asCString(), input.c_str(), input.size()) == 0)
        {
            output[j][0] = root[tagIndex]["name"].asString();
            output[j][1] = root[tagIndex]["id"].asString();
            output[j][2] = root[tagIndex]["count"].asString();
            j++;
        }
        else
        {

        }
        tagIndex++;
    }
    return j;
}
