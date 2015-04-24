#ifndef FONCTIONSGELBOORU_H
#define FONCTIONSGELBOORU_H

#include <QString>
#include "generic_booru_image.h"
#include "constantes.h"

#include "json/json.h"

void chargementImagesGelbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath, std::string baseSiteIndex);
int returnTagNumberGelbooru(Json::Value root);
int lectureTagsGelbooru(std::string input, std::string output[][3], Json::Value root);

#endif // FONCTIONSGELBOORU_H
