#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <sstream>
#include "widget.h"

#include <QString>
#include <QDir>

#include "../json/json.h"

#include "constantes.h"
#include "fonctions.h"
#include "moebooru_fonctions.h"

void chargementImagesMoebooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath)
{
    int i;
    Json::Value root = loadJSONFile(stringToCString(searchFilePath)); // will contains the root value after parsing
    Json::Value root_config = loadJSONFile(CONF_FILE); // will contains the root config value after parsing
    int picture_number = root_config["settings"]["picture_number"].asInt();

    for(i=0;i<picture_number;i++)
    {

        imagesAffichage[i].id               = root["posts"][i]["id"].asInt();
        imagesAffichage[i].created_at       = returnTimeStringConvert(returnPostAgeSec(root["posts"][i]["created_at"].asInt()));
        imagesAffichage[i].author           = strdup(root["posts"][i]["author"].asString().c_str());
        imagesAffichage[i].source           = strdup(root["posts"][i]["source"].asString().c_str());
        imagesAffichage[i].score            = root["posts"][i]["score"].asInt();
        imagesAffichage[i].file_size        = root["posts"][i]["file_size"].asInt();

        imagesAffichage[i].file_url    = root["posts"][i]["file_url"].asString();
        imagesAffichage[i].width       = root["posts"][i]["width"].asInt();
        imagesAffichage[i].height      = root["posts"][i]["height"].asInt();

        /*Search tab*/
        imagesAffichage[i].preview_url             = root["posts"][i]["preview_url"].asString();
        imagesAffichage[i].preview_height          = root["posts"][i]["preview_height"].asInt();
        imagesAffichage[i].preview_width           = root["posts"][i]["preview_width"].asInt();
        imagesAffichage[i].actual_preview_height   = root["posts"][i]["actual_preview_height"].asInt();
        imagesAffichage[i].actual_preview_width    = root["posts"][i]["actual_preview_width"].asInt();

        imagesAffichage[i].sample_url          = root["posts"][i]["sample_url"].asString();
        imagesAffichage[i].sample_height       = root["posts"][i]["sample_height"].asInt();
        imagesAffichage[i].sample_width        = root["posts"][i]["sample_width"].asInt();
        imagesAffichage[i].sample_file_size    = root["posts"][i]["sample_file_size"].asInt();

        imagesAffichage[i].full_url          = root["posts"][i]["jpeg_url"].asString();
        imagesAffichage[i].full_height       = root["posts"][i]["jpeg_height"].asInt();
        imagesAffichage[i].full_width        = root["posts"][i]["jpeg_width"].asInt();
        imagesAffichage[i].full_file_size    = root["posts"][i]["jpeg_file_size"].asInt();

        imagesAffichage[i].rating   = *strdup(root["posts"][i]["rating"].asString().c_str());

        imagesAffichage[i].tagNumber = loadTags(root["posts"][i]["tags"].asString(), imagesAffichage[i].tags);
    }
}

int returnTagNumberMoebooru(Json::Value root)
{
    int tagIndex = 0;
    while(root[tagIndex]["id"].asInt() != NULL)
    {
        tagIndex++;
    }
    return tagIndex;
}

int lectureTagsMoebooru(std::string input, std::string output[][3], Json::Value root)
{
    int tagIndex = 0;
    int j = 0;

    /*Indicateurs des colonnes*/

    output[j][0] = "Tag Name";
    output[j][1] = "Tag ID";
    output[j][2] = "Tag Count";
    j++;

    /*Lecture des tags*/
    while(root[tagIndex]["id"].asInt() != NULL)
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
