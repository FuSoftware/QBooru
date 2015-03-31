#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include "widget.h"

#include <QString>
#include <QDir>

#include "../json/json.h"

#include "constantes.h"
#include "fonctions.h"
#include "danbooru_fonctions.h"
#include "generic_booru_image.h"

void chargementImagesDanbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath, std::string baseSiteIndex)
{
    int i;
    outputInfo("DEBUG",searchFilePath,LEVEL_TOP_WIDGET);
    Json::Value root = loadJSONFile(stringToCString(searchFilePath)); // will contains the root value after parsing
    Json::Value root_config = loadJSONFile(CONF_FILE); // will contains the root config value after parsing

    for(i=0;i<root_config["settings"]["picture_number"].asInt();i++)
    {
        imagesAffichage[i].id               = root[i]["id"].asInt();//Ok
        imagesAffichage[i].created_at       = root[i]["created_at"].asString();//Ok
        imagesAffichage[i].author           = root[i]["uploader_name"].asString(); //Ok
        imagesAffichage[i].source           = root[i]["source"].asString();//Ok
        imagesAffichage[i].score            = root[i]["score"].asInt();//Ok
        imagesAffichage[i].file_size        = root[i]["file_size"].asInt();//Ok

        imagesAffichage[i].file_url    = baseSiteIndex + root[i]["file_url"].asString();//Ok
        imagesAffichage[i].width       = root[i]["image_width"].asInt(); //Ok
        imagesAffichage[i].height      = root[i]["image_height"].asInt();// Ok

        /*Search tab*/
        imagesAffichage[i].preview_url             = baseSiteIndex + root[i]["preview_file_url"].asString(); //Ok

        imagesAffichage[i].sample_url          = baseSiteIndex + root[i]["large_file_url"].asString(); //Ok

        imagesAffichage[i].rating   = *strdup(root[i]["rating"].asString().c_str()); //Ok

        imagesAffichage[i].tagNumber = loadTags(root[i]["tag_string"].asString(), imagesAffichage[i].tags); //Ok
    }
}


int returnTagNumberDanbooru(Json::Value root)
{
    int tagIndex = 0;
    while(root[tagIndex]["id"] == Json::intValue)
    {
        tagIndex++;
    }
    return tagIndex;
}

int lectureTagsDanbooru(std::string input, std::string output[][3], Json::Value root)
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
