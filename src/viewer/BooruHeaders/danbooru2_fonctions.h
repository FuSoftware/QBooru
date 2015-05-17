#ifndef FONCTIONSDANBOORU_H
#define FONCTIONSDANBOORU_H

#include <QString>
#include <QNetworkAccessManager>
#include "generic_booru_image.h"
#include "constantes.h"
#include "../json/json.h"

void chargementImagesDanbooru2(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath, std::string baseSiteIndex);
int returnTagNumberDanbooru2(Json::Value root);
int lectureTagsDanbooru2(std::string input, std::string output[][3], Json::Value root);

#endif // FONCTIONSDANBOORU_H
