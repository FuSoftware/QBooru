#include <iostream>
#include "widget.h"

#include <QString>

#include "../json/json.h"

#include "fonctions.h"
#include "derpibooru_fonctions.h"

void chargementImagesDerpibooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath)
{
    int i;
    Json::Value root = loadJSONFile(stringToCString(searchFilePath)); // will contains the root value after parsing
    Json::Value root_config = loadJSONFile(CONF_FILE); // will contains the root config value after parsing

    for(i=0;i<root_config["settings"]["picture_number"].asInt();i++)
    {
        imagesAffichage[i].id        = root["search"][i]["id_number"].asInt();
        imagesAffichage[i].created_at       = root["search"][i]["created_at"].asString();
        imagesAffichage[i].author         = root["search"][i]["uploader"].asString();
        imagesAffichage[i].score         = root["search"][i]["score"].asInt();
        imagesAffichage[i].width  = root["search"][i]["width"].asInt();
        imagesAffichage[i].height = root["search"][i]["height"].asInt();
        imagesAffichage[i].source              = root["search"][i]["source_url"].asString();

        /*Representations*/
        imagesAffichage[i].preview_url   = root["search"][i]["representations"]["thumb_small"].asString().c_str();
        imagesAffichage[i].sample_url   = root["search"][i]["representations"]["medium"].asString().c_str();
        imagesAffichage[i].full_url   = root["search"][i]["representations"]["full"].asString().c_str();

        /**
          Unused for now:
        imagesAffichage[i].id               = root["search"][i]["id"].asString().c_str();
        imagesAffichage[i].is_rendered             = root["search"][i]["is_rendered"].asBool();
        imagesAffichage[i].is_optimized            = root["search"][i]["is_optimized"].asBool();
        imagesAffichage[i].upvotes       = root["search"][i]["upvotes"].asInt();
        imagesAffichage[i].downvotes     = root["search"][i]["downvotes"].asInt();
        imagesAffichage[i].comment_count = root["search"][i]["comment_count"].asInt();
        imagesAffichage[i].aspect_ratio = root["search"][i]["aspect_ratio"].asDouble();
        imagesAffichage[i].original_format = root["search"][i]["original_format"].asString().c_str();
        imagesAffichage[i].mime_type       = root["search"][i]["mime_type"].asString().c_str();
        imagesAffichage[i].license                 = root["search"][i]["license"].asString().c_str();
        imagesAffichage[i].updated_at       = root["search"][i]["updated_at"].asString().c_str();
        imagesAffichage[i].file_name        = root["search"][i]["file_name"].asString().c_str();
        imagesAffichage[i].description      = root["search"][i]["description"].asString().c_str();

        imagesAffichage[i].representations[0][1]   = root["search"][i]["representations"]["thumb_tiny"].asString().c_str();
        imagesAffichage[i].representations[2][1]   = root["search"][i]["representations"]["thumb"].asString().c_str();
        imagesAffichage[i].representations[3][1]   = root["search"][i]["representations"]["small"].asString().c_str();
        imagesAffichage[i].representations[5][1]   = root["search"][i]["representations"]["large"].asString().c_str();
        imagesAffichage[i].representations[6][1]   = root["search"][i]["representations"]["tall"].asString().c_str();

        imagesAffichage[i].image            = root["search"][i]["image"].asString();
        */

    }
}

char* loadAPIKey()
{
    Json::Value root;
    char* key;
    root = loadJSONFile(CONF_FILE);

    key = strdup(root["settings"]["api_key_derpibooru"].asCString());
    return key;
}
